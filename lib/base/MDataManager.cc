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
    numberOfEntries(-1), currentEntry(-1), branches_set(false)
{
}

void MDataManager::setSimulation(bool simulation)
{
    sim = simulation;
    if (sim)
    {
        // Here register all detector independen categories
        size_t sizes[1];
        sizes[0] = 200;
        registerCategory(MCategory::CatGeantTrack, "MGeantTrack", 1, sizes, true);
    }
}


bool MDataManager::book()
{
    // Create file and open it
    outputFile = new TFile(outputFileName.c_str(), "RECREATE");
    if (!outputFile->IsOpen())
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
    if (outputFile)
    {
        outputFile->cd();
        outputTree->Write();        // Writing the tree to the file
        outputFile->Close();        // and closing the tree (and the file)
        return true;
    }

    return false;
}


Int_t MDataManager::fill()
{
    if (!branches_set)
        initBranches();

    // clear the current event data
    for (CatMap::iterator it = categories.begin(); it != categories.end(); ++it)
    {
        it->second->compress();
    }

    // fill tree
    Int_t status = outputTree->Fill();
//     printf("Fill status = %d\n", status);

    return status;
}

bool MDataManager::open()
{
    inputFile = TFile::Open(inputFileName.c_str());
	if (inputFile == 0)
    {
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

bool MDataManager::registerCategory(MCategory::Cat cat, std::string name, size_t dim, size_t * sizes, bool simulation)
{
    int pos = cat * (1+(int)simulation);

    if (cinfovec[pos].registered == true)
        return false;

    CategoryInfo cinfo;
    cinfo.registered = true;
    cinfo.cat = cat;
    cinfo.name = name;
    cinfo.simulation = simulation;
    cinfo.dim = dim;
    for (int i = 0; i < dim; ++i)
        cinfo.sizes[i] = sizes[i];
    cinfo.ptr = nullptr;

    cinfovec[pos] = cinfo;

//     printf("Register category %d with name=%s\n", cat, cinfo.name.c_str());
    return true;
}

void MDataManager::initBranches()
{
    size_t limit = MCategory::CatLimitDoNotUse * 2;
    for (size_t i = 0; i < limit; ++i)
    {
        CategoryInfo cinfo = cinfovec[i];
        if (!cinfo.persistent)
            continue;

        outputTree->Branch(cinfo.ptr->getName(), cinfo.ptr, 16000, 2);
    }

    branches_set = true;
}

MCategory * MDataManager::buildCategory(MCategory::Cat cat, bool persistent)
{
    if (!outputTree)
        return gNullMCategoryPtr;

    int pos = cat * (1+(int)sim);

    CategoryInfo cinfo = cinfovec[pos];
    if (cinfo.registered == false)
        return gNullMCategoryPtr;

    cinfo.persistent = persistent;
    MCategory * cat_ptr = new MCategory(cinfo.name.c_str(), cinfo.dim, cinfo.sizes, cinfo.simulation);
    cinfo.ptr = cat_ptr;
    cat_ptr->print();

    if (cat_ptr)
    {
        categories[cat] = cat_ptr;
        cinfovec[pos] = cinfo;

//         outputTree->Branch(cat_ptr->getName(), cinfo.ptr, 16000, 2);

        return cat_ptr;
    }

    return gNullMCategoryPtr;
}

MCategory * MDataManager::getCategory(MCategory::Cat cat, bool persistent)
{
    int pos = cat * (1+(int)sim);
    CategoryInfo cinfo = cinfovec[pos];
    if (cinfo.registered == false)
        return gNullMCategoryPtr;
    if (cinfo.ptr)
        return cinfo.ptr;
    MCategory * c = openCategory(cat, persistent);
    if (c)
        return c;

    return gNullMCategoryPtr;
}

MCategory * MDataManager::openCategory(MCategory::Cat cat, bool persistent)
{
    if (!inputTree)
        return gNullMCategoryPtr;

    int pos = cat * (1+(int)sim);

    CategoryInfo cinfo = cinfovec[pos];
    if (cinfo.registered == false)
    {
        fprintf(stderr, "Category %s (%d) not registered!\n", cinfo.name.c_str(), cat);
        return gNullMCategoryPtr;
    }

    MCategory ** cat_ptr = new MCategory*;

    *cat_ptr = new MCategory;
    TBranch * br = inputTree->GetBranch(cinfo.name.c_str());
    if (!br)
    {
        fprintf(stderr, "Category %s (%d) does not exists!\n", cinfo.name.c_str(), cat);
        return gNullMCategoryPtr;
    }
    br->SetAddress(&*cat_ptr);

    cinfo.persistent = persistent;
    if (cat_ptr)
    {
        cinfo.ptr = *cat_ptr;
        cinfovec[pos] = cinfo;

        categories[cat] = *cat_ptr;
        return *cat_ptr;
    }
    else
        return gNullMCategoryPtr;
}

void MDataManager::getEntry(int i)
{
    if (!inputTree)
    {
        std::cerr << "[Warning] in MDataManager: no input tree is opened. cannot get any entry." << "\n";
        return;
    }

    if (i < numberOfEntries)
    {
        currentEntry = i;
        inputTree->GetEntry(i);
    }
}

int MDataManager::getEntriesFast ()
{
    if (!inputTree)
    {
        std::cerr << "[Warning] in MDataManager: no input tree is opened. cannot get any entry." << "\n";
        return -1;
    }
    numberOfEntries = inputTree->GetEntriesFast();
    return numberOfEntries;
}

void MDataManager::print() const
{
    outputFile->cd();
    printf("There are %d categories in the output tree\n", categories.size());
    for (CatMap::const_iterator it = categories.begin(); it != categories.end(); ++it)
    {
        it->second->print();
    }
}

void MDataManager::clear()
{
    for (CatMap::const_iterator it = categories.begin(); it != categories.end(); ++it)
    {
        it->second->clear();
    }
}

MDataManager::CategoryInfo::CategoryInfo()
{
    registered = false;
    persistent = false;
    ptr = nullptr;
}

MDataManager::CategoryInfo::CategoryInfo(MDataManager::CategoryInfo& ci)
{
    registered = ci.registered;
    cat = ci.cat;
    name = ci.name;
    simulation = ci.simulation;
    dim = ci.dim;
    for (int i = 0; i < 16; ++i)
        sizes[i] = ci.sizes[i];
    persistent = ci.persistent;
    ptr = ci.ptr;
}
