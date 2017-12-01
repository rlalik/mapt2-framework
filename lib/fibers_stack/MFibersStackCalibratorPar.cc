// @(#)lib/fibers_stack:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#include "MFibersStackCalibratorPar.h"

#include "MParContainer.h"

/** \class MFibersStackCalibratorPar
\ingroup lib_fibers_stack

A container for Fibers Stack Calibrator parameters

\sa MPar

*/

/** Clear parameters
 */
void MFibersStackCalibratorPar::clear()
{
    fAdcGain = 1.0;
    fAdcOffset = 0.0;
}

/** Get parameters
 * \sa MPar::getParams()
 * \param parcont pointer to container object
 * \return success
 */
bool MFibersStackCalibratorPar::getParams(MParContainer* parcont)
{
    if (!parcont->fill("fAdcGain", fAdcGain)) return false;
    if (!parcont->fill("fAdcOffset", fAdcOffset)) return false;
}

/** Put parameters
 * \sa MPar::putParams()
 * \param parcont pointer to container object
 * \return success
 */
bool MFibersStackCalibratorPar::putParams(MParContainer* parcont) const
{
}

/** Print parameters
 */
void MFibersStackCalibratorPar::print() const
{
    printf(" +++\n adc gain = %g\n", fAdcGain);
    printf(" adc offset = %g\n", fAdcOffset);
}
