#ifndef DATAMANAGER_H
#define DATAMANAGER_H

using namespace std;

#include <string>
#include <fstream>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

class Event;

//! \brief Access point to load, read and write data.
/*!
  The DataManager is responsible to manage all data operations. It loads a root
  tree from specified file.
*/
class DataManager: public TObject
{
public:
    //! \brief Constructor.
    DataManager();
    virtual ~DataManager() {};

    //! \brief Creates a new file at the provided path and creates an empty root tree with Event objects as leafs.
    bool book(string path);

    //! \brief Creates a new file and an empty root tree with Event objects as leafs.
    bool book();

    //! \brief Writes the tree to file and close it.
    bool save();

    //! \brief Fills the current event attribute into the tree.
    bool fill();

    //! \brief Opens a file and loads the root tree.
    bool open(string path);

    //! \brief Reads entry i of the current tree. The event attribute is filled with the event information saved in tree entry i.
    void getEntry(int i);

    //! \brief Returns number of entries in the current tree.
    int getEntriesFast();

    //! \brief Returns the currently loaded event instance.
    Event* getEvent();

    void setSaveFileName(string s) { saveFileName = s; }
    void setSaveTreeName(string s) { saveTreeName = s; }
    void setSaveTreeTitle(string s) { saveTreeTitle = s; }
    void setOpenFileName(string s) { openFileName = s; }
    void setOpenTreeName(string s) { openTreeName = s; }
    void setOpenTreeTitle(string s) { openTreeTitle = s; }

    int getCurrentEntryNumber() { return currentEntry; }
    int getNumberOfEntries() { return numberOfEntries; }

    //! \brief Needed for creation of shared library
    ClassDef(DataManager, 2);

private:
    // file and tree to save the events
    TFile* saveFile;
    //! \brief The save tree.
    TTree* saveTree;
    string saveTreeTitle;
    string saveTreeName;
    string saveFileName;

    // for opening a file with an event tree
    TFile* openFile;
    //! \brief The open tree.
    TTree* openTree;
    string openTreeTitle;
    string openTreeName;
    string openFileName;
    int numberOfEntries;
    int currentEntry;

    //! \brief The currently loaded event instance.
    /*!
        This variable represents the current event. It is filled with the event
        information from the opening tree entry. Calling DataManager::fill writes
        this instance to the save tree.
    */
    Event* event;
};

#endif /* DATAMANAGER_H */
