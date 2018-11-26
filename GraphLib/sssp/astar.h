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

#ifndef GRAPHLIB_ASTAR_SSSP
#define GRAPHLIB_ASTAR_SSSP

#include <list>
#include <queue>
#include <set>
#include "../containers/infNumClass.h"

namespace AStarHeuristics_Functions {

template <template <class weightType> class GraphLikeClass, class weightType,
          class nodeLabelType>
size_t Dijkstra(const GraphLikeClass<weightType>& g, const nodeLabelType start,
                const nodeLabelType end) {
  return 0;
}

template <template <class weightType> class GraphLikeClass, class weightType,
          class nodeLabelType>
size_t Manhattan(const GraphLikeClass<weightType>& g, const nodeLabelType start,
                const nodeLabelType end) {
  return start.StepDistance(end);
}

};  // namespace AStarHeuristics

namespace AStarHeuristics {
  enum{Dijkstra, Manhattan};
}


template <class weightType, class nodeLabelType>
class AStarNode {
 public:
  AStarNode(const nodeLabelType& newNode) : node(newNode) {}

  AStarNode(const nodeLabelType& newNode, const weightType& newWeight)
      : node(newNode), weight(newWeight) {}

  AStarNode(const nodeLabelType& newNode, const weightType& newWeight,
            const nodeLabelType& newPredecessor)
      : node(newNode), weight(newWeight), predecessor(newPredecessor) {}

  bool operator<(const AStarNode& that) const { return that.weight < weight; }

  AStarNode& operator=(const AStarNode& that) {
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
  bool operator()(const AStarNode<weightType, nodeLabelType>& a,
                  const AStarNode<weightType, nodeLabelType>& b) {
    return a.Node() < b.Node();
  }
};

template <template <class weightType> class GraphLikeClass, class weightType,
          class nodeLabelType>
class AStarInstance {
 public:
  AStarInstance(const GraphLikeClass<weightType>& g)
      : graphPointer(&g), source(0) {
    ResetState();
  }
  AStarInstance(const GraphLikeClass<weightType>& g, nodeLabelType mysource)
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

  void SetHeuristic(size_t (*NewHeuristic)(const GraphLikeClass<weightType>&, const nodeLabelType, const nodeLabelType)){
    Heuristic = &AStarHeuristics_Functions::Dijkstra<GraphLikeClass, weightType, nodeLabelType>;
  }

  //sets the heuristic to one builtin
  void SetHeuristic(int choice){
    if(choice == AStarHeuristics::Dijkstra)
      SetHeuristic(&AStarHeuristics_Functions::Dijkstra<GraphLikeClass, weightType, nodeLabelType>);
    else if(choice == AStarHeuristics::Manhattan)
      SetHeuristic(&AStarHeuristics_Functions::Manhattan<GraphLikeClass, weightType, nodeLabelType>);
  }

 private:
  AStarInstance();

  size_t (*Heuristic)(const GraphLikeClass<weightType>&, const nodeLabelType,
                    const nodeLabelType) =
      &AStarHeuristics_Functions::Dijkstra<GraphLikeClass, weightType, nodeLabelType>;
  GraphLikeClass<weightType> const* graphPointer;
  nodeLabelType source;
  std::set<AStarNode<weightType, nodeLabelType>,
           cmpByNodeFunctor<weightType, nodeLabelType>>
      myset;
  std::priority_queue<AStarNode<weightType, nodeLabelType>> pq;
};

template <template <class weightType> class GraphLikeClass, class weightType,
          class nodeLabelType>
AStarInstance<GraphLikeClass, weightType, nodeLabelType> NewAStarInstance(
    const GraphLikeClass<weightType>& g, nodeLabelType source);

#include "astar.tcc"

#endif
