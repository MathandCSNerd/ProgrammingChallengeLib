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
MotionPlanningGrid<weightType>::MotionPlanningGrid(const MatCoords& coord)
    : maze(coord) {
  InfNum<weightType> nam;
  nam.MarkInfinite();
  maze.SetAll(nam);
}

template <class weightType>
MotionPlanningGrid<weightType>::MotionPlanningGrid(
    const MotionPlanningGrid& that)
    : maze(that.maze) {}

template <class weightType>
long long MotionPlanningGrid<weightType>::Size() const {
  return maze.TotalSize();
}

template <class weightType>
const weightType& MotionPlanningGrid<weightType>::Get(
    const MatCoords& coord) const {
  return maze.Get(coord).CGetNum();
}

template <class weightType>
weightType& MotionPlanningGrid<weightType>::Access(const MatCoords& coord) {
  maze(coord).MarkFinite();
  return maze(coord).GetNum();
}

template <class weightType>
weightType& MotionPlanningGrid<weightType>::operator()(const MatCoords& coord) {
  return Access(coord);
}

template <class weightType>
bool MotionPlanningGrid<weightType>::ObstacleAt(const MatCoords& coord) const {
  return maze.Get(coord).IsInfinite();
}

template <class weightType>
typename MotionPlanningGrid<weightType>::iterator
MotionPlanningGrid<weightType>::begin(MatCoords coord) const {
  iterator it(0, coord, this);
  if (!it->ValidIterator()) ++it;
  return it;
}

template <class weightType>
typename MotionPlanningGrid<weightType>::iterator
MotionPlanningGrid<weightType>::end(MatCoords coord) const {
  return iterator(2 * NumDims(), coord, this);
}

/*********/
// ITERATOR/
/*********/
template <class weightType>
void MotionPlanningGrid<weightType>::iterator::CalcIndexCoords(
    MatCoords& coord) const {
  // if the index is even/odd go forward/reverse
  // the direction is chosen by index/2
  //
  // ex: index is 3
  //    index is odd so go in reverse
  //    index/2 = 1 so choose dimension 1

  coord = curCoord;
  if (index < 2 * curCoord.Size()) {
    if (index % 2 == 0)
      ++coord(index / 2);
    else
      --coord(index / 2);
  }
}

template <class weightType>
MatCoords MotionPlanningGrid<weightType>::iterator::Node() const {
  MatCoords coord;
  CalcIndexCoords(coord);
  return coord;
}

template <class weightType>
const weightType& MotionPlanningGrid<weightType>::iterator::Weight() const {
  MatCoords coord;
  CalcIndexCoords(coord);
  return data->Get(coord);
}

template <class weightType>
MotionPlanningGrid<weightType>::iterator::iterator()
    : curCoord(0, 0), index(0), data(nullptr) {}
template <class weightType>
MotionPlanningGrid<weightType>::iterator::iterator(
    int newIndex, MatCoords newNode,
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
  // TODO: change this function to not assume a signed data type
  auto n = Node();
  for (int i = 0; i < curCoord.Size(); ++i)
    if (n(i) < 0 || n(i) >= data->DimSize(i)) return false;
  return !data->ObstacleAt(Node());
}

template <class weightType>
typename MotionPlanningGrid<weightType>::iterator&
MotionPlanningGrid<weightType>::iterator::operator++() {
  // if the node is outside bounds or past the max index, or infinite
  // it is invalid and we should skip past
  do
    ++index;
  while (index < 2 * curCoord.Size() && !ValidIterator());
  return *this;
}

#endif
