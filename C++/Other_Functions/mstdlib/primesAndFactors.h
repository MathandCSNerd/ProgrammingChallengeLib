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

#ifndef MATTSTDLIB_PRIMES_AND_FACTORS_H
#define MATTSTDLIB_PRIMES_AND_FACTORS_H

#include <string.h>
#include <list>
#include <vector>

namespace mstdlib {

// primes and factoring
template <class numType>
bool FermatPrimalityTest(numType x);
template <class numType>
bool IsObviousNonPrime(numType x);
// trial-division based prime checker
template <class numType>
bool IsPrime(numType x);
// checks for x in primeSet
template <class numType>
bool IsPrime(numType x, const std::vector<numType>& primeSet);
// prime checker which builds a cache over time, uses single-argument IsPrime
template <class numType>
bool IsCachePrime(numType x);
// O(n^1.5) time, O(n/ln(n)) space
template <class numType>
std::vector<numType> ListPrimeSieve(numType MAX_NUM);
// sieve of Eratosthenes
template <class numType>
bool* ArrPrimeSieve(numType MAX_NUM);
template <class numType>
std::vector<numType> PrimeArrToVec(bool* parr, numType MAX_NUM);
template <class numType>
std::vector<numType> NormalPrimeSieve(numType MAX_NUM);
template <class numType>
std::pair<numType, numType> DoFactDiv(numType& x, const numType i);
template <class numType>
std::list<std::pair<numType, numType>> Factor(numType x);
// prime-based trial division factor. O(sqrt(n)) time
template <class numType>
std::list<std::pair<numType, numType>> PFactor(
    numType x, const std::vector<numType>& primeList);
// arg is factors
template <class numType>
numType EulerPhi(std::list<std::pair<numType, numType>>& l);
template <class numType>
numType EulerPhi(numType x);
template <class numType>
std::list<numType> FactorsToDivisors(std::list<std::pair<numType, numType>>& l);
template <class numType>
numType DivisorCount(numType x, const std::vector<numType>& primeList);
template <class numType>
numType DivisorCount(numType x);
template <class numType>
numType DivisorSum(numType x, const std::vector<numType>& primeList);
template <class numType>
numType DivisorSum(std::list<std::pair<numType, numType>>& l);

}  // namespace mstdlib

#include "primesAndFactors.tcc"

#endif
