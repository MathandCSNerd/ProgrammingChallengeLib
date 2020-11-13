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

#ifdef MATTSTDLIB_FIGURATES_H

namespace mstdlib {

//**************************
// figurate numbers functions
//**************************
template <class numType>
numType GetOctX(numType i) {
  return ceil(sqrt(float(i) / 3));
}
template <class numType>
numType OctSumN(numType i) {
  return i * (3 * i - 2);
}

template <class numType>
numType GetHeptX(numType i) {
  return ceil(sqrt(float(i) * float(2) / 5));
}
template <class numType>
numType HeptSumN(numType i) {
  return (i * (5 * i - 3)) / 2;
}

template <class numType>
numType GetHexX(numType i) {
  return ceil(sqrt(float(i) / 2));
}
template <class numType>
numType HexSumN(numType i) {
  return 2 * i * i - i;
}

template <class numType>
numType GetPentX(numType i) {
  return ceil(sqrt(float(i) * float(2) / 3));
}
template <class numType>
numType PentSumN(numType i) {
  return (3 * (i * i) - i) / 2;
}

template <class numType>
numType GetTriX(numType i) {
  return floor(sqrt(i * 2));
}
template <class numType>
numType TriSumN(numType i) {
  return ((i * (i + 1)) / 2);
}

template <class numType>
bool IsOct(numType i) {
  numType temp = GetOctX(i);
  return OctSumN(temp) == i;
}
template <class numType>
bool IsHept(numType i) {
  numType temp = GetHeptX(i);
  return HeptSumN(temp) == i;
}
template <class numType>
bool IsHex(numType i) {
  numType temp = GetHexX(i);
  return HexSumN(temp) == i;
}
template <class numType>
bool IsPent(numType i) {
  numType temp = GetPentX(i);
  return PentSumN(temp) == i;
}
template <class numType>
bool IsTri(numType i) {
  numType temp = GetTriX(i);
  return TriSumN(temp) == i;
}
template <class numType>
bool IsSquare(numType i) {
  numType temp = sqrt(i);
  return (temp * temp) == i;
}

}  // namespace mstdlib

#endif
