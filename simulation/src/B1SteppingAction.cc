//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B1SteppingAction.cc 74483 2013-10-09 13:37:06Z gcosmo $
//
/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4OpticalPhoton.hh"
#include "G4EmCalculator.hh"

#include "MMAPTManager.h"
#include "MGeantTrack.h"
#include "MGeantFibersRaw.h"

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction, MMAPTManager* root, B1DetectorConstruction* det, double kB_)
: G4UserSteppingAction(), data_manager(root), detector_construction(det), kB(kB_), fEventAction(eventAction)
{
}

B1SteppingAction::~B1SteppingAction()
{}

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{
    // get volume of the current step
    G4LogicalVolume* volume
    = step->GetPreStepPoint()->GetTouchableHandle()
    ->GetVolume()->GetLogicalVolume();

    // get the DetectorPart according to the current step logical volume
    AbsPart* part = detector_construction->getGeo()->getPart(volume);

    // Is there a detector part?
    if (part == NULL)
        return;

    // get the current_particle and the current event
    int track_ID = step->GetTrack()->GetTrackID();
    current_particle = fEventAction->getParticle(track_ID);

    // particle passed the detector
    current_particle->setInAcceptance(true);

    // get the step defining process and add it to the process list of the current particle if the process is important
    // important processes are defined in the else if section
    const G4String process = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    if (process == "compt")
    {
        current_particle->addProcess(process);
        current_particle->setProcess(MGeantTrack::COMPTON);
    }
    else if(process == "anti_protonInelastic") // empty example -> insert another important process name here
    {
        current_particle->addProcess(process);
        current_particle->setProcess(MGeantTrack::INELASTIC);
    }
    else if(process == "hFritiofCaptureAtRest") // empty example -> insert another important process name here
    {
        current_particle->addProcess(process);
        current_particle->setProcess(MGeantTrack::ATREST);
    }
    else if(process == "StepLimiter")
    {
        current_particle->setStopE(step->GetTrack()->GetKineticEnergy());
    }

    // stop in detektor volume
    if (part != NULL)
    {
        // set flag
        current_particle->setStopInDetector(true);
    }
    else
    {
        // particle did not stop in detektor
        current_particle->setStopInDetector(false);
    }

    // Energy Deposit in fiber
    // is the current volume a fiber?
    CADFiber* fiber = dynamic_cast<CADFiber*>(part);
    if (fiber)
    {
        MCategory * catGeantFibersRaw = data_manager->getCategory(MCategory::CatGeantFibersRaw);
        int x_fiber = fiber->getFiberX();
        int y_fiber = fiber->getFiberY();
        MLocator loc(3);
        loc[0] = 0;
        loc[1] = y_fiber;
        loc[2] = x_fiber;

        MGeantFibersRaw * detector_response = (MGeantFibersRaw *) catGeantFibersRaw->getObject(loc);
        if (!detector_response)
        {
            detector_response = (MGeantFibersRaw *) catGeantFibersRaw->getSlot(loc);
            detector_response = new (detector_response) MGeantFibersRaw;
            detector_response->setX(x_fiber);
            detector_response->setY(y_fiber);
        }
        
        G4double energy_step = step->GetTotalEnergyDeposit() - step->GetNonIonizingEnergyDeposit(); //take here only ionization energy loss
        // formular for  quenching
        double energy_step_quenching =  calculate_quenched_energy(step, kB, energy_step);

        detector_response->addEnergyLoss(step->GetTotalEnergyDeposit());
        detector_response->addEnergyDeposition(energy_step);

//         printf("add dEdx=%f loss=%f  depos=%f  e_in=%f   e_out=%f\n", energy_step, detector_response->getEnergyLoss(), detector_response->getEnergyDeposition(), step->GetPreStepPoint()->GetKineticEnergy(), step->GetPostStepPoint()->GetKineticEnergy());

        detector_response->setEnergyQuenching(energy_step_quenching);
        Float_t t_e = detector_response->getKineticEnergy();
        if (t_e == 0.0)
        {
            detector_response->setKineticEnergy(step->GetPreStepPoint()->GetKineticEnergy());
            detector_response->setTotalEnergy(step->GetPreStepPoint()->GetTotalEnergy());
        }
    }
}

G4double calculate_quenched_energy(const G4Step* step, G4double kB, G4double E_dep)
{
    G4double E_quenched = 0;
    G4double E_before = step->GetPreStepPoint()->GetKineticEnergy();
    G4double E_after = step->GetPostStepPoint()->GetKineticEnergy();
    G4EmCalculator *EmCalculator = new G4EmCalculator();
    G4ParticleDefinition* particle = step->GetTrack()->GetDefinition();
    G4Material* material = step->GetPreStepPoint()->GetMaterial();

    G4double dEdx = EmCalculator->GetDEDX(E_before, particle, material, 0);
    E_quenched += E_dep / (1 + kB * dEdx);


    //G4double range_step = range_diff / (double) substeps;


    //for (int n = 0; n < substeps; n++){
    //	G4double E1 = 0;
    //	G4double E2 = 0;
    //	if (n == 0){
    //		E1 = E_before;
    //	}
    //	else {
    //		E1 = EmCalculator->GetKinEnergy(total_range - range_step * n, particle, material,0);
    //	}
    //
    //	//E2 = EmCalculator->GetKinEnergy(total_range - range_step * (n + 1), particle, material, 0);
    //	E2 = E1 - EmCalculator->GetDEDX(E1,particle,material,0) * range_step;
    //
    //	G4double dEdx = EmCalculator->GetDEDX(E1, particle, material, 0);
    //	if (E1 >= E2){
    //		E_quenched += (E1 - E2)  / (1 + kB * dEdx);
    //		//printf("E1_corr = %e \n", E1);
    //		//printf("Range_1 = %e \n",total_range - range_step * n);
    //		//printf("E2_corr = %e \n", E2);
    //		//printf("Range_2 = %e \n",total_range - range_step * (n + 1));
    //	}
    //	else {
    //		//printf("E1 = %e \n", E1);
    //		//printf("Range_1 = %e \n",total_range - range_step * n);
    //		//printf("E2 = %e \n", E2);
    //		//printf("Range_2 = %e \n",total_range - range_step * (n + 1));
    //
    //	}
    //}

    delete EmCalculator;
    return E_quenched;
}
