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

#ifndef MATTSTDLIB_FIGURATES_H
#define MATTSTDLIB_FIGURATES_H

namespace mstdlib {

// figurate numbers functions
// Get___X: gets candidate for the figurate root of number
// ___SumN: calculates figurate sum of number
// Is___  : returns whether or not the number is of that figure's type
template <class numType>
numType GetOctX(numType i);
template <class numType>
numType OctSumN(numType i);
template <class numType>
numType GetHeptX(numType i);
template <class numType>
numType HeptSumN(numType i);
template <class numType>
numType GetHexX(numType i);
template <class numType>
numType HexSumN(numType i);
template <class numType>
numType GetPentX(numType i);
template <class numType>
numType PentSumN(numType i);
template <class numType>
numType GetTriX(numType i);
template <class numType>
numType TriSumN(numType i);
template <class numType>
bool IsOct(numType i);
template <class numType>
bool IsHept(numType i);
template <class numType>
bool IsHex(numType i);
template <class numType>
bool IsPent(numType i);
template <class numType>
bool IsTri(numType i);
template <class numType>
bool IsSquare(numType i);

}  // namespace mstdlib

#include "figurates.tcc"

#endif
