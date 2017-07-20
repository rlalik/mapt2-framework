#ifndef DATAMANAGER_H
#define DATAMANAGER_H

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
  The MDataManager is responsible to manage all data operations. It loads a root
  tree from specified file.
*/
class MDataManager: public TObject
{
private:
    //! \brief Constructor.
    MDataManager();
    MDataManager(MDataManager const &) {}
    MDataManager & operator=(MDataManager const &) {}

public:
    static MDataManager * instance();

    virtual ~MDataManager() {};

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

    void setSimulation(bool simulation) { sim = simulation; }

    bool registerCategory(MCategory::Cat cat, std::string name, size_t dim, size_t * sizes, bool simulation);

    MCategory * buildCategory(MCategory::Cat cat);
    MCategory * getCategory(MCategory::Cat cat);
    MCategory * openCategory(MCategory::Cat cat);

    void setOutputFileName(string s) { outputFileName = s; }
    void setInputFileName(string s) { inputFileName = s; }

    int getCurrentEntryNumber() { return currentEntry; }
    int getNumberOfEntries() { return numberOfEntries; }

    //! \brief Needed for creation of shared library
    ClassDef(MDataManager, 1);

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
        bool registered = false;
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
    static MDataManager * dm;
    bool sim;
};

#endif /* DATAMANAGER_H */
