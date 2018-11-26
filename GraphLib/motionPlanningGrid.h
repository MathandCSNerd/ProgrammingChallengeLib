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

#ifndef MOTION_PLANNING_GRID
#define MOTION_PLANNING_GRID

#include "containers/coordinates.h"
#include "containers/infNumClass.h"
#include "containers/multiDimMatrix.h"

template <class weightType>
class MotionPlanningGrid {
 public:
  class iterator;

  MotionPlanningGrid(const MatCoords& coord);
  MotionPlanningGrid(const MotionPlanningGrid& that);
  long long Size() const;
  long long NumDims() const { return maze.NumDimensions(); }
  long long DimSize(int dim) const { return maze.DimSize(dim); }

  weightType& Access(const MatCoords& coord);
  const weightType& Get(const MatCoords& coord) const;
  weightType& operator()(const MatCoords& coord);
  bool ObstacleAt(const MatCoords& coord) const;

  iterator begin(MatCoords coord) const;
  iterator end(MatCoords coord) const;

  void Print() { maze.Print(); }

 private:
  MotionPlanningGrid();
  MultidimensionalMatrix<InfNum<weightType>> maze;
};

// TODO: expand this to allow diagonal directions as well
//       maybe also a SetDiagonal(true/false) function?
// notes: n-dimensional grid nodes have 2n directions
//        without diagonals and 2(n^2) directions with.
template <class weightType>
class MotionPlanningGrid<weightType>::iterator {
 private:
  MatCoords curCoord;
  // index just holds the current iteration step
  // from the current node.
  int index;
  MotionPlanningGrid<weightType> const* data;

 public:
  const long long Dim(int i) { return curCoord.Get(i); }
  const long long CDim(int i) const { return curCoord.Get(i); }

  void CalcIndexCoords(MatCoords& coord) const;

  MatCoords Node() const;
  const weightType& Weight() const;
  iterator();
  iterator(int newIndex, MatCoords newNode,
           const MotionPlanningGrid<weightType>* dataPtr);

  iterator& operator=(const iterator& that);

  iterator(const iterator& that);

  const iterator* operator->() const;

  bool operator==(const iterator& that) const;
  bool operator!=(const iterator& that) const;

  bool ValidIterator() const;
  iterator& operator++();
};

#include "motionPlanningGrid.tcc"

#endif
