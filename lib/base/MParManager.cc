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

#include <algorithm> 
#include <cctype>
#include <fstream>
#include <iostream>
#include <locale>
#include <sstream>

#include "MPar.h"

#include "MParManager.h"
#include "MParContainer.h"
#include "MPar.h"

// for trim functions see
// https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}


void simplify(std::string & s)
{
    size_t pos = 0;
    while(1)
    {
        pos = s.find_first_of('\t', pos);
        if (pos == s.npos)
            return;
        s.replace(pos, 1, " ");
    }
}

// see stackoverflow #447206
bool isFloat(const string & str)
{
    std::istringstream iss(str);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail();
}

MParManager * MParManager::tm = nullptr;

MParManager * MParManager::instance()
{
    if (!tm)
        tm = new MParManager;

    return tm;
}

MParManager::MParManager()
{
}

MParManager::~MParManager()
{
}

bool MParManager::parseSource()
{
    ifstream ifs(source);
    size_t length = 0;
    if (ifs)
    {
        ifs.seekg(0, ifs.end);
        length = ifs.tellg();
        ifs.seekg(0, ifs.beg);
    }

    char * cbuff = new char[length];

    WhatNext wn = WNContainer;

    std::string cont_name;
    std::string param_name;
    std::string type_name;
    std::vector<std::string> values;

    while(!ifs.eof())
    {
        ifs.getline(cbuff, length);

        std::string str(cbuff);
        trim(str);
        simplify(str);

        size_t pos = 0, pos2 = 0;

        // check if comment or empty line
        if (str[0] == '#' or (str.length() == 0 and wn != WNParamCont))
        {
            continue;
        }
        // if container mark found, check whether it should be there, e.g. container after param new line is forbidden
        else if (str[0] == '[')
        {
            if (wn == WNContainer or wn == WNContainerOrParam)
            {
                pos = str.find_first_of(']', 1);
                cont_name = str.substr(1, pos-1);
//                 printf("Found container %s\n", cont_name.c_str());

                containers.insert(std::pair<std::string, MParContainer *>(cont_name, new MParContainer(cont_name)));

                param_name.clear();

                wn = WNContainerOrParam;
                continue;
            }
            else
            {
                std::cerr << "Didn't expected container here: " << std::endl << str << std::endl;
                return false;
            }
        }
        else
        {
            // check if container name
            if (wn == WNContainer)
            {
                std::cerr << "Expected container name here: " << std::endl << str << std::endl;
                return false;
            }
            else if (wn == WNParam or wn == WNContainerOrParam)
            {
                // find parameter name ended with :
                pos = str.find_first_of(':', 1);
                param_name = str.substr(0, pos);
                trim(param_name);

                // prepare other variables
                type_name.clear();
                values.clear();

                // find type name
                pos = str.find_first_not_of(' ', pos+1);

                // type name must be in the same line like param name
                if (str[pos] == '\\')
                {
                    std::cerr << "No type name detected in the param name line:" << std::endl << str << std::endl;
                    return false;
                }
                pos2 = str.find_first_of(' ', pos+1);

                type_name = str.substr(pos, pos2-pos);
                if (type_name != "Int_t" and type_name != "Float_t" and type_name != "Double_t")
                {
                    std::cerr << "Invalid param type '" << type_name << "' in line:" << std::endl << str << std::endl;
                    return false;
                }

//                 printf("Found param=%s with type=%s\n", param_name.c_str(), type_name.c_str());

                wn = WNParamCont;
            }

            if (wn == WNParamCont)
            {
//                 printf("Search for values in %s\n", str.substr(pos2, -1).c_str());
                wn = parseValues(str.substr(pos2, -1), values);
                if (wn == WNContainerOrParam)
                {
                    if (values.size() == 0)
                    {
                        std::cerr << "No values given in line:" << std::endl << str << std::endl;
                        return false;
                    }
                    else
                    {
                        containers[cont_name]->initParam(param_name, type_name, values);
                    }
                }
            }
        }
    }

    return true;
}

MParManager::WhatNext MParManager::parseValues(const std::string & str, std::vector<std::string> & values)
{
    size_t pos = 0, pos2 = 0;

    while(1)
    {
        pos = str.find_first_not_of(' ', pos2);
//         printf("Found %c at %d\n", str[pos], pos);
        // if new line detected
        if (str[pos] == '\\')
        {
            return WNParamCont;
        }

        // if end of line
        if (pos == str.npos)
        {
            break;
        }

        pos2 = str.find_first_of(' ', pos+1);
        std::string match = str.substr(pos, pos2-pos);
        if (isFloat(match))
        {
            values.push_back(match);
        }
        else
        {
            std::cerr << "Value is not a number:" << std::endl << str << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    return WNContainerOrParam;
}

void MParManager::writeDestination() const
{
}

void MParManager::print() const
{
     std::map<std::string, MParContainer *>::const_iterator it = containers.begin();
     for (; it != containers.end(); ++it)
         it->second->print();
}

bool MParManager::addParameterContainer(const std::string& cont_name, MPar* parcont)
{
    MParContainer * pc = containers[cont_name];
    if (!pc)
    {
        std::cerr << "Container " << cont_name << " doesn't exists!" << std::endl;
        exit(EXIT_FAILURE);
    }

    parcont->clear();
    bool ret = parcont->getParams(pc);
    if (!ret)
    {
        std::cerr << "Initialization of " << cont_name << " param container failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    parconts.insert(std::pair<std::string, MPar*>(cont_name, parcont));
    return true;
}

MPar * MParManager::getParameterContainer(const std::string& cont_name)
{
    return parconts[cont_name];
}
