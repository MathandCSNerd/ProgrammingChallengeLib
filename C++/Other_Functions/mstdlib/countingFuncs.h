/* Copyright 2018 Matthew Macallister
 *
 * This file is part of ProgrammingChallengeLib.
 *
 * ProgrammingChallengeLib is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ProgrammingChallengeLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ProgrammingChallengeLib.  If not, see
 * <https://www.gnu.org/licenses/>.
 */

#ifndef MATTSTDLIB_COUNTING_H
#define MATTSTDLIB_COUNTING_H

#include <math.h>
#include "miscMath.h"

namespace mstdlib {

// counting functions
template <class numType>
numType Factorial(numType x);
template <class numType>
numType NChoosek(numType n, numType k);
template <class numType>
numType NPermk(numType n, numType k);
// less naive counting functions, which can be used on higher values
template <class numType>
numType PrecisenChoosek(numType n, numType k);
template <class numType>
numType PrecisenPermk(numType n, numType k);
// binomial dist pmf
template <class numType>
numType Binomial(numType k, numType n, numType p);

}  // namespace mstdlib

#include "countingFuncs.tcc"

#endif
