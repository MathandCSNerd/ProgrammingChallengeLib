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

#ifdef MOTION_PLANNING_GRID

template <class weightType>
MotionPlanningGrid<weightType>::MotionPlanningGrid()
    : rowsize(0), colsize(0), maze(nullptr) {}

template <class weightType>
MotionPlanningGrid<weightType>::~MotionPlanningGrid() {
  delete[] maze;
}

template <class weightType>
MotionPlanningGrid<weightType>::MotionPlanningGrid(long long newRowSize,
                                                   long long newColSize) {
  ChangeSize(newRowSize, newColSize);
}

template <class weightType>
MotionPlanningGrid<weightType>::MotionPlanningGrid(
    const MotionPlanningGrid& that)
    : rowsize(that.rowsize),
      colsize(that.colsize),
      maze(new InfNum<weightType>[that.size * that.size]) {
  for (long long i = 0; i < Size(); ++i) maze[i] = that.maze[i];
}

template <class weightType>
void MotionPlanningGrid<weightType>::ChangeSize(long long newRowSize,
                                                long long newColSize) {
  delete[] maze;
  rowsize = newRowSize;
  colsize = newColSize;
  maze = new InfNum<weightType>[Size()];
  for (size_t i = 0; i < Size(); ++i) maze[i].MarkInfinite();
}

template <class weightType>
long long MotionPlanningGrid<weightType>::Size() const {
  return rowsize * colsize;
}

template <class weightType>
long long MotionPlanningGrid<weightType>::CoordsToIndex(
    const CoordinatePair<long long>& coord) const {
  return coord.CRow() * ColSize() + coord.CCol();
}

template <class weightType>
weightType& MotionPlanningGrid<weightType>::Get(
    const CoordinatePair<long long>& coord) const {
  return maze[CoordsToIndex(coord)].GetNum();
}

template <class weightType>
weightType& MotionPlanningGrid<weightType>::Access(
    const CoordinatePair<long long>& coord) {
  maze[CoordsToIndex(coord)].MarkFinite();
  return maze[CoordsToIndex(coord)].GetNum();
}

template <class weightType>
weightType& MotionPlanningGrid<weightType>::operator()(
    const CoordinatePair<long long>& coord) {
  return Access(coord);
}

template <class weightType>
weightType& MotionPlanningGrid<weightType>::operator()(long long row,
                                                       long long col) {
  CoordinatePair<long long> coord(row, col);
  return Access(coord);
}

template <class weightType>
bool MotionPlanningGrid<weightType>::ObstacleAt(
    const CoordinatePair<long long>& coord) const {
  return maze[CoordsToIndex(coord)].IsInfinite();
}

template <class weightType>
typename MotionPlanningGrid<weightType>::iterator
MotionPlanningGrid<weightType>::begin(CoordinatePair<long long> coord) const {
  iterator it(0, coord, this);
  if (!it->ValidIterator()) ++it;
  return it;
}

template <class weightType>
typename MotionPlanningGrid<weightType>::iterator
MotionPlanningGrid<weightType>::end(CoordinatePair<long long> coord) const {
  return iterator(4, coord, this);
}

/*********/
// ITERATOR/
/*********/
template <class weightType>
void MotionPlanningGrid<weightType>::iterator::CalcIndexCoords(
    CoordinatePair<long long>& coord) const {
  /*
  down, right, up, left
  even = row
  odd  = col
  <2   = add
  >=2  = subtract
  */
  bool even = index % 2 == 0;
  // greater than or equal to 2
  bool GEq2 = index >= 2;

  // explanation of the effect of these lines is just below function
  // signature for those unfamiliar with the ternary op
  // TODO: Make this clearer in the future
  coord.Set(CRow() + (GEq2 ? -1 : 1) * even, CCol() + (GEq2 ? -1 : 1) * !even);
}

template <class weightType>
CoordinatePair<long long> MotionPlanningGrid<weightType>::iterator::Node()
    const {
  CoordinatePair<long long> coord;
  CalcIndexCoords(coord);
  return coord;
}

template <class weightType>
const weightType& MotionPlanningGrid<weightType>::iterator::Weight() const {
  CoordinatePair<long long> coord;
  CalcIndexCoords(coord);
  return data->Get(coord);  //.CGetNum();
}

template <class weightType>
MotionPlanningGrid<weightType>::iterator::iterator()
    : curCoord(0, 0), index(0), data(nullptr) {}
template <class weightType>
MotionPlanningGrid<weightType>::iterator::iterator(
    int newIndex, CoordinatePair<long long> newNode,
    const MotionPlanningGrid<weightType>* dataPtr)
    : curCoord(newNode), index(newIndex), data(dataPtr) {}

template <class weightType>
typename MotionPlanningGrid<weightType>::iterator&
MotionPlanningGrid<weightType>::iterator::operator=(const iterator& that) {
  curCoord = that.curCoord;
  index = that.index;
  data = that.data;
  return *this;
}

template <class weightType>
MotionPlanningGrid<weightType>::iterator::iterator(const iterator& that) {
  *this = that;
}

template <class weightType>
const typename MotionPlanningGrid<weightType>::iterator*
    MotionPlanningGrid<weightType>::iterator::operator->() const {
  return this;
}

template <class weightType>
bool MotionPlanningGrid<weightType>::iterator::operator==(
    const iterator& that) const {
  return index == that.index && curCoord == that.curCoord;
}

template <class weightType>
bool MotionPlanningGrid<weightType>::iterator::operator!=(
    const iterator& that) const {
  return !(*this == that);
}

template <class weightType>
bool MotionPlanningGrid<weightType>::iterator::ValidIterator() const {
  long long s = data->ColSize();

  auto n = Node();
  if (n.CRow() < 0 || n.CRow() >= s || n.CCol() < 0 || n.CCol() >= s)
    return false;
  return !data->ObstacleAt(Node());
}

template <class weightType>
typename MotionPlanningGrid<weightType>::iterator&
MotionPlanningGrid<weightType>::iterator::operator++() {
  // if the node is outside bounds or past the max index, it is invalid
  // and we should skip past
  do
    ++index;
  while (!ValidIterator() && index < 4);
  return *this;
}

#endif
