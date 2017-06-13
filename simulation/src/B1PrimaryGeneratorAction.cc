
#include "B1PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1PrimaryGeneratorAction::B1PrimaryGeneratorAction(B1Config* conf)
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{

   config = conf;
   useRootHisto = config->Get_useRootHistoForGun();

   // decide if user wants to use his own root histogramms (-> then the normal particle gun is used)
   // or if he wants to use a gun file (-> then the G4GeneralParticleSource is used)
   if (useRootHisto)
   {
       // Set up default gun properties
       // if user has choosen to use Root histogramms he has to provide a histogram for
       // the energy distribution and the angular distribution
       // For the particle position we first sample a point in a spherial volume
       // around the detector. The particle start position is then generated on a spherical
       // surface with its angles are sampled out of the angular distribution and the radius is a fixed value.
       // The momentum direction is then set to the first sampled points.

       // initialize gun
       histoGun = new G4ParticleGun(1);

       // one particle -> from config file
       G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
       G4ParticleDefinition* particle  = particleTable->FindParticle(config->Get_particleName().c_str());
       histoGun->SetParticleDefinition(particle);

       // initialize random with job number as seed
       randomGenerator = new TRandom (config->Get_job_number ());

       // initialize parameters
       radiusStart = 30;
       centerMaxRadius = 15;

    //    // read in histogram
    //    TFile *f = TFile::Open(config->Get_rootFile().c_str());
    //    if (f == 0)
    //    {
    //        printf("Error: cannot open ROOT file");
    //        return;
    //    }
    //    // load histogramms for energy and direction
    //    f->ls();
    //    energyHisto = (TH1F*) f->Get("energyHisto");
    //    if (energyHisto == 0)
    //    {
    //        printf(" Error: cannot open histo");
    //        return;
    //    }
       //
    //    angularHisto = (TH2F*) f->Get("angular");
    //    if (angularHisto == 0)
    //    {
    //        printf("Error: cannot find angularHisto");
    //        return;
    //    }
   }

       // default particle gun
       fParticleGun  = new G4GeneralParticleSource();

       // one particle : proton
       G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
       G4ParticleDefinition* particle  = particleTable->FindParticle("proton");
       fParticleGun->SetParticleDefinition(particle);
       fParticleGun->SetNumberOfParticles(1);

       // gun position on a sphere surface around origin (0,3.5,0) with radius 7 cm
       fParticleGun->GetCurrentSource()->GetPosDist()->SetPosDisType("Surface");
       fParticleGun->GetCurrentSource()->GetPosDist()->SetPosDisShape("Sphere");
       fParticleGun->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(0.*cm,3.5*cm,0.*cm));
       fParticleGun->GetCurrentSource()->GetPosDist()->SetRadius(7.*cm);

       // isotropic angular distribution
       fParticleGun->GetCurrentSource()->GetAngDist()->SetAngDistType("iso");

       // mono energetic with energy of 100 MeV
       fParticleGun->GetCurrentSource()->GetEneDist()->SetEnergyDisType("Mono");
       fParticleGun->GetCurrentSource()->GetEneDist()->SetMonoEnergy(100*GeV);



}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1PrimaryGeneratorAction::~B1PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    if (useRootHisto)
    {
        // generateFromHisto1();
        generateToMidPoint();
        histoGun->GeneratePrimaryVertex(anEvent);
    }
    else
    {
        fParticleGun->GeneratePrimaryVertex(anEvent);
    }
}



void B1PrimaryGeneratorAction::generateFromHisto1 ()
{
    // Set Energie
    histoGun->SetParticleEnergy(30.0*MeV);

    TVector3 startPosition (0,0,0);
    TVector3 direction (0,0,0);
    TVector3 centerPosition (centerMaxRadius,centerMaxRadius,centerMaxRadius);

    // while (startPosition.y() <= 0)
    // {
        // Set Position -> sample from a spherical volume around detector
        while (centerPosition.Mag() > centerMaxRadius)
        {
            Double_t xCenter = randomGenerator->Uniform(-centerMaxRadius, centerMaxRadius);
            Double_t yCenter = randomGenerator->Uniform(-centerMaxRadius, centerMaxRadius);
            Double_t zCenter = randomGenerator->Uniform(-centerMaxRadius, centerMaxRadius);

            centerPosition = TVector3(xCenter,yCenter,zCenter);
        }
        centerPosition += TVector3(0,3.5,0);

        // Generate direction
        // from histogram
        // Double_t thetaDirection;
        // Double_t phiDirection;
        // angularHisto->GetRandom2(thetaDirection,phiDirection);

        // isotropic flux generated in this way
        Double_t thetaDirection = randomGenerator->Uniform(0,180)*TMath::Pi()/180;
        Double_t phiDirection = randomGenerator->Uniform(-180,180)*TMath::Pi()/180;

        // direction.SetMagThetaPhi(radiusStart,thetaDirection*TMath::Pi()/180,phiDirection*TMath::Pi()/180);
        direction.SetMagThetaPhi(radiusStart,thetaDirection,phiDirection);
        startPosition = centerPosition - direction;
    // }

    histoGun->SetParticlePosition(G4ThreeVector(startPosition.x() *cm,startPosition.y()*cm,startPosition.z()*cm));
    histoGun->SetParticleMomentumDirection(G4ThreeVector(direction.x(),direction.y(),direction.z()));
}

void B1PrimaryGeneratorAction::generateToMidPoint ()
{
    // Set Energie
    histoGun->SetParticleEnergy(50.0*MeV);

    G4ThreeVector pos = fParticleGun->GetCurrentSource()->GetPosDist()->GenerateOne();

    histoGun->SetParticlePosition(pos);
    histoGun->SetParticleMomentumDirection(-(pos-G4ThreeVector(0.*cm,3.5*cm,0.*cm)));
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
