#ifndef MMAPTMANAGER_H
#define MMAPTMANAGER_H

using namespace std;

#include <string>
#include <fstream>
#include <map>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

#include "MCategory.h"

//! \brief Access point to load, read and write data.
/*!
  The MMAPTManager is responsible to manage all data operations. It loads a root
  tree from specified file.
*/
class MMAPTManager: public TObject
{
private:
    //! \brief Constructor.
    MMAPTManager();
    MMAPTManager(MMAPTManager const &) {}
    MMAPTManager & operator=(MMAPTManager const &) { return *this; }

public:
    static MMAPTManager * instance();

    virtual ~MMAPTManager() {};

    void print() const;
    void clear();

    //! \brief Creates a new file and an empty root tree with Event objects as leafs.
    bool book();

    //! \brief Writes the tree to file and close it.
    bool save();

    //! \brief Fills the current event attribute into the tree.
    Int_t fill();

    //! \brief Opens a file and loads the root tree.
    bool open();

    //! \brief Reads entry i of the current tree. The event attribute is filled with the event information saved in tree entry i.
    void getEntry(int i);

    //! \brief Returns number of entries in the current tree.
    int getEntriesFast();

    void setSimulation(bool simulation);
    bool isSimulation() const { return sim; }

    bool registerCategory(MCategory::Cat cat, std::string name, size_t dim, size_t * sizes, bool simulation);

    MCategory * buildCategory(MCategory::Cat cat, bool persistent = true);
    MCategory * getCategory(MCategory::Cat cat, bool persistent = true);
    MCategory * openCategory(MCategory::Cat cat, bool persistent = true);

    void setOutputFileName(string s) { outputFileName = s; }
    void setInputFileName(string s) { inputFileName = s; }

    int getCurrentEntryNumber() { return currentEntry; }
    int getNumberOfEntries() { return numberOfEntries; }

private:
    void initBranches();

    //! \brief Needed for creation of shared library
    ClassDef(MMAPTManager, 1);

private:
    // file and tree to save the events
    TFile* outputFile;
    //! \brief The save tree.
    TTree* outputTree;
    string outputTreeTitle;
    string outputTreeName;
    string outputFileName;

    // for opening a file with an event tree
    TFile* inputFile;
    //! \brief The open tree.
    TTree* inputTree;
    string inputTreeTitle;
    string inputTreeName;
    string inputFileName;
    int numberOfEntries;
    int currentEntry;

    struct CategoryInfo
    {
        CategoryInfo();
        CategoryInfo(CategoryInfo & ci);

        bool registered = false;
        bool persistent = false;
        MCategory::Cat cat;
        std::string name;
        bool simulation;
        size_t dim;
        size_t sizes[16];
        MCategory * ptr = nullptr;
    };

    CategoryInfo cinfovec[MCategory::CatLimitDoNotUse * 2];

    typedef std::map<MCategory::Cat, MCategory *> CatMap;
    CatMap categories;
    static MMAPTManager * dm;
    bool sim;
    bool branches_set;
};

#endif /* DATAMANAGER_H */
