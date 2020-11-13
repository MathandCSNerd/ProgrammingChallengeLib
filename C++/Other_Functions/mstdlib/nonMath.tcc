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

#ifdef MATTSTDLIB_NONMATH_H

namespace mstdlib {

//**************************
// non math functions
//**************************
bool IterateBin(bool* myarrbegin, bool* myarrend) {
  bool* i;

  // the only reason for this loop is retaining the final case
  for (i = myarrbegin; i < myarrend && (*i); ++i)
    ;

  if (i == myarrend)
    return false;

  else {
    (*i) = 1;
    for (--i; i >= myarrbegin; --i) (*i) = 0;
  }
  return true;
}

bool IterateStrin(std::string& str) {
  size_t i;

  for (i = 0; i < str.length() && (str[i] == '1'); ++i)
    ;

  if (i == str.length())
    return false;

  else {
    str[i] = '1';
    if (i) {
      for (--i; i >= 1; --i) str[i] = '0';
      str[0] = '0';
    }
  }
  return true;
}

template <class numType>
bool IterateArr(numType* myarrbegin, numType* myarrend, numType* testarr) {
  numType* i;

  for (i = myarrbegin; i < myarrend && (*i == *(i - myarrbegin + testarr)); ++i)
    ;

  if (i == myarrend)
    return false;

  else {
    ++(*(i - myarrbegin + testarr));
    for (--i; i >= myarrbegin; --i) (*(i - myarrbegin + testarr)) = 0;
  }
  return true;
}

template <class numType>
bool ChooseNFromK(std::vector<numType>& arr, numType maxNum) {
  size_t i;

  for (i = 0; i < arr.size() && (arr[i] >= (maxNum - i - 1)); ++i)
    ;

  if (i == arr.size())
    return false;

  else {
    ++arr[i];
    if (i) {
      for (--i; i >= 1; --i) arr[i] = arr[i + 1] + 1;
      if (arr.size() > 1) arr[0] = arr[1] + 1;
    }
  }
  return true;
}

template <class numType>
numType MkNum(numType start, numType end, numType* myarr) {
  numType num = 0;
  --start;
  while (++start <= end) {
    num *= 10;
    num += myarr[start];
  }
  return num;
}

template <class numType>
numType* MkArr(numType num, numType& size) {
  numType len = CountDigits(num);
  size = len;
  numType* digits = new numType[len];

  numType i = len;
  while (num) {
    digits[--i] = num % 10;
    num /= 10;
  }
  return digits;
}

template <class numType>
numType MkPalNum(numType x) {
  numType num = x;
  while (x) {
    num *= 10;
    num += x % 10;
    x /= 10;
  }
  return num;
}

template <class numType>
numType MkPalNum2(numType x) {
  numType num = x;
  x /= 10;
  while (x) {
    num *= 10;
    num += x % 10;
    x /= 10;
  }
  return num;
}

template <class numType>
numType RevNum(numType x) {
  numType num = 0;
  while (x) {
    num *= 10;
    num += x % 10;
    x /= 10;
  }
  return num;
}

template <class numType>
bool IsPal(numType x) {
  return RevNum(x) == x;
}

template <class numType>
std::vector<numType> SetToVec(std::set<numType>& myset) {
  using namespace std;
  vector<numType> myvec(myset.size());
  copy(myset.begin(), myset.end(), myvec.begin());
  return myvec;
}

template <class numType>
std::vector<bool> GetBinaryString(numType x, bool pad, size_t padlen) {
  using namespace std;
  vector<bool> vec, retvec;
  while (x) {
    vec.push_back(x % 2);
    x /= 2;
  }
  if (pad)
    while (vec.size() + retvec.size() < padlen) retvec.push_back(0);
  while (vec.size()) {
    retvec.push_back(vec.back());
    vec.pop_back();
  }
  return retvec;
}

template <class numType>
numType FromBinaryString(const std::vector<bool>& binstr) {
  numType retval = 0;

  for (auto it : binstr) {
    retval *= 2;
    retval += it;
  }
  return retval;
}

template <class numType>
bool IsInSet(numType x, std::set<numType>& mySet) {
  return mySet.find(x) != mySet.end();
}

}  // namespace mstdlib

#endif
