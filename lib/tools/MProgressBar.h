// @(#)lib/tools:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef MPROGRESSBAR_H
#define MPROGRESSBAR_H

#include <string>

class MProgressBar
{
protected:
    // members
    long int cnt_current;      ///< current counter
    long int cnt_previous;     ///< previous counter
    long int cnt_limit;        ///< counter limit
    int point_width;           ///< width of a point
    int bar_width;             ///< width of a bar
    bool new_bar;              ///< make new bar
    bool new_bar_line;         ///< make new bar line

    std::string line_prefix;   ///< line prefix
    char bar_p;                ///< ???
    char alarm_p;              ///< ???

public:
    // constructor
    MProgressBar(long int limit, int point_width = 500, int bar_width = 20);
    // destructor
    virtual ~MProgressBar() {}

    // methods
    void close();
    void setProgress(int current_location);

    MProgressBar & operator++();
    MProgressBar operator++(int);

    /// Set line prefix
    /// \param prefix prefix
    void setLinePrefix(const std::string & prefix) { line_prefix = prefix; }
    /// Get line prefix
    /// \return current line prefix
    std::string getLinePrefix() const { return line_prefix; }

    /// Set bar character
    /// \param p character
    void setBarCharacter(char p) { bar_p = p; }
    /// Set alarm character
    /// \param p character
    void setAlarmCharacter(char p) { alarm_p = p; }

private:
    void render();
};

#endif /* MPROGRESSBAR_H */
