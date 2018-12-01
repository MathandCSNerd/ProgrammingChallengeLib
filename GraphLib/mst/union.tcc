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

UnionFind::UnionFind(int x) {
  p = new int[x];
  rank = new int[x];
  size = x;
  for (int i = 0; i < size; ++i) MakeSet(i);
}

UnionFind::~UnionFind() {
  delete[] p;
  delete[] rank;
}

void UnionFind::MakeSet(int x) {
  p[x] = x;
  rank[x] = 0;
}

void UnionFind::Link(int x, int y) {
  if (rank[x] > rank[y])
    p[y] = x;
  else {
    p[x] = y;
    if (rank[x] == rank[y]) ++rank[y];
  }
}

int UnionFind::FindSet(int x) {
  if (x != p[x]) p[x] = FindSet(p[x]);
  return p[x];
}

void UnionFind::Union(int x, int y) { Link(FindSet(x), FindSet(y)); }

// for debugging purposes
#include <iostream>
void UnionFind::Print() {
  for (int i = 0; i < size; ++i) {
    std::cout << "i: " << i << '\t' << "p " << p[i] << '\t'
              << "rank: " << rank[i] << std::endl;
  }
}
