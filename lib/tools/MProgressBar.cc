// @(#)lib/tools:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#include "MProgressBar.h"

#include <iostream>

/** \class MProgressBar
\ingroup lib_tools

Display progress of the analysis.

*/

/** Constructor
 * \param cnt_limit limit of the bar
 * \param point_width width of the point
 * \param bar_width width of teh bar
 */
MProgressBar::MProgressBar(long int cnt_limit, int point_width, int bar_width) :
    cnt_current(0), cnt_previous(0), cnt_limit(cnt_limit),
    point_width(point_width), bar_width(bar_width),
    new_bar(true), new_bar_line(true),
    bar_p('.'), alarm_p('!')
{
    line_prefix = "==> Processing data ";
}

/** Close bar line
 */
void MProgressBar::close()
{
    std::cout << std::endl;
}

/** Set current progress status
 * \param current_location current position
 */
void MProgressBar::setProgress(int current_location)
{
    cnt_current = current_location;
    render();
}

/** Increase progress
 */
MProgressBar & MProgressBar::operator++()
{
    ++cnt_current;
    render();

    return *this;
}

/** Increase progress
 */
MProgressBar MProgressBar::operator++(int)
{
    MProgressBar pb(*this);
    ++(*this);

    return pb;
}

/** Render bar
 */
void MProgressBar::render()
{
    for (long int i = cnt_previous; i < cnt_current; ++i)
    {
        if (new_bar or new_bar_line)
        {
            std::cout << line_prefix << std::flush;
            new_bar = false;
            new_bar_line = false;
        }

        if (i != 0  and ( (i+1) % point_width ) == 0)
        {
            if (i < cnt_limit)
                std::cout << bar_p << std::flush;
            else
                std::cout << alarm_p << std::flush;
        }

        if ((i != 0  and (i+1) % (point_width * bar_width) == 0) or
            (i == (cnt_limit-1)))
        {
            double num_percent = 100.0*(i+1)/cnt_limit;
            std::cout << " " << i+1 << " (" << num_percent << "%) " << "\n" << std::flush;

            new_bar_line = true;
        }
    }

    cnt_previous = cnt_current;
}
