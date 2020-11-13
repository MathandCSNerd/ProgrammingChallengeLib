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

#ifndef UNION_FIND
#define UNION_FIND

#include <vector>

class UnionFind {
 public:
  UnionFind(int x);
  void MakeSet(int x);
  void Link(int x, int y);
  int FindSet(int x);
  void Union(int x, int y);
  void Print();  // for debugging

 private:
  std::vector<int> p;
  std::vector<int> rank;
  int size;
};

#include "union.tcc"

#endif
