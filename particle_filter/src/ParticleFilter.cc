#include "ParticleFilter.h"

#include "MCategory.h"
#include "MGeantTrack.h"

ParticleFilter::ParticleFilter(UserCGALGeometry* geo, int num) : debugLvl(1), evalSigma(0.05), number(num), geometry(geo) {}

int f_cnt = 0;
int f_pidx = 0;
ParticleFilter::~ParticleFilter()
{
    for (int i=0;i<number;i++)
    {
        delete particles[i];
        delete temps[i];
    }
    particles.clear();
    temps.clear();
}

bool ParticleFilter::initEvent(MDataManager * event_, double deltaE, double deltaPos, double deltaDir)
{
    event = event_;
    catFibersCal = event->getCategory(MCategory::CatFibersCal);
    catGeantTrack = event->getCategory(MCategory::CatGeantTrack);

//     printf("============== RANDOM PARTICLES =================\n");
    // generate particles and weights
    for (int i=0; i < number; i++)
    {
        // generate particles
        Particle * rand_part = generateParticleFromSimulatedEvent(deltaE, deltaPos, deltaDir);
        particles.push_back(rand_part);
        
        // generate temps
        temps.push_back(new Particle());
        
        // set all weights uniformly
        weights.push_back(1.0 / number);
        tempWeights.push_back(1.0 / number);
        
        // calculate CDF
        cdf.push_back(i * 1.0 / number);

//         rand_part->print();
//         printf("[idx=%3d]  weight=%g  cdf=%g\n\n", i, weights[i], cdf[i]);
    }
    cdf[number] = 1.0;
    
    checkVectorSize ();
    std::cout << "initialize PF done" << "\n";
}

Particle* ParticleFilter::generateParticleFromSimulatedEvent(double deltaE, double deltaDir, double deltaPos)
{
    int tracks = catGeantTrack->getEntries();
    MGeantTrack * track = nullptr;
    
    if (tracks > 0)
        track = (MGeantTrack *) catGeantTrack->getObject(0);
    else
        return nullptr;
    
    //     printf("in pos=%f,%f,%f\n", track->getStartX(), track->getStartY(), track->getStartZ());
    TVector3 inPos(track->getStartX(), track->getStartY(), track->getStartZ());
    TVector3 inDir(track->getStartPx(), track->getStartPy(), track->getStartPz());
    
    // sample pIn
    TVector3 pIn = samplePos(inPos, deltaPos);
    // sample pOut
    TVector3 pOut = pIn + sampleDir(inDir, deltaDir);
    // sample E0 -> E0 = eIn = eOut
    double eIn = sampleE0(track->getStartE(), deltaE);
    double eOut = eIn;
    
    return new Particle(pIn, pOut, eIn, eOut);
}

TVector3 ParticleFilter::samplePos(TVector3 p, double deltaPos)
{
    // shift the MC truth value randomly +/- 1
    double shiftValue1 = gRandom->Uniform(-1, 1);
    double shiftValue2 = gRandom->Uniform(-1, 1);
    //sample
    p = p - TVector3(0,35,0); // shift sphere to origin
    double theta = gRandom->Uniform(p.Theta()/TMath::Pi()*180-deltaPos + shiftValue1,p.Theta()/TMath::Pi()*180+deltaPos + shiftValue1);
    double phi = gRandom->Uniform(p.Phi()/TMath::Pi()*180-deltaPos + shiftValue2 ,p.Phi()/TMath::Pi()*180+deltaPos + shiftValue2);
    
    // create the position vector
    TVector3 d;
    d.SetMagThetaPhi(p.Mag(),theta*TMath::Pi()/180,phi*TMath::Pi()/180);
    return d + TVector3(0,35,0);
}

TVector3 ParticleFilter::sampleDir(TVector3 p, double deltaDir)
{
    // shift the MC truth value randomly +/- 1
    double shiftValue1 = gRandom->Uniform(-1, 1);
    double shiftValue2 = gRandom->Uniform(-1, 1);
    
    //sample
    double theta = gRandom->Uniform(p.Theta()/TMath::Pi()*180-deltaDir,p.Theta()/TMath::Pi()*180+deltaDir);
    double phi = gRandom->Uniform(p.Phi()/TMath::Pi()*180-deltaDir,p.Phi()/TMath::Pi()*180+deltaDir);
    
    TVector3 d;
    d.SetMagThetaPhi(1,theta*TMath::Pi()/180,phi*TMath::Pi()/180);
    return d;
}

double ParticleFilter::sampleE0(double e, double deltaE)
{
    // shift the MC truth value randomly +/- 1
    double shiftValue1 = gRandom->Uniform(-1, 1);
    //sample
    return gRandom->Uniform(e + shiftValue1 - deltaE, e + shiftValue1 + deltaE);
}

bool ParticleFilter::checkVectorSize()
{
    if (particles.size() != number)
    {
        std::cerr << "particle size not equal number" << "\n";
        return false;
    }
    if (weights.size() != number)
    {
        std::cerr << "weights size not equal number" << "\n";
        return false;
    }
    if (tempWeights.size() != number)
    {
        std::cerr << "tempWeights size not equal number" << "\n";
        return false;
    }
    if (cdf.size() != number)
    {
        std::cerr << "cdf size not equal number: " << cdf.size() << "\n";
        return false;
    }
    return true;
}

bool ParticleFilter::checkInitialisation()
{
    if (!checkVectorSize())
    {
        std::cerr << "Particles not initialized" << "\n";
        return false;
    }
    if (geometry == NULL)
    {
        std::cerr << "geometry not initialized" << "\n";
        return false;
    }
    if (event == NULL)
    {
        std::cerr << "event not initialized" << "\n";
        return false;
    }
    if (catFibersCal == NULL)
    {
        std::cerr << "hits not initialized" << "\n";
        return false;
    }
    return true;
}

int ParticleFilter::sir()
{
    // perform an uniform sampling along y-axis
    double rn = RandomGenerator::getInstance()->uniform();

    // search the corresponding particle on x-axis (binary search)
    int start = 0;
    int end = number;
    while ((start+1) < end)
    {
        int center = (start + end) / 2;
        if (rn < cdf[center])
            end = center;
        else
            start = center;
    }

    // done
    return start;
}

// forward filter
bool ParticleFilter::filter()
{
    // check check consistency
    if (!checkInitialisation())
        return false;
    
    // number of measurements
    catGeantTrack->print();
    catFibersCal->print();
    int numMeasurements = catFibersCal->getEntries();
    
    std::cout << "\n\n\nSTART FILTERING" << "\n";
    std::cout << "\nThere are "<< numMeasurements << " measurements (fibers)" << "\n";
    std::cout << "------------------------------------------------------";
    std::cout <<"\nTest particles: "<< number <<  "\n\n\n";
    
    Particle* oldP = new Particle();
    Particle* newP = new Particle();
    
    for (int i = 0; i < numMeasurements; ++i)
    {
        MFibersCal * f = (MFibersCal *)(catFibersCal->getObject(i));
        f->print();
    }

    // loop through measurements
    for (int m = 0; m < numMeasurements; ++m)
    {
        int state[4] = { 0 };

//         printf("============ WEIGHTS =============\n");
//         for (int i = 0; i < number; ++i)
//             printf("[idx=%3d]  weight=%g  cdf=%g\n", i, weights[i], cdf[i]);

        std::cout << "--------------------\nFiber: " << m << "\n";
        int p_idx;                          // sampled particle ID
        double i_sum = 0;                   // sum of weights
        
        // generate a new particle set
        for (int i=0; i< number; ++i)
        {
            // draw a particle according to weights factors
            int errorSum = 0;
            double eO=-1;
            while (eO <= 0) // only draw particles with energy > 0
            {
                errorSum++;
                p_idx = sir();
//                 printf("p_idx = %d\n", p_idx);
                eO = particles[p_idx]->geteOut();
                if (errorSum >= 10000)
                {
                    std::cout << "errorSum >= 10000" << "\n";
                    for (int y=0;y<number;y++){
                        std::cout << weights[y] << "\n";
                    }
                    return false;
                }
            }
            // set the old particle
            oldP->set(particles[p_idx]);
//             printf("Test particle:\n");
//             oldP->print();

            int volumeIndex = -1;
            // propagate the particle
            int status = propagate(oldP, newP, volumeIndex);

            f_pidx = p_idx;
            f_cnt = i;
            switch(status)
            {
                case 1: { // particle is in fiber -> do evaluation
                    // particle lost all its energy before the last fiber -> weight to zero
//                     printf("eOut = %f\n", newP->geteOut());
                    if ((m != numMeasurements-1) && (newP->geteOut() <= 0.00001))
                    {
                        i_sum += tempWeights[i] = 0;
                    }
                    // normal evaluation
                    else
                    {
                        double w = evaluate(newP, volumeIndex);
                        if (w != w)
                        {
                            std::cerr << "weight from evaluate is nan in step: " << m << "\n";
                            newP->print();
                            w = 0;
                        }
                        i_sum += tempWeights[i] = w;
                    }
                    break;
                }
                case -1: { // error state -> set weight to 0
                    i_sum += tempWeights[i] = 0;
                    break;
                }
                case 0: { // out of world state
                    i_sum += tempWeights[i] = 0;
                    break;
                }
                case 2: { // particle stopped in CADPart before fiber -> weight becomes 0
                    i_sum += tempWeights[i] = 0;
                    break;
                }
            }
//             printf("i_sum=%g\n", i_sum);
            // copy new particle to temps[i]
            temps[i]->set(newP);
            ++state[status+1];
        }

        std::cout << "Step: " << m << " END" << "\n--------------------\n";
        printf("STATUS:\n [ 1] In Fiber = %d\n" \
        " [-1] Error = %d\n" \
        " [ 0] Out = %d\n" \
        " [ 2] Stopped = %d\n", state[2], state[0], state[1], state[3]);

        // check if all particles are invalid
        if (i_sum == 0.0)
        {
            cerr << "[Warning] none of the particles is valid. " << endl;
            cout << "[Warning] none of the particles is valid. " << endl;
            return false;
        }
        
        // swap buffers
        for (int s=0;s<particles.size();s++)
        {
            particles[s]->set(temps[s]);
            weights[s] = tempWeights[s];
        }
        
        // normalize weights factors and calculate CDF
        cdf[0] = 0;
        for (int i=0; i<number; i++)
        {
            weights[i] /= i_sum;                // normalize importance factors
            cdf[i+1] = cdf[i] + weights[i];     // calculate CDF
        }
    }
    
    std::cout << "\n------------------------------------------------------\n";
    std::cout << "finished filtering" << "\n\n\n";
    return true;
}

int ParticleFilter::propagate(Particle* p, Particle* newParticle, int &volumeIndex)
{
    TVector3 newPIn (0,0,0);
    TVector3 newPOut (0,0,0);
    double newEIn = -1;
    double newEOut = -1;
    volumeIndex = -1;
    
    do {
        newEIn = p->geteOut(); // the particle entry energy is the output energy of old particle
        
        if (newEIn <= 0.00001)
        {
            std::cerr << "in propagate: newEIn: " << newEIn << "\n";
            newEIn = 0;
            newParticle->set(p);
            return -1;
        }
        
        int stepStatus = geometry->getNextStep(p->getpOut(), p->getDir(), newPIn, newPOut, volumeIndex);
        switch (stepStatus)
        {
            case 1: // next step found
            {
                AbsPartCGAL* part = geometry->getCurrentPart(volumeIndex);
                // propagtePhysics
                propagatePhysics(newPIn,newPOut,newEIn,newEOut,part);
//                 printf("idx=%d\n", volumeIndex);newPIn.Print(); newPOut.Print();
                // which part? Fiber?
                CADFiberCGAL* fiber;
                if (fiber = dynamic_cast<CADFiberCGAL*>(part))
                {
//                     printf("vI=%d -> y,z=%d,%d\n", volumeIndex, fiber->getFiberY(), fiber->getFiberX()); newPIn.Print(); newPOut.Print();
                    // std::cerr << "It's a fiber" << "\n";
                    // it is a fiber -> step is finished
                    // new particle can be filled
                    newParticle->set(newPIn,newPOut,newEIn,newEOut);
                    // newParticle->print();
                    // std::cout << "fiber measurement: " << hits->getValue(fiber->getFiberX(),fiber->getFiberY()) << "\n";
                    // return for evaluation
                    return 1;
                }
                else
                {
                    // std::cerr << "It's a CADPart" << "\n";
                    // it is a CADPart -> stay in the loop until a Fiber is found
                    // no newParticle, just old particle with new values
                    p->set(newPIn,newPOut,newEIn,newEOut);
                    if (newEOut == 0) // particle stopped befor last fiber
                    {
                        return 2;
                    }
                    // p->print();
                }
                break;
            }
            case 0: // left world
            {
                newParticle->set(p);
                return 0;
                break;
            }
            case -1: // error
            {
                std::cerr << "[Error] in ParticleFilter::propagate()" << "\n";
                newParticle->set(p);
                return -1;
                break;
            }
        }
    } while (true);
}

void ParticleFilter::propagatePhysics(TVector3 &newPIn, TVector3 &newPOut, double &newEIn, double &newEOut, AbsPartCGAL* part)
{
    double length = (newPOut - newPIn).Mag();
    // does particle stop?
    if (physics::maxRangeInMaterial(newEIn,part->getMaterial()) > length)
    {
        // particle doesn't stops
        // calculate mean energy loss
        double eLoss = physics::calculateEnergyLossCSDA (length, newEIn, part->getMaterial());
        // sample energy straggling
        newEOut = physics::sampleEnergyStraggling (length, newEIn, eLoss, part->getMaterial());
        if (newEOut <= 0.00001)
        {
            // std::cout << "after straggling: newEOut <= 0.01" << "\n";
            newEOut = 0;
        }
        // sample multiple scattering
        TVector3 direction = newPOut - newPIn;
        direction.SetMag(1);
        physics::sampleMultipleScattering (length, newEIn, direction, part->getMaterial());
        newPIn = newPOut + direction;
    }
    else
    {
        // particle stops
        newEOut = 0;
    }
}

double ParticleFilter::evaluate(Particle* p, int volumeIndex)
{
    CADFiberCGAL* fiber = static_cast<CADFiberCGAL*> (geometry->getCurrentPart(volumeIndex));
    if (fiber != NULL)
    {
        //         p->print();
        double m = TMath::Abs(p->geteIn() - p->geteOut());
        MLocator loc(3);
        loc[0] = 0;
        loc[1] = fiber->getFiberY();
        loc[2] = fiber->getFiberX();

//         printf("************* category *************\n");
//         Int_t m_, l_, f_;
//         int n = catFibersCal->getEntries();
//         for (int i = 0; i < n; ++i)
//         {
//             MFibersCal * hit = (MFibersCal*) catFibersCal->getObject(i);
//             hit->getAddress(m_, l_, f_);
//             printf("object at %d,%d,%d\n", 0, l_, f_);
//         }

//         printf("************* geometry *************\n");
//         for (int i = 0; i < 30; ++i)
//         {
//         for (int j = 0; j < 30; j++)
//         {
//             CADFiberCGAL* fiber = dynamic_cast<CADFiberCGAL*> (geometry->getFiber(j, i));
//             if (fiber)
//             {
//                 double measurement = hits->getValue(fiber->getFiberX(),fiber->getFiberY());
//                 if (measurement)
//                     printf("fiber at %d,%d\n", j, i);
//             }
//         }
//         }

//         printf("************* current  *************\n");
//         printf("[t=%02d  pidx=%03d] asking for %d,%d,%d", f_cnt, f_pidx, 0, loc[1], loc[2]);

        MFibersCalSim * hit = (MFibersCalSim*) catFibersCal->getObject(loc);
        if (!hit)
        {
            //             Int_t m_, l_, f_;
            //             int n = catFibersCal->getEntries();
            //             for (int i = 0; i < n; ++i)
            //             {
            //                 MFibersCal * hit = (MFibersCal*) catFibersCal->getObject(i);
            //                 hit->getAddress(m_, l_, f_);
            //                 printf("object at %d,%d,%d\n", 0, l_, f_);
            //             }
            // 
            //             printf("asking for %d,%d,%d\n", 0, loc[1], loc[2]);
            // 
//             std::cout << "\tSHIT!" << std::endl;
            return 0;
        }
        double measurement = hit->getEnergyLoss();
// printf("Ein=%f  Eout=%f  dEdx=%f  E=%f  T=%f   vs  m=%f\n", p->geteIn(), p->geteOut(), hit->getEnergyLoss(), hit->getTotalEnergy(), hit->getKineticEnergy(), m);

        // if measurement is zero, weight of this particle also has to be zero
        // because it has to lose energy in this fiber, but nothingh is measured
        if (measurement == 0)
            return 0;
        
        // first test -> gaussian
        double w = TMath::Gaus (m,measurement,evalSigma);
//         printf("\tw = %f\n", w);
        return w;
    }
    else
    {
        std::cerr << "[Error] evaluate: volume not a fiber" << "\n";
        return -1;
    }
}

// BACK FILTER
bool ParticleFilter::backFilter()
{
    // initialize particles for back filtering
    // take the current particles and swap eIn and eOut, pIn and pOut
    for (int i = 0; i < number; ++i)
    {
        TVector3 pIn = particles[i]->getpIn();
        TVector3 pOut = particles[i]->getpOut();
        double eIn = particles[i]->geteIn();
        double eOut = particles[i]->geteOut();
        particles[i]->set(pOut,pIn,eOut,eIn);
    }
    
    // number of measurements
    int numMeasurements = catFibersCal->getEntries();
    numMeasurements--; // reduce numMeasurements because last measurement is not evaluated in back filter
    
    std::cout << "\n\n\nSTART BACK FILTERING" << "\n";
    std::cout << "\nThere are "<< numMeasurements << " Measurements" << "\n";
    std::cout << "------------------------------------------------------" <<"\nNumber: "<< number <<  "\n\n\n";

    Particle* oldP = new Particle();
    Particle* newP = new Particle();
    
    // loop through measurements
    for (int m=0;m<numMeasurements;m++)
    {
        int state[4] = { 0 };

        std::cout << "--------------------\nStep: " << m << "\n";
        int p_idx;                          // sampled particle ID
        double i_sum = 0;                   // sum of weights
        
        // generate a new particle set
        for (int i=0; i<number; i++)
        {
            // draw a particle according to weights factors
            p_idx = sir();
            // set the old particle
            oldP->set(particles[p_idx]);
            
            int volumeIndex = -1;
            // propagate the particle
            int status = backPropagate(oldP,newP,volumeIndex);
            switch(status) {
                case 1: // particle is in fiber -> do evaluation
                {
                    i_sum += tempWeights[i] = evaluate(newP, volumeIndex);
                    break;
                }
                case -1: // error state -> set weight to 0
                {
                    i_sum += tempWeights[i] = 0;
                    break;
                }
                case 0: // out of world state
                {
                    // if this is the last iteration => hold weight
                    
                    // else => particle left too early -> weight 0
                    i_sum += tempWeights[i] = 0;
                    break;
                }
            }
            // copy new particle to temps[i]
            temps[i]->set(newP);
            ++state[status+1];
        }
        // check how many different particle are there
        printf("STATUS:\n [ 1] In Fiber = %d\n" \
        " [-1] Error = %d\n" \
        " [ 0] Out = %d\n", state[2], state[0], state[1]);

        // check if all particles are invalid
        if (i_sum == 0.0)
        {
            cerr << "[Warning] none of the particles is valid. " << endl;
            cout << "[Warning] none of the particles is valid. " << endl;
            return false;
        }
        
        // swap buffers
        for (int s=0;s<particles.size();s++)
        {
            particles[s]->set(temps[s]);
            weights[s] = tempWeights[s];
        }
        
        // normalize weights factors and calculate CDF
        cdf[0] = 0;
        for (int i=0; i<number; i++)
        {
            // normalize importance factors
            weights[i] /= i_sum;
            // calculate CDF
            cdf[i+1] = cdf[i] + weights[i];
        }
        std::cout << "Step: " << m << " ENDE" << "\n--------------------\n";
    }
    std::cout << "\n------------------------------------------------------\n";
    std::cout << "finished filtering" << "\n\n\n";
    return true;
}

int ParticleFilter::backPropagate(Particle* p, Particle* newParticle, int &volumeIndex)
{
    TVector3 newPIn (0,0,0);
    TVector3 newPOut (0,0,0);
    double newEIn = -1;
    double newEOut = -1;
    volumeIndex = -1;
    
    // std::cout << "start propagate" << "\n";
    do {
        newEIn = p->geteOut(); // the particle entry energy is the output energy of old particle
        int stepStatus = geometry->getNextStep(p->getpOut(),p->getDir(),newPIn,newPOut, volumeIndex);
        switch (stepStatus){
            case 1: { // next step found
                AbsPartCGAL* part = geometry->getCurrentPart(volumeIndex);//printf("idx=%d\n", volumeIndex);newPIn.Print(); newPOut.Print();
                // propagtePhysics
                backPropagatePhysics(newPIn,newPOut,newEIn,newEOut,part);
                // which part? Fiber?
                CADFiberCGAL* fiber;
                if (fiber = dynamic_cast<CADFiberCGAL*>(part))
                {
                    // std::cerr << "It's a fiber" << "\n";
                    // it is a fiber -> step is finished
                    // new particle can be filled
                    newParticle->set(newPIn,newPOut,newEIn,newEOut);
                    // newParticle->print();
                    // std::cout << "fiber measurement: " << hits->getValue(fiber->getFiberX(),fiber->getFiberY()) << "\n";
                    // return for evaluation
                    return 1;
                }
                else
                {
                    // std::cerr << "It's a CADPart" << "\n";
                    // it is a CADPart -> stay in the loop until a Fiber is found
                    // no newParticle, just old particle with new values
                    p->set(newPIn,newPOut,newEIn,newEOut);
                    // p->print();
                }
                break;
            }
            case 0: { // left world
                newParticle->set(p);
                return 0;
                break;
            }
            case -1: { // error
                std::cerr << "[Error] in ParticleFilter::propagate()" << "\n";
                newParticle->set(p);
                return -1;
                break;
            }
        }
        
    } while (true);
}

void ParticleFilter::backPropagatePhysics(TVector3 &newPIn, TVector3 &newPOut, double &newEIn, double &newEOut, AbsPartCGAL* part)
{
    double length = (newPOut - newPIn).Mag();
    
    newEOut =  physics::backSampleEnergyStraggling (length, newEIn, part->getMaterial());
    
    // _______ OLD_________
    
    // calculate mean energy loss
    // newEOut = physics::backCalculateEnergyLossCSDA (length, newEIn, part->getMaterial());
    // double eLoss = newEOut - newEIn;
    // // sample energy straggling
    // newEOut =newEIn +  physics::backSampleEnergyStraggling (length, newEIn+eLoss, eLoss, part->getMaterial());
    
    // _______ OLD_________
    
    // sample multiple scattering
    TVector3 direction = newPOut - newPIn;
    direction.SetMag(1);
    physics::sampleMultipleScattering (length, newEIn, direction, part->getMaterial());
    newPIn = newPOut + direction;
}

void ParticleFilter::printParticles()
{
    for (int i=0; i< particles.size();i++){
        particles[i]->print();
    }
}

void ParticleFilter::createPosteriors(string path)
{
    TFile f(path.c_str(),"recreate");
    TH1D hE("E_in","e_in",500,-1,20);
    TH1D hEO("E_out","e_out",500,-1,10);
    TH1D hT("Theta","theta",1000,0,180);
    TH1D hP("Phi","phi",1000,-180,180);
    
    double sum =0;
    std::cout << "Output Posterior Particles: "<<particles.size()  << "\n";
    for (int i=0; i<particles.size();i++)
    {
        TVector3 dir =  particles[i]->getDir();
        double deltaT = dir.Theta();
        deltaT = deltaT/TMath::Pi()*180;
        double deltaP = dir.Phi();
        deltaP = deltaP/TMath::Pi()*180;
        double weight = weights[i];
        sum += weights[i];
        hE.Fill(particles[i]->geteIn(), weight);
        hEO.Fill(particles[i]->geteOut(), weight);
        hT.Fill(deltaT,weight);
        hP.Fill(deltaP,weight);
    }
    std::cout << "P Sum: " << sum << "\n";
    
    hE.Write();
    hEO.Write();
    hT.Write();
    hP.Write();
    f.Close();
}

void ParticleFilter::createBackPosteriors(string path, double time)
{
    int tracks = catGeantTrack->getEntries();
    MGeantTrack * track = nullptr;
    
    if (tracks > 0)
        track = (MGeantTrack *) catGeantTrack->getObject(0);
    else
        return;
    
    TVector3 inDir(track->getStartPx(), track->getStartPy(), track->getStartPz());
    
    double mcTheta = inDir.Theta()/TMath::Pi()*180;
    double mcPhi = inDir.Phi()/TMath::Pi()*180;
    
    TFile f(path.c_str(),"recreate");
    TH1D hEO("E_out","e_out",1000,20,110);
    TH1D hT("Theta","theta",100,-10,10);
    TH1D hP("Phi","phi",100,-10,10);
    
    TTree tree("pdf","pdf");
    double w, e0, phi, theta;
    double px, py, pz, t;
    tree.Branch("w",&w,"w/D");
    tree.Branch("e0",&e0,"e0/D");
    tree.Branch("theta",&theta,"theta/D");
    tree.Branch("phi",&phi,"phi/D");
    tree.Branch("px",&px,"px/D");
    tree.Branch("py",&py,"py/D");
    tree.Branch("pz",&pz,"pz/D");
    
    //time variable
    TVectorD v(1);
    v[0] = time;
    
    double sum =0;
    std::cout << "Output Posterior Particles: "<<particles.size()  << "\n";
    for (int i=0; i<particles.size();i++)
    {
        TVector3 dir = -1* particles[i]->getDir();
        double deltaT = dir.Theta()/TMath::Pi()*180 - mcTheta;
        double deltaP = dir.Phi()/TMath::Pi()*180 - mcPhi;
        double weight = weights[i];
        sum += weights[i];
        hEO.Fill(particles[i]->geteOut(), weight);
        hT.Fill(deltaT,weight);
        hP.Fill(deltaP,weight);
        
        // fill tree
        w = weight;
        e0 = particles[i]->geteOut();
        theta = dir.Theta()/TMath::Pi()*180;
        phi = dir.Phi()/TMath::Pi()*180;
        px = particles[i]->getpOut().X();
        py = particles[i]->getpOut().Y();
        pz = particles[i]->getpOut().Z();
        tree.Fill();
    }
    std::cout << "BP Sum: " << sum << "\n";
    
    hEO.Write();
    hT.Write();
    hP.Write();
    tree.Write();
    v.Write();
    f.Close();
}
