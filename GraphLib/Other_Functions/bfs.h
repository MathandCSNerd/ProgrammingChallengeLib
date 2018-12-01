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

#ifndef GRAPHLIB_BFS
#define GRAPHLIB_BFS

#include <queue>
#include <vector>
#include "../graphContainers.h"

template <class GraphClass>
void BFS(const GraphClass& graph, int source, std::vector<int>& order, std::vector<int>& predecessor,
         std::vector<int>& distance) {
  enum colours { WHITE, BLACK, GRAY };
  std::queue<int> myq;
  std::vector<bool> colour;

  order.clear();
  order.reserve(graph.Size());

  predecessor.resize(graph.Size());
  distance.resize(graph.Size());
  colour.resize(graph.Size());

  // for each vertex
  for (size_t u = 0; u < graph.Size(); ++u) {
    colour[u] = WHITE;
    distance[u] = -1;     // NIL
    predecessor[u] = -1;  // NIL
  }
  // There's not really a point to marking a node gray for the
  // purposes of this function, so I won't be using that part
  // of the algorithm.
  // colour[source] = GRAY;
  distance[source] = 0;
  predecessor[source] = -1;  // NIL
  myq.push(source);
  order.push_back(source);
  myq.push(source);
  while (myq.size()) {
    int u = myq.front();
    myq.pop();
    // for each v in edge list of u
    for (auto it = graph.begin(u); it != graph.end(u); ++it){
    //for (int v = 0; v < size; ++v)
    //  if (graph.Connected(u, v)) {
        if (colour[it->Node()] == WHITE) {
          order.push_back(it->Node());
          // colour[v] = GRAY;
          distance[it->Node()] = distance[u] + 1;
          predecessor[it->Node()] = u;
          myq.push(it->Node());
        }
    //  }
      colour[u] = BLACK;
    }
  }
}

template <class GraphClass>
std::vector<int> BFSOrder(const GraphClass& g, int source) {
  std::vector<int> order, predecessor, distance;
  BFS(g, source, order, predecessor, distance);
  return order;
}

#endif
