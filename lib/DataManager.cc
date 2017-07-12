#include "DataManager.hh"

#include "Category.hh"
#include "GeantSim.h"

#include <iostream>

// Needed for Creation of shared libs
ClassImp(DataManager);

DataManager::DataManager()
{
    saveTreeTitle   = "saveTreeTitle";
    saveTreeName    = "saveTreeName";
    saveFileName    = "saveFileName.root";
    openTreeTitle   = "saveTreeTitle";
    openTreeName    = "saveTreeName";
    openFileName    = "saveFileName.root";
    geant_sim = nullptr;
    numberOfEntries = -1;
    currentEntry = -1;
}

bool DataManager::buildCategory(DataManager::Cat cat)
{
    if (!saveTree)
        return false;

    switch (cat)
    {
        case CatGeantSim:
            if (!geant_sim)
                geant_sim = new GeantSim;
            return saveTree->Branch("GeantSim", "GeantSim*", geant_sim, 16000, 0);
            break;
        case CatData:
            break;
        case CatFilter:
            break;
    }
}

bool DataManager::book(string path)
{
    saveFileName = path;
    return book();
}

bool DataManager::book()
{
    // Create file and open it
    saveFile = new TFile(saveFileName.c_str(), "RECREATE");
    if(!saveFile)
    {
        std::cerr  << "[Error] in DataManager: could not create saveFile" << std::endl;
        return false;
    }

    // Create tree
    saveTree = new TTree(saveTreeName.c_str(),saveTreeTitle.c_str());

    return true;
}

bool DataManager::save()
{
    if (saveFile) {
        saveFile->cd();
        saveTree->Write();        // Writing the tree to the file
        saveFile->Close();        // and closing the tree (and the file)
        return true;
    }
    return false;
}


bool DataManager::fill()
{
    // fill tree
    saveTree->Fill();
    // clear the current event data
    if (geant_sim) geant_sim->clear();
    return true;
}


Category * DataManager::getCategory(Cat cat)
{
    switch (cat)
    {
        case CatGeantSim:
            return geant_sim;
            break;
        case CatData:
            return nullptr;
            break;
        case CatFilter:
            return nullptr;
            break;
    }

    return nullptr;
}


bool DataManager::open(string path)
{
    openFileName = path;
    openFile = TFile::Open(openFileName.c_str());
	if (openFile == 0) {
		std::cerr << "[Error] in DataManager: cannot open ROOT file" << "\n";
		return false;
	}
	openTree = (TTree*) openFile->Get(openTreeName.c_str());
    if (!openTree) {
        std::cerr << "[Error] in DataManager open: openTree == NULL" << "\n";
        return false;
    }

    numberOfEntries = openTree->GetEntriesFast();
    return true;
}

bool DataManager::openCategory(DataManager::Cat cat)
{
    if (!saveTree)
        return false;

    switch (cat)
    {
        case CatGeantSim:
            openTree->GetBranch("GeantSim")->SetAddress(&geant_sim);
            break;
        case CatData:
            break;
        case CatFilter:
            break;
    }
}

void DataManager::getEntry (int i) {
    if (!openTree) {
        std::cerr << "[Warning] in DataManager: no input tree is opened. cannot get any entry." << "\n";
        return;
    }
    if (i < numberOfEntries) {
        currentEntry = i;
        if (geant_sim) geant_sim->clear();
        openTree->GetEntry(i);
    }
}



int DataManager::getEntriesFast () {
    if (!openTree) {
        std::cerr << "[Warning] in DataManager: no input tree is opened. cannot get any entry." << "\n";
        return -1;
    }
    numberOfEntries = openTree->GetEntriesFast();
    return numberOfEntries;
}
