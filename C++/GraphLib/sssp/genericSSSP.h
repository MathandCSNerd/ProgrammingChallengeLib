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

#ifndef GENERIC_SSSP
#define GENERIC_SSSP

#include <list>
#include <queue>
#include <set>
#include <stack>
#include "bellmanFordSSSP.h"
#include "dijkstraSSSP.h"

template <template <class weightType> class GraphLikeClass, class weightType,
          class nodeLabelType>
bool HasNegativeWeights(const GraphLikeClass<weightType>* graphPointer,
                        nodeLabelType source) {
  if (graphPointer->Size() < 1) return 0;
  std::set<nodeLabelType> visiting;
  std::stack<nodeLabelType> mystack;
  nodeLabelType currIndex;

  mystack.push(source);
  visiting.insert(source);

  while (mystack.size()) {
    currIndex = mystack.top();
    mystack.pop();
    visiting.insert(currIndex);

    for (auto it = graphPointer->begin(currIndex);
         it != graphPointer->end(currIndex); ++it) {
      if (it->Weight() < 0) return true;
      if (visiting.find(it->Node()) == visiting.end()) {
        visiting.insert(it->Node());
        mystack.push(it->Node());
      }
    }
  }
  return false;
}

// People who've been doing a lot with polymorphism lately will get
// entirely the wrong idea from this.
// Here I'm not trying to create a base class to inherit certain
// properties from (though that's actually a decent idea and I might
// do it in the future). This class exists to pick the best SSSP
// algorithm for the given graph.
// Right now it only has bellman-ford and dijkstra's to choose between
// so the choice is predicated solely on the existence of negative
// weights, but upon adding more SSSP implementations I'll likely
// have more selection criterea
template <template <class weightType> class GraphLikeClass, class weightType,
          class nodeLabelType>
class SSSPInstance {
 public:
  SSSPInstance(const GraphLikeClass<weightType>& g)
      : graphPointer(&g),
        source(0),
        dstra(*graphPointer, source),
        bellman(*graphPointer, source),
        choose(0) {
    ResetState();
  }
  SSSPInstance(const GraphLikeClass<weightType>& g, nodeLabelType mysource)
      : graphPointer(&g),
        source(mysource),
        dstra(*graphPointer, source),
        bellman(*graphPointer, source),
        choose(0) {
    ResetState();
  }

  void ChooseSearch() {
    if (!choose) choose = 1 + HasNegativeWeights(graphPointer, source);
  }

  InfNum<weightType> ShortestPathCost(nodeLabelType end) {
    ChooseSearch();
    if (choose == 1)
      return dstra.ShortestPathCost(end);
    else
      return bellman.ShortestPathCost(end);
  }
  std::list<nodeLabelType> ShortestPath(nodeLabelType end) {
    ChooseSearch();
    if (choose == 1)
      return dstra.ShortestPath(end);
    else
      return bellman.ShortestPath(end);
  }

  void ResetState() {
    dstra.ResetState();
    bellman.ResetState();
  }

 private:
  SSSPInstance();

  GraphLikeClass<weightType> const* graphPointer;
  nodeLabelType source;
  int choose;
  DijkstraSSSPInstance<GraphLikeClass, weightType, nodeLabelType> dstra;
  BellmanFordSSSPInstance<GraphLikeClass, weightType, nodeLabelType> bellman;
};

template <template <class weightType> class GraphLikeClass, class weightType,
          class nodeLabelType>
SSSPInstance<GraphLikeClass, weightType, nodeLabelType> NewSSSPInstance(
    const GraphLikeClass<weightType>& g, nodeLabelType source) {
  return SSSPInstance<GraphLikeClass, weightType, nodeLabelType>(g, source);
}

#endif
