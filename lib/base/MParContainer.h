/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2017  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MPARCONTAINER_H
#define MPARCONTAINER_H

#include <TArrayI.h>
#include <TArrayF.h>
#include <TArrayD.h>

#include <vector>
#include <map>

#include "MMAPTManager.h"

typedef std::pair<std::string, std::vector<std::string> > TypeDataField;
typedef std::map<std::string, TypeDataField> ParMap;

class MParContainer
{
public:
    MParContainer(const std::string & container);
    virtual ~MParContainer() {}

    virtual bool add(const std::string & name, Int_t val);
    virtual bool add(const std::string & name, Float_t val);
    virtual bool add(const std::string & name, Double_t val);
    virtual bool add(const std::string & name, const TArrayI & val);
    virtual bool add(const std::string & name, const TArrayF & val);
    virtual bool add(const std::string & name, const TArrayD & val);

    virtual bool fill(const std::string & name, Int_t & val);
    virtual bool fill(const std::string & name, Float_t & val);
    virtual bool fill(const std::string & name, Double_t & val);
    virtual bool fill(const std::string & name, TArrayI & val);
    virtual bool fill(const std::string & name, TArrayF & val);
    virtual bool fill(const std::string & name, TArrayD & val);

    bool initParam(const std::string & name, const std::string & type, const std::vector<std::string> & values);

    MMAPTManager * dm() { return MMAPTManager::instance(); }

    void setLineSplit(size_t n) { line_split = n; }

    void print();

private:
    ParMap parameters;
    std::string container;
    size_t line_split;
};

#endif // MPARCONTAINER_H
