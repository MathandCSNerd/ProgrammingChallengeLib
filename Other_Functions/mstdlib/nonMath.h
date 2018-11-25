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

#ifndef MATTSTDLIB_NONMATH_H
#define MATTSTDLIB_NONMATH_H

#include <set>
#include <vector>

namespace mstdlib {

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

#include "nonMath.tcc"

#endif
