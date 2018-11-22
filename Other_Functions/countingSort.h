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

#ifndef COUNTING_SORT
#define COUNTING_SORT

#include <algorithm>
#include <iterator>
#include <vector>

namespace CountingSortInternal {

// if the class is a non-integral type, it has to be explicitly
// castable to a long long or else a seperate function need to be
// provided for that purpose
// Of course, the return value should be an order identifier
template <typename CountableType>
long long ToIntT(const CountableType& a) {
  return (long long)a;
}

template <class CountableType>
bool CountingSortCmp(const CountableType& a, const CountableType& b) {
  return ToIntT(a) < ToIntT(b);
}

}  // namespace CountingSortInternal

// So that I could drop a call to this sort into code using the stl
// sort, I wrote it with a similar function signature. This, however,
// meant I had to change the algorithm to move items to a working
// array and copy them back into the source array rather than the
// usual definition of the algorithm requiring an output array.
template <typename RandomAccessIterator>
void CountingSort(
    RandomAccessIterator first, RandomAccessIterator last,
    // ToIntFunc is a function of the form: long long f(const mytype& x);
    // where mytype is whatever the type of (*first) is a reference to.
    //
    // Yes this seems a very roundabout way of writing that,
    // but it's the best way I've found to add a cv qualifier to decltype
    long long (*ToIntFunc)(
        const typename std::remove_reference<decltype(*first)>::type&)) {
  using namespace std;
  using namespace CountingSortInternal;

  // find max value to determine size of counting array
  long long myMax =
      ToIntFunc(*max_element(first, last,
                             CountingSortCmp<decay_t<decltype(*first)>>)) +
      1;

  // temp vector for moving elements into order
  vector<decay_t<decltype(*first)>> workVec;
  // vector to hold counts of values
  vector<long long> counts;

  workVec.resize(distance(first, last));
  counts.resize(myMax);

  // creation of counting array
  for (auto& it : counts) it = 0;
  for (auto it = first; it != last; ++it) ++counts[ToIntFunc(*it)];
  for (size_t i = 1; i < counts.size(); ++i) counts[i] += counts[i - 1];

  // initial sorting of items into working vector
  for (auto it = last - 1; it >= first; --it) {
    --counts[ToIntFunc(*it)];
    workVec[counts[ToIntFunc(*it)]] = move(*it);
  }

  // moving items back to original vector
  for (size_t i = 0; first + i < last; ++i) *(first + i) = move(workVec[i]);
}

template <typename RandomAccessIterator>
void CountingSort(RandomAccessIterator first, RandomAccessIterator last) {
  CountingSort(first, last, CountingSortInternal::ToIntT);
}

#endif
