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

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include "../countingSort.h"

using namespace std;

long long aunt(const int& lol) { return lol + 1; }

class mytype {
 public:
  long long ToInt() const { return a; }
  operator long long() const { return a; }
  typedef int Use;

 private:
  long long a;
};

long long aunt2(const mytype& that) {
  // return (long long)that;
  return that.ToInt();
}

int main() {
  srand(time(NULL));

  // creates a random vector v
  std::vector<int> v(100);
  for (auto& it : v) it = rand() % 100;

  // v2 is now a copy of v
  std::vector<int> v2(v);

  // sorts v with std::sort
  sort(v.begin(), v.end());
  // sorts v2 with CountingSort using aunt as the function for
  // returning the integer representation of our vector elements.
  // This is a redundant example to be sure, but it's just a
  // demonstration.
  CountingSort(v2.begin(), v2.end(), aunt);

  // creates and sorts a new vector v3 of mytype with 5 items
  //
  // I don't care what items are inside because I just want
  // to demonstrate the ability to call counting sort with
  // user-defined data types.
  std::vector<mytype> v3(5);
  CountingSort(v3.begin(), v3.end());

  // this loop makes sure the vectors v1 (sorted with std::sort) and
  // v2 (sorted with counting sort) match to demonstrate the
  // counting sort succeded
  int count = 0;
  for (size_t i = 0; i < v.size(); ++i) count += v[i] != v2[i];
  cout << count << " elements don't match" << endl;

  return 0;
}
