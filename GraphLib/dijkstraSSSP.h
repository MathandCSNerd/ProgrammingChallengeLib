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

template <class weightType>
class DijkstraSSSPNode {
 public:
  DijkstraSSSPNode(const long long& newNode) : node(newNode) {}

  DijkstraSSSPNode(const long long& newNode, const weightType& newWeight)
      : node(newNode), weight(newWeight) {}

  DijkstraSSSPNode(const long long& newNode, const weightType& newWeight,
                   const long long& newPredecessor)
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
  long long Node() const { return node; }
  weightType Weight() const { return weight; }
  long long Predecessor() const { return predecessor; }

 private:
  long long node;
  weightType weight;
  long long predecessor;
};

// Comparator used for causing the set of searched nodes to be sorted by node
// rather than weight. This is to ensure the criterea for checking if a node
// is in the set is simply whether or the Node label matches.
template <class weightType>
struct cmpByNodeFunctor {
  bool operator()(const DijkstraSSSPNode<weightType>& a,
                  const DijkstraSSSPNode<weightType>& b) {
    return a.Node() < b.Node();
  }
};

// TODO: change DijkstraSSSP to have arbitrary node-label-type and
// MotionPlanningGrid::iterator::Node() to return an int pair
//
// Also change return type to InfNumClass<weightType> so that
// the approach is not as hacky.
template <template <class weightType> class GraphLikeClass, class weightType>
class DijkstraSSSPInstance {
 public:
  DijkstraSSSPInstance(const GraphLikeClass<weightType>& g)
      : graphPointer(&g), source(0) {
    ResetState();
  }
  DijkstraSSSPInstance(const GraphLikeClass<weightType>& g, long long mysource)
      : graphPointer(&g), source(mysource) {
    ResetState();
  }
  void CalcShortestPath(long long end);

  // todo: make const versions of the following
  //      which make no calls to CalcShortestPath
  InfNum<weightType> ShortestPathCost(long long end);
  std::list<long long> ShortestPath(long long end);

  void ResetState();
  void SetSource(long long newSource) { source = newSource; }

 private:
  DijkstraSSSPInstance();

  GraphLikeClass<weightType> const* graphPointer;
  long long source;
  std::set<DijkstraSSSPNode<weightType>, cmpByNodeFunctor<weightType>> myset;
  std::priority_queue<DijkstraSSSPNode<weightType>> pq;
};

/*template <template <class weightType> class GraphLikeClass, class weightType>
DijkstraSSSPInstance<GraphLikeClass, weightType> NewDijkstraSSSPInstance(
    const GraphLikeClass<weightType>& g, long long source);
*/
#include "dijkstraSSSP.tcc"

#endif
