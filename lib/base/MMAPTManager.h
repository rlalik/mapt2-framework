// @(#)lib/base:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef MMAPTMANAGER_H
#define MMAPTMANAGER_H

using namespace std;

#include <string>
#include <fstream>
#include <map>

#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"

#include "MCategory.h"

class MMAPTManager: public TObject
{
protected:
    // members
    TFile* outputFile;                          ///< Pointer to output file
    TTree* outputTree;                          ///< Pointer to output tree
    string outputTreeTitle;                     ///< Output tree title
    string outputTreeName;                      ///< Output tree name
    string outputFileName;                      ///< Output file name
    TChain* inputTree;                          ///< Pointer to input tree
    string inputTreeTitle;                      ///< Input tree title
    string inputTreeName;                       ///< Input tree name
    std::vector<std::string> inputFiles;        ///< Input file name
    int numberOfEntries;                        ///< Number of input entries
    int currentEntry;                           ///< Current input entry number

    /// Ctaegory info
    struct CategoryInfo
    {
        CategoryInfo();
        CategoryInfo(CategoryInfo & ci);

        bool registered = false;    ///< Category is registered
        bool persistent = false;    ///< Category is persistent
        MCategory::Cat cat;         ///< Category ID
        std::string name;           ///< Category name
        bool simulation;            ///< Simulation run
        size_t dim;                 ///< Dimension of ctageory
        size_t sizes[16];           ///< Sizes of dimension
        MCategory * ptr = nullptr;  ///< Pointer to category object
    };

    /// Category info array
    CategoryInfo cinfovec[MCategory::CatLimitDoNotUse * 2];

    typedef std::map<MCategory::Cat, MCategory *> CatMap;
    CatMap categories;              ///< Map of categories
    static MMAPTManager * mm;       ///< Instance of the MMAPTManager
    bool sim;                       ///< Simulation run
    bool branches_set;              ///< Has branches set

private:
    // constructor
    MMAPTManager();
    MMAPTManager(MMAPTManager const &) {}   ///< Copy constructor
    /// Assignment operator
    /// \return this object
    MMAPTManager & operator=(MMAPTManager const &) { return *this; }

public:
    // instance method
    static MMAPTManager * instance();

    // destructor
    virtual ~MMAPTManager() {};

    // methods
    void print() const;
    void clear();

    bool book();
    bool save();
    Int_t fill();
    bool open();

    void getEntry(int i);
    int getEntriesFast();

    void setSimulation(bool simulation);
    /// Check if simulation run
    /// \return is simulation
    bool isSimulation() const { return sim; }

    bool registerCategory(MCategory::Cat cat, std::string name, size_t dim, size_t * sizes, bool simulation);

    MCategory * buildCategory(MCategory::Cat cat, bool persistent = true);
    MCategory * getCategory(MCategory::Cat cat, bool persistent = true);
    MCategory * openCategory(MCategory::Cat cat, bool persistent = true);

    /// Set output file name
    /// \param file file name
    void setOutputFileName(const std::string & file) { outputFileName = file; }
    void setInputFileName(const std::string & file);
    void addInputFileName(const std::string & file);
    void setInputFileNames(const std::vector<std::string> & files);
    void addInputFileNames(const std::vector<std::string> & files);

    /// Get entry number
    /// \return entry number
    int getEntryNumber() { return currentEntry; }
    /// Get number of entries
    /// \return number of entries
    int getEntries() { return numberOfEntries; }

    /// Get input tree
    /// \return input tree
    TChain * getTree() const { return inputTree; }

private:
    void initBranches();

    ClassDef(MMAPTManager, 1);
};

extern MMAPTManager * mapt();

#endif /* DATAMANAGER_H */
