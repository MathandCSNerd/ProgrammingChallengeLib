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

#ifdef MATTSTDLIB_COUNTING_H

namespace mstdlib {

template <class numType>
numType Factorial(numType x) {
  numType sum = 1;
  for (numType i = x; i > 1; --i) sum *= i;
  return sum;
}

template <class numType>
numType NChoosek(numType n, numType k) {
  if (n < k) swap(n, k);
  return Factorial(n) / (Factorial(n - k) * Factorial(k));
}

template <class numType>
numType NPermk(numType n, numType k) {
  return Factorial(n) / (Factorial(n - k));
}

template <class numType>
numType PrecisenChoosek(numType n, numType k) {
  if (n < k) swap(n, k);

  numType m;
  if (k < n - k)
    m = (n - k);
  else
    m = k;

  k = n - m;
  numType sumn = 1;
  numType sumd = 1;

  numType i = m + 1, i2 = 1;
  while (i <= n && i2 <= k) {
    sumn *= i++;
    sumd *= i2++;
    Simplify(sumn, sumd);
  }
  return sumn / sumd;
}

template <class numType>
numType PrecisenPermk(numType n, numType k) {
  numType sum = 1;
  for (numType i = n; i > (n - k); --i) sum *= i;
  return sum;
}

template <class numType>
numType Binomial(numType k, numType n, numType p) {
  return powl(p, k) * powl(1 - p, n - k) * PrecisenChoosek(n, k);
}

}  // namespace mstdlib
#endif
