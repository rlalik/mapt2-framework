#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>

#include <TObject.h>

class TObject;

//! \brief Data structure representing an event.
/*!
  Contains all information of an event. Also the MC truth is saved here.
*/
class Category: public TObject
{
public:
    Category();
    virtual ~Category();

    void clear();

    // Needed for creation of shared library
    ClassDef(Category, 1);

};

#endif /* CATEGORY_H */
