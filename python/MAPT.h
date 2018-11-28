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

#ifndef MAPT_H
#define MAPT_H

class MMAPTManager;
class MDetectorManager;
class MCategory;
class MGeantTrack;
class MGeantFibersRaw;
class MFibersCalSim;
class MFibersCal;

class MAPT
{
public:
    MAPT();
    virtual ~MAPT();

    int initAnalysis(const std::string & file, int events = 1000);
    long getEventsNumber() const { return ev_limit; }
    int getEvent(long i);
//     void printEvent() const;

    int getGeantTrackNum() const;
    int getGeantFibersRawNum() const;
    int getFibersCalSimNum() const;
    int getFibersCalNum() const;

    MGeantTrack * getGeantTrack(int i) const;
    MGeantFibersRaw * getGeantFibersRaw(int i) const;
    MFibersCalSim * getFibersCalSim(int i) const;
    MFibersCal * getFibersCal(int i) const;

    void fill();
    void save();

private:
    MMAPTManager * dataManager;
    MDetectorManager * detm;
    MCategory * catGeantTrack;
    MCategory * catGeantFibersRaw;
    MCategory * catFibersCalSim;

    long ev_limit;
};

#endif // MAPT_H
