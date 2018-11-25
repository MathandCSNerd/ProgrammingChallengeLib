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
  MotionPlanningGrid(long long newRowSize, long long newColSize);
  MotionPlanningGrid(const MotionPlanningGrid& that);
  void ChangeSize(long long newRowSize, long long newColSize);
  long long Size() const;
  long long RowSize() const { return rowsize; };
  long long ColSize() const { return colsize; };

  long long CoordsToIndex(const CoordinatePair<long long>& coord) const;
  weightType& Access(const CoordinatePair<long long>& coord);
  weightType& Get(const CoordinatePair<long long>& coord) const;
  weightType& operator()(const CoordinatePair<long long>& coord);
  weightType& operator()(long long row, long long col);
  bool ObstacleAt(const CoordinatePair<long long>& coord) const;

  iterator begin(CoordinatePair<long long> coord) const;
  iterator end(CoordinatePair<long long> coord) const;

 private:
  long long rowsize;
  long long colsize;
  InfNum<weightType>* maze;
};

// TODO: expand this to allow diagonal directions as well
//       maybe also a SetDiagonal(true/false) function?
template <class weightType>
class MotionPlanningGrid<weightType>::iterator {
 private:
  CoordinatePair<long long> curCoord;
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

  void CalcIndexCoords(CoordinatePair<long long>& coord) const;

  CoordinatePair<long long> Node() const;
  const weightType& Weight() const;
  iterator();
  iterator(int newIndex, CoordinatePair<long long> newNode,
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
