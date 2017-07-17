#include "MDataManager.h"

#include "MCategory.h"

#include <iostream>

MCategory * gNullMCategoryPtr = 0;

// Needed for Creation of shared libs
ClassImp(MDataManager);

MDataManager * MDataManager::dm = nullptr;

MDataManager * MDataManager::instance()
{
    if (!dm)
        dm = new MDataManager;

    return dm;
}

MDataManager::MDataManager() :
    outputFile(nullptr), outputTree(nullptr), outputTreeTitle("M"), outputTreeName("M"), outputFileName("output.root"),
    inputFile(nullptr), inputTree(nullptr), inputTreeTitle("M"), inputTreeName("M"), inputFileName("input.root"),
    numberOfEntries(-1), currentEntry(-1)
{
}

bool MDataManager::book()
{
    // Create file and open it
    outputFile = new TFile(outputFileName.c_str(), "RECREATE");
    if(!outputFile)
    {
        std::cerr  << "[Error] in MDataManager: could not create saveFile" << std::endl;
        return false;
    }

    // Create tree
    outputTree = new TTree(outputTreeName.c_str(), outputTreeTitle.c_str());

    return true;
}

bool MDataManager::save()
{
    if (outputFile) {
        outputFile->cd();
        outputTree->Write();        // Writing the tree to the file
        outputFile->Close();        // and closing the tree (and the file)
        return true;
    }
    return false;
}


bool MDataManager::fill()
{
    // clear the current event data
    for (CatMap::iterator it = categories.begin(); it != categories.end(); ++it)
    {
        it->second->Compress();
    }

    // fill tree
    outputTree->Fill();

    return true;
}

bool MDataManager::open()
{
    inputFile = TFile::Open(inputFileName.c_str());
	if (inputFile == 0) {
		std::cerr << "[Error] in MDataManager: cannot open ROOT file" << "\n";
		return false;
	}
	inputTree = (TTree*) inputFile->Get(inputTreeName.c_str());
    if (!inputTree) {
        std::cerr << "[Error] in MDataManager open: openTree == NULL" << "\n";
        return false;
    }

    numberOfEntries = inputTree->GetEntriesFast();
    return true;
}

bool MDataManager::buildCategory(MCategory::Cat cat)
{
    if (!outputTree)
        return false;

    CatMap::iterator it = categories.find(cat);
    if (it != categories.end())
        return true;

    MCategory * cat_ptr = nullptr;
    size_t sizes[10];

    switch (cat)
    {
        case MCategory::CatGeantTrack:
            sizes[0] = 100;
            cat_ptr = new MCategory("MGeantTrack", 1, sizes, true);
            break;
        case MCategory::CatGeantFibersRaw:
            sizes[0] = 1;
            sizes[1] = 30;
            sizes[2] = 30;
            cat_ptr = new MCategory("MGeantFibersRaw", 3, sizes, true);
            break;
        case MCategory::CatFibersRaw:
            sizes[0] = 1;
            sizes[1] = 30;
            sizes[2] = 30;
            if (!sim)
                cat_ptr = new MCategory("FibersRaw", 3, sizes, false);
            break;
        case MCategory::CatFibersCal:
            sizes[0] = 1;
            sizes[1] = 30;
            sizes[2] = 30;
            if (sim)
                cat_ptr = new MCategory("FibersCal", 3, sizes, true);
            else
                cat_ptr = new MCategory("FibersCalSim", 1, sizes, false);
            break;
        default:
            break;
    }

    printf("My name is %s\n", cat_ptr->GetName());

    if (cat_ptr)
    {
        categories[cat] = cat_ptr;
        return outputTree->Branch(cat_ptr->getName().c_str(), cat_ptr, 16000, 0);
    }

    return false;
}

MCategory *& MDataManager::getCategory(MCategory::Cat cat)
{
    CatMap::iterator it = categories.find(cat);
    if (it != categories.end())
        return it->second;

    return gNullMCategoryPtr;
}

MCategory *& MDataManager::openCategory(MCategory::Cat cat)
{
    if (!inputTree)
        return gNullMCategoryPtr;

    MCategory * cat_ptr = 0;

    switch (cat)
    {
        case MCategory::CatGeantTrack:
            cat_ptr = new MCategory;
            inputTree->GetBranch("MGeantTrack")->SetAddress(&*cat_ptr);
            break;
        case MCategory::CatGeantFibersRaw:
            cat_ptr = new MCategory;
            inputTree->GetBranch("MGeantFibersRaw")->SetAddress(&*cat_ptr);
            break;
        default:
            break;
    }
}

void MDataManager::getEntry (int i)
{
    if (!inputTree)
    {
        std::cerr << "[Warning] in MDataManager: no input tree is opened. cannot get any entry." << "\n";
        return;
    }

    if (i < numberOfEntries)
    {
        currentEntry = i;

//         for (CatMap::iterator it = categories.begin(); it != categories.end(); ++it)
//             it->second->clear();

        inputTree->GetEntry(i);
    }
}

int MDataManager::getEntriesFast () {
    if (!inputTree) {
        std::cerr << "[Warning] in MDataManager: no input tree is opened. cannot get any entry." << "\n";
        return -1;
    }
    numberOfEntries = inputTree->GetEntriesFast();
    return numberOfEntries;
}
