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
MotionPlanningGrid<weightType>::~MotionPlanningGrid() {
  // delete[] maze;
}

template <class weightType>
MotionPlanningGrid<weightType>::MotionPlanningGrid(const MatCoords& coord)
    : maze(coord) {
  InfNum<weightType> nam;
  nam.MarkInfinite();
  maze.SetAll(nam);
}
/*for (size_t i = 0; i < Size(); ++i) maze(i).Set();
  }*/

template <class weightType>
MotionPlanningGrid<weightType>::MotionPlanningGrid(
    const MotionPlanningGrid& that)
    : maze(that.maze) {}

/*
template <class weightType>
void MotionPlanningGrid<weightType>::ChangeSize(
    const MatCoords& coord) {
  delete[] maze;
  rowsize = coord.CRow();
  colsize = coord.CCol();
  maze = new InfNum<weightType>[Size()];
  for (size_t i = 0; i < Size(); ++i) maze[i].MarkInfinite();
}*/

template <class weightType>
long long MotionPlanningGrid<weightType>::Size() const {
  return maze.TotalSize();
}

/*template <class weightType>
long long MotionPlanningGrid<weightType>::CoordsToIndex(
    const MatCoords& coord) const {
  return coord.CRow() * ColSize() + coord.CCol();
}*/

template <class weightType>
const weightType& MotionPlanningGrid<weightType>::Get(
    const MatCoords& coord) const {
  // return maze[CoordsToIndex(coord)].GetNum();
  return maze.Get(coord).CGetNum();
}

template <class weightType>
weightType& MotionPlanningGrid<weightType>::Access(const MatCoords& coord) {
  // maze[CoordsToIndex(coord)].MarkFinite();
  // return maze[CoordsToIndex(coord)].GetNum();
  maze(coord).MarkFinite();
  return maze(coord).GetNum();
}

template <class weightType>
weightType& MotionPlanningGrid<weightType>::operator()(const MatCoords& coord) {
  return Access(coord);
}

/*template <class weightType>
weightType& MotionPlanningGrid<weightType>::operator()(long long row,
                                                       long long col) {
  MatCoords coord(row, col);
  return Access(coord);
}*/

template <class weightType>
bool MotionPlanningGrid<weightType>::ObstacleAt(const MatCoords& coord) const {
  // return maze[CoordsToIndex(coord)].IsInfinite();
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
  /*
  down, right, up, left
  even = row
  odd  = col
  <2   = add
  >=2  = subtract
  */
  // bool even = index % 2 == 0;
  // int dim =
  // greater than or equal to 2
  // bool GEq2 = index >= 2;

  // explanation of the effect of these lines is just below function
  // signature for those unfamiliar with the ternary op
  // TODO: Make this clearer in the future
  // coord.Set(CRow() + (GEq2 ? -1 : 1) * even, CCol() + (GEq2 ? -1 : 1) *
  // !even);
  coord = curCoord;
  // std::cout << "undex: " << index << ' ' << 2*curCoord.Size() << std::endl;
  if (index < 2 * curCoord.Size()) {
    if (index % 2 == 0)
      ++coord(index / 2);
    else
      --coord(index / 2);
  }
  // coord.Set()
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
  return data->Get(coord);  //.CGetNum();
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
  using namespace std;
  // long long s = data->DimSize(0);
  auto n = Node();
  // TODO: change this function to not assume a signed data type
  // if (n.CRow() < 0 || n.CRow() >= data->DimSize(0) || n.CCol() < 0 ||
  // n.CCol() >= data->DimSize(1))
  /*if(index >= 2*curCoord.Size())
    return false;*/
  // cout << "INDEXING: " << n << endl;
  for (int i = 0; i < curCoord.Size(); ++i)
    if (n(i) < 0 || n(i) >= data->DimSize(i)) return false;
  // cout << "looks valid? " << endl;
  return !data->ObstacleAt(Node());
}

template <class weightType>
typename MotionPlanningGrid<weightType>::iterator&
MotionPlanningGrid<weightType>::iterator::operator++() {
  // if the node is outside bounds or past the max index, it is invalid
  // and we should skip past
  do
    ++index;
  while (index < 2 * curCoord.Size() && !ValidIterator());
  // std::cout << "INDEXING2: " << ValidIterator() << std::endl;
  return *this;
}

#endif
