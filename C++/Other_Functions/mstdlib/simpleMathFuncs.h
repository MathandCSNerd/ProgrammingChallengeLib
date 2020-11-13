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

#ifndef MATTSTDLIB_SIMPLE_MATH_H
#define MATTSTDLIB_SIMPLE_MATH_H

#include <limits.h>
#include <vector>

namespace mstdlib {

// simple math functions
template <class numType>
numType gcd(numType a, numType b);
template <class numType>
numType lcm(numType a, numType b);
template <class numType>
numType log(numType base, numType num);
// parralel assign
template <class numType>
void PAssign(numType& var1, numType& var2, numType val1, numType val2);
template <class numType>
std::vector<numType> xgcd(numType a, numType b);
template <class numType>
numType InverseMod(numType a, numType b);
// a higher precision pow function for numTypeegers
template <class numType>
numType IntPow(numType base, numType exp);
template <class numType>
numType pow(numType base, numType exp, numType mod);

}  // namespace mstdlib

#include "simpleMathFuncs.tcc"

#endif
