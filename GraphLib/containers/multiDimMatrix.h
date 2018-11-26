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

// This is an n-dimensional Matrix class for use the motion planning
// grid class

#ifndef MULTIDIMENSIONAL_MATRIX
#define MULTIDIMENSIONAL_MATRIX
#include "coordinates.h"

// typedef Coordinates<size_t> MatCoords;
typedef Coordinates<long long> MatCoords;

template <class type>
class MultidimensionalMatrix {
 public:
  ~MultidimensionalMatrix();
  MultidimensionalMatrix(const MatCoords& coords);
  MultidimensionalMatrix(const MultidimensionalMatrix<type>& that);
  const MultidimensionalMatrix& operator=(
      const MultidimensionalMatrix<type>& that);

  const type& Get(const MatCoords& coords) const;
  void Set(const MatCoords& coords, const type& val);
  type& Access(const MatCoords& coords);
  type& operator()(const MatCoords& coords);

 private:
  // these are the current internal methods, not to be used
  // outside the class
  const type& GetIndex(int x) const;
  void SetIndex(size_t x, const type& val);
  type& AccessIndex(size_t x);
  type& operator()(size_t x);

 public:
  MatCoords GetDims() const { return dimensions; }
  size_t NumDimensions() const;
  size_t DimSize(size_t x) const;
  size_t TotalSize() const;
  void SetAll(const type& that);

  // printing:
  size_t PrintRow(size_t startIndex, size_t count) const;
  size_t PrintSlice(size_t startIndex, size_t rowcount, size_t colCount) const;
  size_t Print3D() const;
  size_t Print() const;

 private:
  MultidimensionalMatrix();
  // I'm setting this to private because I'm considering toying around
  // with some template metaprogramming for this class in the future.
  // I would rather not expose an interface only to take it away, so
  // I'm avoiding doing do.
  void AllocSize(MatCoords newDims);
  void ReCalculateIndexMultipliers();
  size_t CoordsToIndex(const MatCoords& coords) const;
  // bool IterateCoords(MatCoords myarr);

  MatCoords dimensions;
  MatCoords indexMultipliers;
  type* arr;
};

#include "multiDimMatrix.tcc"

#endif
