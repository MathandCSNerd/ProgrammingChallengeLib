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

#ifndef GRAPHLIB_DIJKSTRA_SSSP
#define GRAPHLIB_DIJKSTRA_SSSP

#include <queue>
#include <set>
#include "containers/infNumClass.h"

template <class weightType, class nodeLabelType>
class DijkstraSSSPNode {
 public:
  DijkstraSSSPNode(const nodeLabelType& newNode) : node(newNode) {}

  DijkstraSSSPNode(const nodeLabelType& newNode, const weightType& newWeight)
      : node(newNode), weight(newWeight) {}

  DijkstraSSSPNode(const nodeLabelType& newNode, const weightType& newWeight,
                   const nodeLabelType& newPredecessor)
      : node(newNode), weight(newWeight), predecessor(newPredecessor) {}

  bool operator<(const DijkstraSSSPNode& that) const {
    return that.weight < weight;
  }

  DijkstraSSSPNode& operator=(const DijkstraSSSPNode& that) {
    node = that.node;
    weight = that.weight;
    predecessor = that.predecessor;
    return *this;
  }
  nodeLabelType Node() const { return node; }
  weightType Weight() const { return weight; }
  nodeLabelType Predecessor() const { return predecessor; }

 private:
  nodeLabelType node;
  weightType weight;
  nodeLabelType predecessor;
};

// Comparator used for causing the set of searched nodes to be sorted by node
// rather than weight. This is to ensure the criterea for checking if a node
// is in the set is simply whether or the Node label matches.
template <class weightType, class nodeLabelType>
struct cmpByNodeFunctor {
  bool operator()(const DijkstraSSSPNode<weightType, nodeLabelType>& a,
                  const DijkstraSSSPNode<weightType, nodeLabelType>& b) {
    return a.Node() < b.Node();
  }
};

template <template <class weightType> class GraphLikeClass, class weightType,
          class nodeLabelType>
class DijkstraSSSPInstance {
 public:
  DijkstraSSSPInstance(const GraphLikeClass<weightType>& g)
      : graphPointer(&g), source(0) {
    ResetState();
  }
  DijkstraSSSPInstance(const GraphLikeClass<weightType>& g,
                       nodeLabelType mysource)
      : graphPointer(&g), source(mysource) {
    ResetState();
  }
  void CalcShortestPath(nodeLabelType end);

  // todo: make const versions of the following
  //      which make no calls to CalcShortestPath
  InfNum<weightType> ShortestPathCost(nodeLabelType end);
  std::list<nodeLabelType> ShortestPath(nodeLabelType end);

  void ResetState();
  void SetSource(nodeLabelType newSource) {
    if (source != newSource) ResetState();
    source = newSource;
  }

 private:
  DijkstraSSSPInstance();

  GraphLikeClass<weightType> const* graphPointer;
  nodeLabelType source;
  std::set<DijkstraSSSPNode<weightType, nodeLabelType>,
           cmpByNodeFunctor<weightType, nodeLabelType>>
      myset;
  std::priority_queue<DijkstraSSSPNode<weightType, nodeLabelType>> pq;
};

template <template <class weightType> class GraphLikeClass, class weightType,
          class nodeLabelType>
DijkstraSSSPInstance<GraphLikeClass, weightType, nodeLabelType>
NewDijkstraSSSPInstance(const GraphLikeClass<weightType>& g,
                        nodeLabelType source);

#include "dijkstraSSSP.tcc"

#endif
