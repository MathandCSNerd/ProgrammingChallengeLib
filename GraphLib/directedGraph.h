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

#ifndef DIRECTED_GRAPH_CLASS
#define DIRECTED_GRAPH_CLASS

// only included for the PrintStats function
#include <iostream>

#include "containers/edgeContainers.h"
#include "containers/squareArray.h"
#include "containers/triArray.h"

// used for unweighted graphs
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
  virtual bool Directed() const { return true; };
  void PrintGraph() const;

 protected:
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
  void RmConnection(int x, int y);
  bool Directed() const { return false; }
};

// arr graphs
template <class weightType>
class DirectedArrGraph : public DirectedGraph<SquareArray, weightType> {};
template <class weightType>
class UndirectedArrGraph : public DirectedGraph<TriangularArray, weightType> {
 public:
  bool Directed() const { return false; }
};

// stl container graphs
template <class weightType>
class DirectedListGraph : public DirectedGraph<EdgeList, weightType> {};
template <class weightType>
class UndirectedListGraph : public UndirectedGraph<EdgeList, weightType> {
 public:
  bool Directed() const { return false; }
};

using NonweightedDirectedArrGraph = DirectedArrGraph<EmptyClass>;
using NonweightedUndirectedArrGraph = UndirectedArrGraph<EmptyClass>;

// file with most implementation details
#include "directedGraph.tcc"

#endif
