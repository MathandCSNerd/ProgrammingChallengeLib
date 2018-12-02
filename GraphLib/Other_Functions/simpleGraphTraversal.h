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

#ifndef GRAPHLIB_SIMPLE_GRAPH_TRAVERSAL
#define GRAPHLIB_SIMPLE_GRAPH_TRAVERSAL

#include <queue>
#include <stack>
#include <vector>
#include "../graphContainers.h"

// These 2 functions bear some explanation.
//
// As everyone knows, the difference between BFS and DFS is a queue
// and a stack. Because of this, instead of writing a new function for
// DFS I figured it would make sense to use the same function for both
// and just swapout the data type using templates or something else.
// Problem: the first element in stl stack is referenced with "top"
// and the first element in queue is reference with "front".
// It's kind of annoying that they don't even have the option of
// having the same interface, but I don't want to maintain my own
// just because of this.
//
// There's a couple things then I can do:
// 1. Write 2 functions with a one line difference. Bad idea.
// 2. Maintain my own queue with a "top" function. A worse idea.
// 3. Use a deque and a bool switch to decide what to act like.
// 4. Have a class which strictly uses one or the other
//   based on a bool switch.
// 5. Write a function for a queue and another for a stack
//   which uses the proper function to emulate them having
//   the same interface.
// I have chosen option 5 since it seems the most logical and easy
template <class type>
type QFront(const std::stack<type>& myq) {
  return myq.top();
}

template <class type>
type QFront(const std::queue<type>& myq) {
  return myq.front();
}


// TODO: figure out a way to allow switching between leftwise and
//       rigthwise node order
template <class GraphClass, class ContainerType>
void AsteriskFirstSearch(const GraphClass& graph, int source,
                         std::vector<int>& order, std::vector<int>& predecessor,
                         std::vector<int>& distance) {
  enum colours { WHITE, GRAY, BLACK};
  ContainerType myq;
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

  colour[source] = GRAY;
  distance[source] = 0;
  predecessor[source] = -1;  // NIL
  myq.push(source);

  while (myq.size()) {
    int u = QFront(myq);
    myq.pop();
    // for each v in edge list of u
    for (auto it = graph.begin(u); it != graph.end(u); ++it) {
      if (colour[it->Node()] == WHITE) {
        colour[it->Node()] = GRAY;
        distance[it->Node()] = distance[u] + 1;
        predecessor[it->Node()] = u;
        myq.push(it->Node());
      }
    }
    order.push_back(u);
    //colour[u] = BLACK;
  }
}

template <class GraphClass>
void BFS(const GraphClass& graph, int source, std::vector<int>& order,
         std::vector<int>& predecessor, std::vector<int>& distance) {
  AsteriskFirstSearch<GraphClass, std::queue<int>>(graph, source, order,
                                                   predecessor, distance);
}

template <class GraphClass>
void DFS(const GraphClass& graph, int source, std::vector<int>& order,
         std::vector<int>& predecessor, std::vector<int>& distance) {
  AsteriskFirstSearch<GraphClass, std::stack<int>>(graph, source, order,
                                                   predecessor, distance);
}

template <class GraphClass>
std::vector<int> BFSOrder(const GraphClass& g, int source) {
  std::vector<int> order, predecessor, distance;
  BFS(g, source, order, predecessor, distance);
  return order;
}

template <class GraphClass>
std::vector<int> DFSOrder(const GraphClass& g, int source) {
  std::vector<int> order, predecessor, distance;
  DFS(g, source, order, predecessor, distance);
  return order;
}

#endif
