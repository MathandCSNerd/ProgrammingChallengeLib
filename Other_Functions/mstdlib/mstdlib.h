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

#ifndef MATTSTDLIB_MSTDLIB_H
#define MATTSTDLIB_MSTDLIB_H
#include <limits.h>
#include <math.h>
#include <string.h>
#include <algorithm>
#include <iostream>

#include <list>
#include <set>
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

// simple common functions
template <class numType>
void swap(numType& a, numType& b);
// simplify fraction where a is the numerator and b is the denominator
template <class numType>
void Simplify(numType& a, numType& b);
template <class numType>
numType CountDigits(numType i);

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

// summing functions
template <class numType>
numType Sum(numType n);
template <class numType>
numType SquareSum(numType n);
template <class numType>
numType CubeSum(numType n);
template <class numType>
numType SumBy(numType n, numType m);

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

// other math functions
template <class numType>
numType DigitSum(numType x);
template <class numType>
numType SquareDigitSum(numType x);

//**********************
// misc/non-math section
//**********************

// returns true while there exists a nextiteration
// for use similar to next_permutation
bool IterateBin(bool* myarrbegin, bool* myarrend);

// in case you would rather have a string numTypeerface to iterate over
bool IterateStrin(std::string& str);

// like IterateBin, but uses $testarr as the upper bound and 0 as the lower
// bound
template <class numType>
bool IterateArr(numType* myarrbegin, numType* myarrend, numType* testarr);

// function for selecting n items from a group of k without replacement
// n = arr.size(), k = maxNum
// begining array is numbers 0 to k-1 in descending order
// ex, for choosin 3 from 5
// ChooseNFromK({2,1,0}, 5)
template <class numType>
bool ChooseNFromK(std::vector<numType>& arr, numType maxNum);

// takes an array, converts it to number
template <class numType>
numType MkNum(numType start, numType end, numType* myarr);

// takes a num, converts it to an array
template <class numType>
numType* MkArr(numType num, numType& size);

// concats number essentially creating a palindrome
// the second one deletes the last digit so as to include odd palindromes
template <class numType>
numType MkPalNum(numType x);
template <class numType>
numType MkPalNum2(numType x);

// reverses a number
template <class numType>
numType RevNum(numType x);

// checks is a number is a palindrome
template <class numType>
bool IsPal(numType x);

// converts a set to a vector...
// usefull if you need to iterate over a set multiple times while
// changing nothing
template <class numType>
std::vector<numType> SetToVec(std::set<numType>& myset);

// returns binary string representing the number, padded to padlen zeroes if
// requested I may want to consider switching to a string numTypeerface to allow
// for the less than operator... hmmm
template <class numType>
std::vector<bool> GetBinaryString(numType x, bool pad = false,
                                  size_t padlen = 0);

// return number represented by binary string
template <class numType>
numType FromBinaryString(const std::vector<bool>& binstr);

// here purely out of convinience
// probably going to make this a template
template <class numType>
bool IsInSet(numType x, std::set<numType>& mySet);

}  // namespace mstdlib

#include "mstdlib.tcc"

#endif
