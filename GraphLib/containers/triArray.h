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

#ifndef TRI_ARRAY
#define TRI_ARRAY
#include "genericArray.h"

template <class type>
class TriangularArray : public GenericArray<type> {
 public:
  int CalcRSize(int n) const { return (n * (n + 1)) / 2; }

  int CoordsToIndex(int row, int col) const {
    if (row > col) std::swap(row, col);

    return (GenericArray<type>::RSize() - 1) -
           CalcRSize(GenericArray<type>::size - row) + (col - row + 1);
  }
};

#endif
