#include "DataManager.hh"

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
    event = 0;
    numberOfEntries = -1;
    currentEntry = -1;
}

bool DataManager::book(string path) {
    saveFileName = path;
    // Create file and open it
    saveFile = new TFile(saveFileName.c_str(), "RECREATE");
    if(!saveFile) {
        std::cerr  << "[Error] in DataManager: could not create saveFile" << std::endl;
        return false;
    }

    if(!event) {
        event = new Event();
    }
    event->clear();

    // Create tree
    saveTree = new TTree(saveTreeName.c_str(),saveTreeTitle.c_str());

    // Add branches
    saveTree->Branch("Event","Event*",event,16000,0);

    return true;
}

bool DataManager::book() {
    // Create file and open it
    saveFile = new TFile(saveFileName.c_str(), "RECREATE");
    if(!saveFile) {
        std::cerr  << "[Error] in DataManager: could not create saveFile" << std::endl;
        return false;
    }

    if(!event) {
        event = new Event();
    }
    event->clear();

    // Create tree
    saveTree = new TTree(saveTreeName.c_str(),saveTreeTitle.c_str());

    // Add branches
    saveTree->Branch("Event","Event*",event,16000,0);

    return true;
}



bool DataManager::save() {
    if (saveFile) {
        saveFile->cd();
        saveTree->Write();        // Writing the tree to the file
        saveFile->Close();        // and closing the tree (and the file)
        return true;
    }
    return false;
}


bool DataManager::fill() {
    // fill tree
    saveTree->Fill();
    // clear the current event data
    event->clear();
    return true;
}


Event* DataManager::getEvent() {
    return event;
}


bool DataManager::open(string path) {

    // if openTree already exists. delete it.
    // if (!openTree) {
    //      openFile->Close ();
    //      delete openTree;
    //      delete openFile;
    //      openTree = NULL;
    //      openFile = NULL;
    // }

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
    event = 0;
    openTree->GetBranch("Event")->SetAddress(&event);

    numberOfEntries = openTree->GetEntriesFast();
    return true;
}


void DataManager::getEntry (int i) {
    if (!openTree) {
        std::cerr << "[Warning] in DataManager: no input tree is opened. cannot get any entry." << "\n";
        return;
    }
    if (i < numberOfEntries) {
        currentEntry = i;
        event->clear();
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
