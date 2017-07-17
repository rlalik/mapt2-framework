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
// $Id: B1EventAction.cc 75117 2013-10-28 09:38:37Z gcosmo $
//
/// \file B1EventAction.cc
/// \brief Implementation of the B1EventAction class

#include <iostream>

#include "B1EventAction.hh"
#include "B1Run.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include "MDataManager.h"
#include "MGeantTrack.h"

B1EventAction::B1EventAction(MDataManager* root)
: G4UserEventAction()
{
    data_manager = root;
}

B1EventAction::~B1EventAction()
{
    for (int i = 0; i < tracks.size(); ++i)
    {
        delete tracks[i];
    }
}

void B1EventAction::BeginOfEventAction(const G4Event* evt)
{
    // Get Event ID
    G4int evtNb = evt->GetEventID();
}

void B1EventAction::EndOfEventAction(const G4Event*)
{
    // fill tree with data acquired from current event
    MCategory * catGeantTrack = data_manager->getCategory(MCategory::CatGeantTrack);
    MLocator loc(1);

    for (size_t i = 0; i < tracks.size(); ++i)
    {
        loc[0] = i;

        MGeantTrack * track = (MGeantTrack *) catGeantTrack->getSlot(loc);
        track = new (track) MGeantTrack;
        
        *track = *tracks[i];
    }

    data_manager->fill();
}

MGeantTrack * B1EventAction::getTrack(Int_t track_num) const
{
    if (track_num < tracks.size())
        return tracks[track_num];
    else
        return nullptr;
}

MGeantTrack* B1EventAction::getParticle(int trackID) const
{
    for (int i = 0; i < tracks.size(); ++i)
    {
        if (tracks[i]->getTrackID() == trackID) {
            return tracks[i];
        }
    }

    std::cerr << "[Error] in MGeantSim getParticle(int trackID): no Particle with given ID found" << std::endl;
    return nullptr;
}
