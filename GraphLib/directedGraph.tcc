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

#ifdef DIRECTED_GRAPH_CLASS

//functions definitions:
template <template <class weightType> class containerType, class weightType>
DirectedGraph<containerType, weightType>::DirectedGraph()
    : myContainer() {}

template <template <class weightType> class containerType, class weightType>
DirectedGraph<containerType, weightType>::~DirectedGraph() {}

template <template <class weightType> class containerType, class weightType>
DirectedGraph<containerType, weightType>::DirectedGraph(
    const DirectedGraph<containerType, weightType>& that)
    : myContainer(that.myContainer) {}

template <template <class weightType> class containerType, class weightType>
DirectedGraph<containerType, weightType>&
DirectedGraph<containerType, weightType>::operator=(
    const DirectedGraph<containerType, weightType>& that) {
  myContainer = that.myContainer;
  return *this;
}

template <template <class weightType> class containerType, class weightType>
void DirectedGraph<containerType, weightType>::ChangeSize(int s) {
  myContainer.ChangeSize(s);
}

template <template <class weightType> class containerType, class weightType>
int DirectedGraph<containerType, weightType>::Size() const {
  return myContainer.Size();
}

template <template <class weightType> class containerType, class weightType>
void DirectedGraph<containerType, weightType>::AddConnection(int x, int y) {
  if (x >= 0 and x < Size() and y >= 0 and y < Size())
    myContainer.Set(x, y, defaultVal);
}

template <template <class weightType> class containerType, class weightType>
void DirectedGraph<containerType, weightType>::AddConnection(
    int x, int y, const weightType& val) {
  if (x >= 0 and x < Size() and y >= 0 and y < Size())
    myContainer.Set(x, y, val);
}

template <template <class weightType> class containerType, class weightType>
void DirectedGraph<containerType, weightType>::RmConnection(int x, int y) {
  if (x >= 0 and x < Size() and y >= 0 and y < Size()) myContainer.Unset(x, y);
}

template <template <class weightType> class containerType, class weightType>
bool DirectedGraph<containerType, weightType>::IsConnected(int x, int y) const {
  if (x >= 0 and x < Size() and y >= 0 and y < Size())
    return myContainer.Exists(x, y);
  return false;
}

template <template <class weightType> class containerType, class weightType>
weightType& DirectedGraph<containerType, weightType>::Access(int x, int y) {
  if (x >= 0 and x < Size() and y >= 0 and y < Size())
    return myContainer.Access(x, y);
  return weightType();
}

template <template <class weightType> class containerType, class weightType>
typename DirectedGraph<containerType, weightType>::iterator
DirectedGraph<containerType, weightType>::begin(int x) const {
  if (x >= 0 and x < Size()) return iterator(myContainer.begin(x));
  return iterator(myContainer.begin(0));
}

template <template <class weightType> class containerType, class weightType>
typename DirectedGraph<containerType, weightType>::iterator
DirectedGraph<containerType, weightType>::end(int x) const {
  if (x >= 0 and x < Size()) return iterator(myContainer.end(x));
  return iterator(myContainer.begin(0));
}

template <template <class weightType> class containerType, class weightType>
void DirectedGraph<containerType, weightType>::PrintGraph() const {
  myContainer.Output();
}

template <template <class weightType> class containerType, class weightType>
class DirectedGraph<containerType, weightType>::iterator
    : public containerType<weightType>::iterator {
 public:
  iterator(const typename containerType<weightType>::iterator& it)
      : containerType<weightType>::iterator(it) {}
};

template <template <class weightType> class containerType, class weightType>
void UndirectedGraph<containerType, weightType>::AddConnection(int x, int y){
  if (x >= 0 and x < this->Size() and y >= 0 and y < this->Size()){
    this->myContainer.Set(x, y, this->defaultVal);
    this->myContainer.Set(y, x, this->defaultVal);
  }
}

template <template <class weightType> class containerType, class weightType>
void UndirectedGraph<containerType, weightType>::AddConnection(int x, int y, const weightType& val){
  if (x >= 0 and x < this->Size() and y >= 0 and y < this->Size()){
    this->myContainer.Set(x, y, val);
    this->myContainer.Set(y, x, val);
  }
}

template <template <class weightType> class containerType, class weightType>
void UndirectedGraph<containerType, weightType>::RmConnection(int x, int y) {
  if (x >= 0 and x < this->Size() and y >= 0 and y < this->Size()){
    this->myContainer.Unset(x, y);
    this->myContainer.Unset(y, x);
  }
}

#endif
