#include "Physics.h"


double physics::calculateEnergyLossCSDA (double length, double eIn, Material* material)
{
    double materialDensity = material->getDensity();
    // E in MeV
    double E_after = 0;
	if ( eIn < 0.05 ){
		return 0 ;
	}
    // length to cm
    length = length / 10;

	double Range_before= material->CSDARangeEval(eIn) ;
	double Range_after=0;
	if ( Range_before > length* materialDensity / material->detourEval(eIn))
    {
		E_after = material->CSDARangeInverseEval(Range_before - length* materialDensity  / material->detourEval(eIn));
        // std::cout << "length: " << length << "   eIn: " << eIn << "\n";
        // std::cout << "eIn - after: "<<eIn - E_after << "   e after: " << E_after << "\n";
        return eIn - E_after;
	}

	else {
        E_after = 0 ;
		return E_after;
	}
    return 0;
}


double physics::sampleEnergyStraggling (double length, double eIn, double eLoss, Material* material)
{
    // convert to units used in straggling functions
    eIn = eIn * 1000.;                                   // from MeV to keV
    length = length / 10.;                                // from mm to cm
    eLoss = eLoss * 1000.;                               // from MeV to keV

    // electron parameters
    double massElectron = 511;                          //in keV

    // incoming particle parameters -> hard coded proton
    int incomingZ = 1;
    double incomingMass = 938.*1000.;                     //in keV
    double kin_energy = eIn;                            //in keV
    double gamma = kin_energy / incomingMass + 1;
    double beta = sqrt(1. - 1. / (gamma*gamma));

    // traversed volume material parameters -> hard coded Polystyrene
    double materialZ = material->getZ();
    double materialA = material->getA();
    double materialDensity = material->getDensity();

    // calculate xi
    double xi = 153.4 * incomingZ * incomingZ / (beta*beta) * materialZ / materialA * materialDensity * length;
    // calculate eMax
    double eMax = (2. * massElectron * beta * beta * gamma * gamma) / (1 + 2 * gamma * massElectron / incomingMass + (massElectron * massElectron) / (incomingMass * incomingMass));
    // calculate kappa
    double kappa = xi / eMax;

    double eStrag = 0;

    // std::cout << "kappa: " << kappa << "\n";

    // // decide which kappa regime should be used
    // if ((kappa < 10) && (kappa > 0.01))    // kappa < 10 -> Vavilov distribution
    // {
    //     eStrag = eLoss/1000;
    //     // // TF1 vavi ("vavi", "TMath::Vavilov(x,[0] , [1])", -100, 100);
    //     // vavi->SetParameters(kappa, beta*beta);
    //     // while (eStrag <= 0)
    //     // {
    //     //
    //     //     // sample lambdaL from Vavilov distribution
    //     //     double lambdaL = vavi->GetRandom();
    //     //
    //     //     // calculate straggling from lambdaL
    //     //     eStrag = xi * (lambdaL + TMath::Log(kappa) + (1 - TMath::EulerGamma()) + (beta * beta)) + eLoss;
    //     //     // convert eStrag to MeV
    //     //     eStrag /= 1000;
    //     //     if (eStrag <= 0)
    //     //     {
    //     //         if(debugLvl >= 100)
    //                 std::cout << "Energy Straggling Vavilov (MeV): " << eStrag << "\n";
    //     //     }
    //     // }
    // }
    // else if (kappa <= 0.01)
    if (kappa <= 0.01)
    {
        // std::cout << "kappa kleiner 0.01" << "\n";
        eStrag = eLoss/1000;
    }
    else                // kappa > 10 -> Gaus distribution
    {
        // std::cout << "eLoss: " << eLoss << "\n";
        double sigma = sqrt( xi * eMax * (1. - (beta * beta)/2.) );
        eStrag = gRandom->Gaus(eLoss,sigma);
        eStrag /= 1000.;
        // std::cout << "Delta Energy Straggling Gauss (MeV): " << eLoss/1000 - eStrag << "\n";
    }
    return eIn/1000. - eStrag;
}


void physics::sampleMultipleScattering (double length, double eIn, TVector3 &direction, Material* material)
{

    // !!!!!!!
    // not implemented correctly -> sampling of the angles is wrong. Should be like in Michael Milde's master thesis
    // !!!!!!!


    // inconming -> hard coded proton
    double incomingMass = 938;  // in MeV/c
    int incomingZ = 1;

    double kin_energy = eIn;
    double gamma = kin_energy / incomingMass + 1;
    double beta = sqrt(1 - 1 / (gamma*gamma));

    // traversed volume material parameters -> hard coded Polystyrene
    double materialDensity = material->getDensity(); // in g/cm^3
    double radiationLength = material->getRadiationLength(); // in g/cm^2
    double L = radiationLength/materialDensity * 10; // in mm
    double xOverL = length / L;

    // Highland formula -> in rad
    double sigma = 0.5* ( 0.91 * sqrt(2) * 15 /  (2*eIn) ) * ( 0.91 * sqrt(2) * 15 /  (2*eIn) ) * incomingZ * incomingZ * xOverL * (1+0.04*log(xOverL))* (1+0.04*log(xOverL));

    // both angles are uncorrelated -> sample from two 1 dim gaussians
    double t = gRandom->Gaus(0,TMath::Sqrt(sigma));
    double p = gRandom->Gaus(0,TMath::Sqrt(sigma));

    // std::cout << "delta theta: " << t << "  delta phi: " << p << "\n";
    // turn around direction and add scattering angles
    direction = -1* direction;
    double thetaDir = direction.Theta() +t;
    double phiDir = direction.Phi() +p;
    direction.SetTheta(thetaDir);
    direction.SetPhi(phiDir);
    direction.SetMag(1);
}

double physics::maxRangeInMaterial (double eIn, Material* material)
{
    double projectedRange = material->CSDARangeEval(eIn) * material->detourEval(eIn);
    projectedRange *= 10; // convert projectedRange from cm to mm
    return projectedRange;
}



double physics::backCalculateEnergyLossCSDA (double length, double eIn, Material* material)
{
    double materialDensity = material->getDensity();
    // E in MeV
    double E_after = 0;
    // length to cm
    length = length / 10;

    double range = material->CSDARangeEval(eIn) + length * materialDensity / material->detourEval(eIn);
    return material->CSDARangeInverseEval(range);
}



// double physics::backSampleEnergyStraggling (double length, double eIn, double eLoss, Material* material)
// {
//     // convert to units used in straggling functions
//     eIn = eIn * 1000;                                   // from MeV to keV
//     length = length /10;                                // from mm to cm
//     eLoss = eLoss * 1000;                               // from MeV to keV
//
//     // electron parameters
//     double massElectron = 511;                          //in keV
//
//     // incoming particle parameters -> hard coded proton
//     int incomingZ = 1;
//     double incomingMass = 938*1000;                     //in keV
//     double kin_energy = eIn;                            //in keV
//     double gamma = kin_energy / incomingMass + 1;
//     double beta = sqrt(1 - 1 / (gamma*gamma));
//
//     // traversed volume material parameters -> hard coded Polystyrene
//     double materialZ = material->getZ();
//     double materialA = material->getA();
//     double materialDensity = material->getDensity();
//
//     // calculate xi
//     double xi = 153.4 * incomingZ * incomingZ / (beta*beta) * materialZ / materialA * materialDensity * length;
//     // calculate eMax
//     double eMax = (2* massElectron * beta * beta * gamma * gamma) / (1 + 2 * gamma * massElectron / incomingMass + (massElectron * massElectron) / (incomingMass * incomingMass));
//     // calculate kappa
//     double kappa = xi / eMax;
//
//     double eStrag = 0;
//
//     if (kappa <= 0.01)
//     {
//         // std::cout << "kappa kleiner 0.01" << "\n";
//         eStrag = eLoss/1000;
//     }
//     else                // kappa > 10 -> Gaus distribution
//     {
//         // std::cout << "eLoss: " << eLoss << "\n";
//         double sigma = sqrt( xi * eMax * (1 - (beta * beta)/2) );
//         eStrag = gRandom->Gaus(eLoss,sigma);
//         eStrag /= 1000;
//         // std::cout << "Delta Energy Straggling Gauss (MeV): " << eStrag << "\n";
//     }
//     return eStrag;
// }








double physics::backSampleEnergyStraggling (double length, double eIn, Material* material)
{
    // hit or miss algorithm

    //  define parameters
    double upperBoundary = 0.1;
    double proposeRange = 0.1;

    // use CSDA backward to get an educated guess for eInPropose
    double before = physics::backCalculateEnergyLossCSDA (length, eIn, material);

    // break condition
    bool stop = false;
    double finaleEIn = 0;

    while (!stop) {
        // sample a proposed eIn
        double eInPropose = gRandom->Uniform(before-proposeRange*before,before+proposeRange*before);
        // use eInPropose to calculate proposed mean e loss
        double meanELossProposed = physics::calculateEnergyLossCSDA (length, eInPropose, material);
        // get straggling sigma for proposed eIn
        double sigma = physics::getEnergyStragglingSigma(length, eInPropose, material);
        // evaluate straggling function
        double t = TMath::Gaus((eInPropose - eIn)*1000,meanELossProposed*1000,sigma,true);
        // sample uniformly for hit and miss
        double u = gRandom->Uniform(0,upperBoundary);
        // hit or miss
        if (u < t)
        {
            // accept
            finaleEIn = eInPropose;
            return finaleEIn;
            stop = true;
        }
    }
}


double physics::getEnergyStragglingSigma (double length, double eIn, Material* material)
{
    // convert to units used in straggling functions
    eIn = eIn * 1000;                                   // from MeV to keV
    length = length /10;                                // from mm to cm

    // electron parameters
    double massElectron = 511;                          //in keV

    // incoming particle parameters -> hard coded proton
    int incomingZ = 1;
    double incomingMass = 938*1000;                     //in keV
    double kin_energy = eIn;                            //in keV
    double gamma = kin_energy / incomingMass + 1;
    double beta = sqrt(1 - 1 / (gamma*gamma));

    // traversed volume material parameters -> hard coded Polystyrene
    double materialZ = material->getZ();
    double materialA = material->getA();
    double materialDensity = material->getDensity();

    // calculate xi
    double xi = 153.4 * incomingZ * incomingZ / (beta*beta) * materialZ / materialA * materialDensity * length;
    // calculate eMax
    double eMax = (2* massElectron * beta * beta * gamma * gamma) / (1 + 2 * gamma * massElectron / incomingMass + (massElectron * massElectron) / (incomingMass * incomingMass));
    // calculate kappa
    double kappa = xi / eMax;

    if (kappa <= 0.01)
    {

    }
    else
    {
        double sigma = sqrt( xi * eMax * (1 - (beta * beta)/2) );
        return sigma;
    }
    return 0;
}
