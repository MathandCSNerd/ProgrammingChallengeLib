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

#ifndef KRUSKALS_ALGORITHM
#define KRUSKALS_ALGORITHM

#include <queue>
#include <set>
#include "../graphContainers.h"
#include "union.h"

// I just noticed I haven't implemented any BFS function so this is a
// temporary BFS while that is the case
template <template <class weightType> class containerType, class weightType>
std::set<int> ConnectedNodes(const DirectedGraph<containerType, weightType>& g,
                             int index) {
  std::queue<int> nodeQ;
  std::set<int> visited;
  int cur;

  using namespace std;
  nodeQ.push(index);

  while (nodeQ.size()) {
    cur = nodeQ.front();
    nodeQ.pop();
    if (visited.find(cur) == visited.end()) {
      visited.insert(cur);

      for (auto it = g.begin(cur); it != g.end(cur); ++it)
        if (visited.find(it->Node()) == visited.end()) nodeQ.push(it->Node());
    }
  }

  return visited;
}

template <template <class weightType> class containerType, class weightType>
DirectedGraph<containerType, weightType> GetTree(
    DirectedGraph<containerType, weightType>& g, int index) {
  DirectedGraph<containerType, weightType> mst;
  std::set<int> nodes(ConnectedNodes(g, index));

  mst.ChangeSize(g.Size());

  for (auto it : nodes) {
    for (auto it2 = g.begin(it); it2 != g.end(it); ++it2)
      mst.AddConnection(it, it2->Node(), it2->Weight());

    for (auto it2 = mst.begin(it); it2 != mst.end(it); ++it2)
      g.RmConnection(it, it2->Node());
  }
  return mst;
}

// this functions use Kruskal's algorithm to return list of MST's
// representing a minimum spanning forest for the graph "g"
// Each element of forest is a minimum spanning tree
// If only one tree is found, the forest will only have one tree
// If g has no edges then the forest will be empty
template <template <class weightType> class containerType, class weightType>
std::list<DirectedGraph<containerType, weightType>> Kruskals(
    const DirectedGraph<containerType, weightType>& g) {
  // return value for this function
  std::list<DirectedGraph<containerType, weightType>> Forest;
  // edges which will make up the mst
  std::vector<CompleteEdge<weightType>> KeepEdges;
  // graph which is used to seperate trees
  UndirectedGraph<containerType, weightType> mstGraph;
  // union find data structure for use with kruskals
  UnionFind myUnion(g.Size());
  // a vector containing all the edges in g
  auto Edges = g.GetAllEdges();

  mstGraph.ChangeSize(g.Size());

  // sorts the Edges by weight
  sort(Edges.begin(), Edges.end());

  for (auto it : Edges) {
    if (myUnion.FindSet(it.From()) != myUnion.FindSet(it.To())) {
      myUnion.Union(it.From(), it.To());
      KeepEdges.push_back(it);
    }
  }

  for (auto it : KeepEdges)
    mstGraph.AddConnection(it.From(), it.To(), it.Weight());

  for (size_t i = 0; i < mstGraph.Size(); ++i)
    if (mstGraph.begin(i) != mstGraph.end(i))
      Forest.push_back(GetTree(mstGraph, i));

  return Forest;
}

#endif
