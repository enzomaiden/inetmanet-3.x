//
// Copyright (C) 2013 OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef __INET_IDEALANALOGMODEL_H
#define __INET_IDEALANALOGMODEL_H

#include "inet/physicallayer/contract/IAnalogModel.h"

namespace inet {

namespace physicallayer {

/**
 * Implements the IdealAnalogModel model, see the NED file for details.
 */
class INET_API IdealAnalogModel : public cModule, public IAnalogModel
{
  public:
    virtual void printToStream(std::ostream& stream) const;
    virtual const IReception *computeReception(const IRadio *radio, const ITransmission *transmission, const IArrival *arrival) const;
    virtual const INoise *computeNoise(const IListening *listening, const IInterference *interference) const;
    virtual const ISNIR *computeSNIR(const IReception *reception, const INoise *noise) const;
};

} // namespace physicallayer

} // namespace inet

#endif // ifndef __INET_IDEALANALOGMODEL_H
