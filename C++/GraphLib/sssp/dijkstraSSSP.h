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

#include "astar.h"

template <template <class weightType> class GraphLikeClass, class weightType,
          class nodeLabelType>
class DijkstraSSSPInstance {
 public:
  DijkstraSSSPInstance(const GraphLikeClass<weightType>& g) : dstra(g, 0) {
    ResetState();
  }
  DijkstraSSSPInstance(const GraphLikeClass<weightType>& g,
                       nodeLabelType mysource)
      : dstra(g, mysource) {
    ResetState();
  }

  InfNum<weightType> ShortestPathCost(nodeLabelType end) {
    return dstra.ShortestPathCost(end);
  }
  std::list<nodeLabelType> ShortestPath(nodeLabelType end) {
    return dstra.ShortestPath(end);
  }

  void ResetState() { dstra.ResetState(); }

 private:
  DijkstraSSSPInstance();

  AStarInstance<GraphLikeClass, weightType, nodeLabelType> dstra;
};

template <template <class weightType> class GraphLikeClass, class weightType,
          class nodeLabelType>
DijkstraSSSPInstance<GraphLikeClass, weightType, nodeLabelType>
NewDijkstraSSSPInstance(const GraphLikeClass<weightType>& g,
                        nodeLabelType source) {
  return DijkstraSSSPInstance<GraphLikeClass, weightType, nodeLabelType>(
      g, source);
}

#endif
