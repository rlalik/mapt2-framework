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

#include <iostream>
#include <sstream>

#include "MParContainer.h"

MParContainer::MParContainer(const std::string& container) : container(container)
{
}

bool MParContainer::add(const std::string & name, Int_t val)
{
    std::stringstream buff;
    buff << "  " << val;
    std::vector<std::string> v;
    v.push_back(buff.str());
    parameters[name] = TypeDataField("Int_t", v);

    return true;
}

bool MParContainer::add(const std::string & name, Float_t val)
{
    std::stringstream buff;
    buff << "  " << val;
    std::vector<std::string> v;
    v.push_back(buff.str());
    parameters[name] = TypeDataField("Float_t", v);

    return true;
}

bool MParContainer::add(const std::string & name, Double_t val)
{
    std::stringstream buff;
    buff << "  " << val;
    std::vector<std::string> v;
    v.push_back(buff.str());
    parameters[name] = TypeDataField("Double_t", v);

    return true;
}

bool MParContainer::add(const std::string & name, const TArrayI & val)
{
    std::stringstream buff;
    std::vector<std::string> v;
    for (int i = 0; i < val.GetSize(); ++i)
    {
        buff << "  " << val[i];
        v.push_back(buff.str());
    }
    parameters[name] = TypeDataField("Int_t", v);

    return true;
}

bool MParContainer::add(const std::string & name, const TArrayF & val)
{
   std::stringstream buff;
   std::vector<std::string> v;
    for (int i = 0; i < val.GetSize(); ++i)
    {
        buff << "  " << val[i];
        v.push_back(buff.str());
    }
    parameters[name] = TypeDataField("Float_t", v);

    return true;
}

bool MParContainer::add(const std::string & name, const TArrayD & val)
{
    std::stringstream buff;
    std::vector<std::string> v;
    for (int i = 0; i < val.GetSize(); ++i)
    {
        buff << "  " << val[i];
        v.push_back(buff.str());
    }
    parameters[name] = TypeDataField("Double_t", v);

    return true;
}

bool MParContainer::fill(const std::string & name, Int_t& val)
{
    ParMap::const_iterator it = parameters.find(name);

    if (it == parameters.end())
    {
        std::cerr << "Parameter name " << name << " doesn't exists in the container!" << std::endl;
        return false;
    }
    if (it->second.first != "Int_t")
    {
        std::cerr << "Incorrect type for parameter name " << name << std::endl;
        return false;
    }

    std::stringstream buff(it->second.second[0]);
    buff >> val;

    return true;
}

bool MParContainer::fill(const std::string & name, Float_t& val)
{
    ParMap::const_iterator it = parameters.find(name);

    if (it == parameters.end())
    {
        std::cerr << "Parameter name " << name << " doesn't exists in the container!" << std::endl;
        return false;
    }
    if (it->second.first != "Float_t")
    {
        std::cerr << "Incorrect type for parameter name " << name << std::endl;
        return false;
    }

    std::stringstream buff(it->second.second[0]);
    buff >> val;

    return true;
}

bool MParContainer::fill(const std::string & name, Double_t& val)
{
    ParMap::const_iterator it = parameters.find(name);

    if (it == parameters.end())
    {
        std::cerr << "Parameter name " << name << " doesn't exists in the container!" << std::endl;
        return false;
    }
    if (it->second.first != "Double_t")
    {
        std::cerr << "Incorrect type for parameter name " << name << std::endl;
        return false;
    }

    std::stringstream buff(it->second.second[0]);
    buff >> val;

    return true;
}

bool MParContainer::fill(const std::string & name, TArrayI& val)
{
    ParMap::const_iterator it = parameters.find(name);

    if (it == parameters.end())
    {
        std::cerr << "Parameter name " << name << " doesn't exists in the container!" << std::endl;
        return false;
    }
    if (it->second.first != "Int_t")
    {
        std::cerr << "Incorrect type for parameter name " << name << std::endl;
        return false;
    }

    for (int i = 0; i < it->second.second.size(); ++i)
        val[i] = stoi(it->second.second[i].c_str());

    return true;
}

bool MParContainer::fill(const std::string & name, TArrayF& val)
{
    ParMap::const_iterator it = parameters.find(name);

    if (it == parameters.end())
    {
        std::cerr << "Parameter name " << name << " doesn't exists in the container!" << std::endl;
        return false;
    }
    if (it->second.first != "Float_t")
    {
        std::cerr << "Incorrect type for parameter name " << name << std::endl;
        return false;
    }

    for (int i = 0; i < it->second.second.size(); ++i)
        val[i] = stof(it->second.second[i].c_str());

    return true;
}

bool MParContainer::fill(const std::string & name, TArrayD& val)
{
    ParMap::const_iterator it = parameters.find(name);

    if (it == parameters.end())
    {
        std::cerr << "Parameter name " << name << " doesn't exists in the container!" << std::endl;
        return false;
    }
    if (it->second.first != "Double_t")
    {
        std::cerr << "Incorrect type for parameter name " << name << std::endl;
        return false;
    }

    for (int i = 0; i < it->second.second.size(); ++i)
        val[i] = stod(it->second.second[i].c_str());

    return true;
}

void MParContainer::print()
{
    printf("Container [%s]\n", container.c_str());
    ParMap::const_iterator it = parameters.begin();
    for (; it != parameters.end(); ++it)
    {
        printf("%s:  %s", it->first.c_str(), it->second.first.c_str());
        for (int i = 0; i < it->second.second.size(); ++i)
        {
            printf("  %s", it->second.second[i].c_str());
        }
        putchar('\n');
    }
}

bool MParContainer::initParam(const std::string& name, const std::string& type, const std::vector<std::string> & values)
{
    parameters[name] = TypeDataField(type, values);
}
