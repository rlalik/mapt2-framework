// @(#)lib/fibers_stack:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#include "MFibersStackDigitizerPar.h"

#include "MParContainer.h"

/** \class MFibersStackDigitizerPar
\ingroup lib_fibers_stack

A container for Fibers Stack Digitizer parameters

\sa MPar

*/

/** Get parameters
 * \sa MPar::getParams()
 * \param parcont pointer to container object
 * \return success
 */
bool MFibersStackDigitizerPar::getParams(MParContainer* parcont)
{
    return true;
}

/** Put parameters
 * \sa MPar::putParams()
 * \param parcont pointer to container object
 * \return success
 */
bool MFibersStackDigitizerPar::putParams(MParContainer* parcont) const
{
    return true;
}

/** Clear parameters
 */
void MFibersStackDigitizerPar::clear()
{
}
