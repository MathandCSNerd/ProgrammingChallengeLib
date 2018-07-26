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

#ifndef MDGraph
#define MDGraph

// only included for the PrintStats function
#include <iostream>

#include "containers/edgeContainers.h"
#include "containers/squareArray.h"
#include "containers/triArray.h"

class EmptyClass {};

template <template <class weightType> class containerType, class weightType>
class DirectedGraph {
 public:
  class iterator;

  DirectedGraph();
  ~DirectedGraph();
  DirectedGraph(const DirectedGraph& that);
  DirectedGraph& operator=(const DirectedGraph& that);
  void ChangeSize(int s);
  int Size() const;
  void AddConnection(int x, int y);
  void AddConnection(int x, int y, const weightType& val);
  void RmConnection(int x, int y);
  bool IsConnected(int x, int y) const;
  weightType& Access(int x, int y);
  DirectedGraph<containerType, weightType>::iterator begin(int x) const;
  DirectedGraph<containerType, weightType>::iterator end(int x) const;
  void SortEdge(int x);  // do nothing if array
  void SortAllEdges();   // do nothing if array
  void SetDirected(bool x);
  bool Directed() const;
  void PrintGraph() const;

 private:
  bool directed;
  containerType<weightType> myContainer;
  weightType defaultVal;
};

// the decision to make this a class was based in efficiency, clarity, and code
// reuse the alternative was either parameter specialization for list or adding
// redundant connections
template <template <class weightType> class containerType, class weightType>
class UndirectedGraph : public DirectedGraph<containerType, weightType> {
 public:
  void AddConnection(int x, int y);
  void AddConnection(int x, int y, const weightType& val);
};

// some may find it strange that I used template classes for this while I used
// C++11 alias declarations for things later, but this was done for
// simplification of other methods as well as simplification of use.

// arr graphs
template <class weightType>
class UndirectedArrGraph : public DirectedGraph<TriangularArray, weightType> {};
template <class weightType>
class DirectedArrGraph : public DirectedGraph<SquareArray, weightType> {};

// stl container graphs
template <class weightType>
class UndirectedListGraph : public UndirectedGraph<EdgeList, weightType> {};
template <class weightType>
class DirectedListGraph : public DirectedGraph<EdgeList, weightType> {};

using UnweightedDirectedArrGraph = DirectedArrGraph<EmptyClass>;
using UnweightedUndirectedArrGraph = UndirectedArrGraph<EmptyClass>;

template <template <class weightType> class containerType, class weightType>
DirectedGraph<containerType, weightType>::DirectedGraph()
    : directed(true), myContainer() {}

template <template <class weightType> class containerType, class weightType>
DirectedGraph<containerType, weightType>::~DirectedGraph() {}

template <template <class weightType> class containerType, class weightType>
DirectedGraph<containerType, weightType>::DirectedGraph(
    const DirectedGraph<containerType, weightType>& that)
    : directed(that.directed), myContainer(that.myContainer) {}

template <template <class weightType> class containerType, class weightType>
DirectedGraph<containerType, weightType>&
DirectedGraph<containerType, weightType>::operator=(
    const DirectedGraph<containerType, weightType>& that) {
  directed = that.directed;
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

// once I've finally determined each data type I wish to use this with, I will
// list them here  that way I don't have to recompile this file all the time
/*
template class DirectedGraph<TriangularArray,int>;
template class DirectedGraph<TriangularArray,long long>;
template class DirectedGraph<TriangularArray,long double>;

template class DirectedGraph<SquareArray,int>;
template class DirectedGraph<SquareArray,long long>;
template class DirectedGraph<SquareArray,long double>;
*/

#endif
