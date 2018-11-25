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

#ifdef MATTSTDLIB_MISCMATH_H

namespace mstdlib {

//**************************
// simple common functions
//**************************
template <class numType>
void swap(numType& a, numType& b) {
  numType tmp(a);
  a = b;
  b = tmp;
}

template <class numType>
void Simplify(numType& a, numType& b) {
  numType tmp = gcd(a, b);
  a /= tmp;
  b /= tmp;
}

template <class numType>
numType CountDigits(numType i) {
  numType ret = (ceil(log10l(i)));
  if (ret == (log10l(i))) ++ret;
  return ret;
}

//**************************
// summing functions
//**************************
template <class numType>
numType Sum(numType n) {
  return (n * (n + 1)) / 2;
}

template <class numType>
numType SquareSum(numType n) {
  return (n * (n + 1) * (2 * n + 1)) / 6;
}

template <class numType>
numType CubeSum(numType n) {
  return (n * n * (n + 1) * (n + 1)) / 4;
}

template <class numType>
numType SumBy(numType n, numType m) {
  return m * Sum(n / m);
}

//**************************
// other math functions
//**************************
template <class numType>
numType DigitSum(numType x) {
  numType sum = 0;
  while (x) {
    sum += (x % 10);
    x /= 10;
  }
  return sum;
}

template <class numType>
numType SquareDigitSum(numType x) {
  numType sum = 0;
  while (x) {
    sum += (x % 10) * (x % 10);
    x /= 10;
  }
  return sum;
}

}  // namespace mstdlib

#endif
