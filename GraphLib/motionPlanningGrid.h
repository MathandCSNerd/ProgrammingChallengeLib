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

#include "containers/infNumClass.h"
#include "coords.h"

// TODO: expand to have an arbitrary number of dimensions
template <class weightType>
class MotionPlanningGrid {
 public:
  class iterator;

  MotionPlanningGrid();
  ~MotionPlanningGrid();
  MotionPlanningGrid(const Coordinates<long long>& coord);
  MotionPlanningGrid(const MotionPlanningGrid& that);
  void ChangeSize(const Coordinates<long long>& coord);
  long long Size() const;
  long long RowSize() const { return rowsize; };
  long long ColSize() const { return colsize; };
  // long long DimSize(int dim) const;

  long long CoordsToIndex(const Coordinates<long long>& coord) const;
  weightType& Access(const Coordinates<long long>& coord);
  weightType& Get(const Coordinates<long long>& coord) const;
  weightType& operator()(const Coordinates<long long>& coord);
  bool ObstacleAt(const Coordinates<long long>& coord) const;

  iterator begin(Coordinates<long long> coord) const;
  iterator end(Coordinates<long long> coord) const;

 private:
  long long rowsize;
  long long colsize;
  InfNum<weightType>* maze;
};

// TODO: expand this to allow diagonal directions as well
//       maybe also a SetDiagonal(true/false) function?
// notes: n-dimensional grid nodes have 2n directions
//        without diagonals and 2(n^2) directions with.
template <class weightType>
class MotionPlanningGrid<weightType>::iterator {
 private:
  Coordinates<long long> curCoord;
  // index just holds the current iteration step
  // from the current node.
  // It might be a good idea to change it to a
  // size_t in the future, but I don't even have
  // multidimensional Grids finished so it's
  // pointless to think about now.
  int index;
  MotionPlanningGrid<weightType> const* data;

 public:
  const long long Row() { return curCoord.Row(); }
  const long long Col() { return curCoord.Col(); }
  const long long CRow() const { return curCoord.CRow(); }
  const long long CCol() const { return curCoord.CCol(); }

  void CalcIndexCoords(Coordinates<long long>& coord) const;

  Coordinates<long long> Node() const;
  const weightType& Weight() const;
  iterator();
  iterator(int newIndex, Coordinates<long long> newNode,
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
