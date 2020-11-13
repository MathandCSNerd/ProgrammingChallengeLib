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

#ifndef MATTSTDLIB_MISCMATH_H
#define MATTSTDLIB_MISCMATH_H
#include "simpleMathFuncs.h"

namespace mstdlib {
// simple common functions
template <class numType>
void swap(numType& a, numType& b);
// simplify fraction where a is the numerator and b is the denominator
template <class numType>
void Simplify(numType& a, numType& b);
template <class numType>
numType CountDigits(numType i);

// summing functions
template <class numType>
numType Sum(numType n);
template <class numType>
numType SquareSum(numType n);
template <class numType>
numType CubeSum(numType n);
template <class numType>
numType SumBy(numType n, numType m);

// other math functions
template <class numType>
numType DigitSum(numType x);
template <class numType>
numType SquareDigitSum(numType x);

}  // namespace mstdlib

#include "miscMath.tcc"

#endif
