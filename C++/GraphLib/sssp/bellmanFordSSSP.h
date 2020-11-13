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

#ifndef BELLMAN_FORD
#define BELLMAN_FORD

#include <list>
#include <set>
#include <vector>
#include "../containers/infNumClass.h"

template <class weightType, class nodeLabelType>
class BellmanNode {
 public:
  BellmanNode() { Reset(); }
  BellmanNode(const BellmanNode& that)
      : predecessor(that.predecessor),
        distance(that.distance),
        negativeCycle(that.negativeCycle) {}

  BellmanNode(const nodeLabelType& newNode,
              const InfNum<weightType>& newDistance,
              const bool& newNegativeCycle)
      : predecessor(newNode),
        distance(newDistance),
        negativeCycle(newNegativeCycle) {}

  bool operator<(const BellmanNode& that) const {
    return that.distance < distance;
  }

  BellmanNode& operator=(const BellmanNode& that) {
    predecessor = that.predecessor;
    distance = that.distance;
    negativeCycle = that.negativeCycle;
    return *this;
  }
  nodeLabelType& Predecessor() { return predecessor; }
  InfNum<weightType>& Distance() { return distance; }
  /*bool& NegativeCycle() { return negativeCycle; }*/
  void MarkNegativeCycle() { distance.MarkNegInfinite(); }
  void Reset() {
    predecessor = -1;
    distance.MarkInfinite();
    negativeCycle = false;
  }

 private:
  // make predecessor a pointer for future changes
  nodeLabelType predecessor;
  InfNum<weightType> distance;
  bool negativeCycle;
};

// template <class weightType>
// class BellmanResults public: vector<BellmanNode<weightType>>{};

template <class weightType, class nodeLabelType>
using BellmanResults = std::vector<BellmanNode<weightType, nodeLabelType>>;

// this is a hacky, not yet finished function for marking negative cycles
// this will be either removed or fixed in a future update
template <class weightType, class nodeLabelType>
void MarkNegativeCycles(nodeLabelType start,
                        BellmanResults<weightType, nodeLabelType>& vertices) {
  std::set<nodeLabelType> preds;
  nodeLabelType cur = vertices[start].Predecessor();

  vertices[start].MarkNegativeCycle();
  // while(cur != start){
  while (cur != -1 && preds.find(cur) == preds.end() &&
         !vertices[cur].NegativeCycle()) {
    // std::cout << "c: " << cur << std::endl;
    vertices[cur].MarkNegativeCycle();
    cur = vertices[cur].Predecessor();
  }
}

template <template <class weightType> class GraphLikeClass, class weightType,
          class nodeLabelType>
BellmanResults<weightType, nodeLabelType> Bellman(
    nodeLabelType source, const GraphLikeClass<weightType>& g) {
  BellmanResults<weightType, nodeLabelType> vertices;
  vertices.resize(g.Size());

  for (auto it : vertices) it.Reset();

  vertices[source].Distance() = 0;

  for (long long i = 1; i < g.Size(); ++i) {
    // for each edge u,v
    for (nodeLabelType u(0); u < g.Size(); ++u) {
      for (auto v = g.begin(u); v != g.end(u); ++v)
        if (/*v->Node() != u && */ vertices[u].Distance() + v->Weight() <
            vertices[v->Node()].Distance()) {
          vertices[v->Node()].Distance() = vertices[u].Distance() + v->Weight();
          vertices[v->Node()].Predecessor() = u;
        }
    }
  }

  // find all nodes which are part of negative cycles
  for (long long i = 0; i <= g.Size(); ++i) {
    for (nodeLabelType u(0); u < g.Size(); ++u) {
      for (auto v = g.begin(u); v != g.end(u); ++v) {
        if (/*v->Node() != u && */ (vertices[u].Distance() + v->Weight()) <
            vertices[v->Node()].Distance()) {
          vertices[v->Node()].Predecessor() = u;
          vertices[v->Node()].MarkNegativeCycle();
          vertices[u].MarkNegativeCycle();
        }
      }
    }
  }

  return vertices;
}

template <template <class weightType> class GraphLikeClass, class weightType,
          class nodeLabelType>
class BellmanFordSSSPInstance {
 public:
  BellmanFordSSSPInstance(const GraphLikeClass<weightType>& g,
                          nodeLabelType mysource)
      : graphPointer(&g), source(mysource), myresults(NULL) {
    ResetState();
  }
  ~BellmanFordSSSPInstance() { delete myresults; }

  void CalcShortestPath() {
    if (!myresults)
      myresults = new BellmanResults<weightType, nodeLabelType>(
          Bellman(source, *graphPointer));
  }

  // TODO: make const versions of the following
  //      which make no calls to CalcShortestPath
  InfNum<weightType> ShortestPathCost(nodeLabelType end) {
    CalcShortestPath();
    return (*myresults)[end].Distance();
  }

  std::list<nodeLabelType> ShortestPath(nodeLabelType end);

  void ResetState() {
    delete myresults;
    myresults = NULL;
  }

 private:
  GraphLikeClass<weightType> const* graphPointer;
  nodeLabelType source;
  BellmanResults<weightType, nodeLabelType>* myresults;
};

template <template <class weightType> class GraphLikeClass, class weightType,
          class nodeLabelType>
std::list<nodeLabelType>
BellmanFordSSSPInstance<GraphLikeClass, weightType,
                        nodeLabelType>::ShortestPath(nodeLabelType end) {
  std::list<nodeLabelType> nodeList;

  CalcShortestPath();

  if (end < 0 || end > myresults->size()) return nodeList;

  auto node = (*myresults)[end];
  if (!(node.Distance()).IsFinite())  // we don't have that node
    return nodeList;                  // so return an empty list

  nodeList.push_front(end);

  nodeLabelType curnode = (*myresults)[end].Predecessor();

  while (curnode != -1 && (*myresults)[curnode].Predecessor() != curnode) {
    nodeList.push_front(curnode);
    curnode = (*myresults)[curnode].Predecessor();
  }

  return nodeList;
}

template <template <class weightType> class GraphLikeClass, class weightType,
          class nodeLabelType>
BellmanFordSSSPInstance<GraphLikeClass, weightType, nodeLabelType>
NewBellmanFordSSSPInstance(const GraphLikeClass<weightType>& g,
                           nodeLabelType source) {
  return BellmanFordSSSPInstance<GraphLikeClass, weightType, nodeLabelType>(
      g, source);
}

#endif
