/* Copyright 2018 Matthew Macallister
 *
 * This file is part of ProgrammingChallengeLib.
 *
 * ProgrammingChallengeLib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ProgrammingChallengeLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ProgrammingChallengeLib.  If not, see <https://www.gnu.org/licenses/>.
 */

/*
 *  mstdlib.h
 *
 *  Copyright (C) 2018 Matthew Mac Allister
 *
 *  This file contains declarations for some standard math functions
 *  as well as a couple others.
 */

#ifndef MATTSTDLIB_MSTDLIB_H
#define MATTSTDLIB_MSTDLIB_H
#include <math.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <iostream>

#include <list>
#include <set>
#include <vector>

namespace mstdlib{


// simple math functions
long long gcd(long long a, long long b);
long long lcm(long long a, long long b);
long double log(long double base, long double num);
// parralel assign
void PAssign(long long& var1, long long& var2, long long val1, long long val2);
std::vector<long long> xgcd(long long a, long long b);
long long InverseMod(long long a, long long b);
//a higher precision pow function for integers
unsigned long long IntPow(unsigned long long base, unsigned long long exp);
unsigned long long pow(unsigned long long base, unsigned long long exp, unsigned long long mod);

// simple common functions
void swap(long long& a, long long& b);
// simplify fraction where a is the numerator and b is the denominator
void Simplify(long long& a, long long& b);
int CountDigits(unsigned long long i);

// counting functions
long long Factorial(int x);
long long NChoosek(long long n, long long k);
long long NPermk(long long n, long long k);
//less naive counting functions, which can be used on higher values
long long PrecisenChoosek(long long n, long long k);
long long PrecisenPermk(long long n, long long k);
// binomial dist pmf
long double Binomial(int k, int n, long double p);

// summing functions
long long Sum(long long n);
long long SquareSum(long long n);
long long CubeSum(long long n);
long long SumBy(long long n, long long m);

// primes and factoring
bool FermatPrimalityTest(long long x);
bool IsObviousNonPrime(long long x);
// trial-division based prime checker
bool IsPrime(long long x);
// checks for x in primeSet
bool IsPrime(long long x, const std::vector<long long>& primeSet);
// prime checker which builds a cache over time, uses single-argument IsPrime
bool IsCachePrime(int x);
// O(n^1.5) time, O(n/ln(n)) space
std::vector<long long> ListPrimeSieve(long long MAX_NUM);
// sieve of Eratosthenes
bool* ArrPrimeSieve(long long MAX_NUM);
std::vector<long long> PrimeArrToVec(bool* parr, long long MAX_NUM);
std::vector<long long> NormalPrimeSieve(long long MAX_NUM);
std::pair<long long, long long> DoFactDiv(long long& x, const long long i);
std::list<std::pair<long long, long long>> Factor(long long x);
// prime-based trial division factor. O(sqrt(n)) time
std::list<std::pair<long long, long long>> PFactor(
    long long x, const std::vector<long long>& primeList);
// arg is factors
long long EulerPhi(std::list<std::pair<long long, long long>>& l);
long long EulerPhi(long long x);
std::list<long long> FactorsToDivisors(
    std::list<std::pair<long long, long long>>& l);
long long DivisorCount(long long x, const std::vector<long long>& primeList);
long long DivisorCount(long long x);
long long DivisorSum(long long x, const std::vector<long long>& primeList);
long long DivisorSum(std::list<std::pair<long long, long long>>& l);

// figurate numbers functions
// Get___X: gets candidate for the figurate root of number
// ___SumN: calculates figurate sum of number
// Is___  : returns whether or not the number is of that figure's type
long long GetOctX(long long i);
long long OctSumN(long long i);
long long GetHeptX(long long i);
long long HeptSumN(long long i);
long long GetHexX(long long i);
long long HexSumN(long long i);
long long GetPentX(long long i);
long long PentSumN(long long i);
long long GetTriX(long long i);
long long TriSumN(long long i);
bool IsOct(long long i);
bool IsHept(long long i);
bool IsHex(long long i);
bool IsPent(long long i);
bool IsTri(long long i);
bool IsSquare(long long i);

// other math functions
long long DigitSum(long long x);
long long SquareDigitSum(long long x);

//**********************
// misc/non-math section
//**********************

// returns true while there exists a nextiteration
// for use similar to next_permutation
bool IterateBin(bool* myarrbegin, bool* myarrend);

// in case you would rather have a string interface to iterate over
bool IterateStrin(std::string& str);

// like IterateBin, but uses $testarr as the upper bound and 0 as the lower
// bound
bool IterateArr(long long* myarrbegin, long long* myarrend, long long* testarr);

//function for selecting n items from a group of k without replacement
//n = arr.size(), k = maxNum
//begining array is numbers 0 to k-1 in descending order
//ex, for choosin 3 from 5
//ChooseNFromK({2,1,0}, 5)
bool ChooseNFromK(std::vector<int>& arr, int maxNum);

// takes an array, converts it to number
long long MkNum(int start, int end, int* myarr);

// takes a num, converts it to an array
int* MkArr(unsigned long long num, int& size);

// concats number essentially creating a palindrome
// the second one deletes the last digit so as to include odd palindromes
unsigned long long MkPalNum(unsigned long long x);
unsigned long long MkPalNum2(unsigned long long x);

// reverses a number
unsigned long long RevNum(unsigned long long x);

// checks is a number is a palindrome
bool IsPal(unsigned long long x);

// converts a set to a vector...
// usefull if you need to iterate over a set multiple times while
// changing nothing
std::vector<long long> SetToVec(std::set<long long>& myset);

// returns binary string representing the number, padded to padlen zeroes if
// requested I may want to consider switching to a string interface to allow
// for the less than operator... hmmm
std::vector<bool> GetBinaryString(long long x, bool pad = false,
                                  size_t padlen = 0);

// return number represented by binary string
long long FromBinaryString(const std::vector<bool>& binstr);

//here purely out of convinience
//probably going to make this a template
bool IsInSet(long long x, std::set<long long>& mySet);

} // namespace mstdlib

#endif
