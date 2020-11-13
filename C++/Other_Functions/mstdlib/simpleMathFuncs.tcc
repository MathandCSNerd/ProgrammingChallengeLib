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

#ifdef MATTSTDLIB_SIMPLE_MATH_H

namespace mstdlib {

//**************************
// simple math functions
//**************************
template <class numType>
numType gcd(numType a, numType b) {
  if (!b)
    return a;
  else
    return gcd(b, a % b);
}

template <class numType>
numType lcm(numType a, numType b) {
  if (a || b) {
    numType tmp = a * b;
    if (tmp < 0) tmp *= -1;
    return tmp / gcd(a, b);
  } else {
    return 0;
  }
}

template <class numType>
numType log(numType base, numType num) {
  return log10l(num) / log10l(base);
}

template <class numType>
void PAssign(numType& var1, numType& var2, numType val1, numType val2) {
  var1 = val1;
  var2 = val2;
}

template <class numType>
std::vector<numType> xgcd(numType a, numType b) {
  using namespace std;
  vector<numType> vec;
  numType s = 0, old_s = 1;
  numType t = 1, old_t = 0;
  numType r = b, old_r = a;
  numType q;
  while (r) {
    q = old_r / r;
    PAssign(old_r, r, r, old_r - q * r);
    PAssign(old_s, s, s, old_s - q * s);
    PAssign(old_t, t, t, old_t - q * t);
  }
  vec.push_back(old_r);
  vec.push_back(old_s);
  vec.push_back(old_t);
  return vec;
}

template <class numType>
numType InverseMod(numType a, numType b) {
  auto l = xgcd(a, b);
  if (l[1] < 0) l[1] += b;
  return l[1];
}

template <class numType>
numType IntPow(numType base, numType exp) {
  // return (numType)(floorl(powl(base, exp) + 0.5));
  return pow(base, exp, ULLONG_MAX);
}

template <class numType>
numType pow(numType base, numType exp, numType mod) {
  if (base < 1) return 0;
  if (!exp) return 1;
  numType curr = base, result = 1;

  while (exp) {
    if (exp % 2) result = (result * curr) % mod;
    exp /= 2;
    curr = (curr * curr) % mod;
  }
  return result;
}

}  // namespace mstdlib

#endif
