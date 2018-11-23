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

#ifdef GRAPHLIB_DIJKSTRA_SSSP

template <template <class weightType> class GraphLikeClass, class weightType>
InfNum<weightType>
DijkstraSSSPInstance<GraphLikeClass, weightType>::ShortestPathCost(
    long long end) {
  using namespace std;
  CalcShortestPath(end);

  InfNum<weightType> retVal;
  retVal.MarkInfinite();  // mark infinite in case node is not found

  auto node = myset.find(end);
  if (node != myset.end()) retVal = node->Weight();

  return retVal;
}

template <template <class weightType> class GraphLikeClass, class weightType>
std::list<long long>
DijkstraSSSPInstance<GraphLikeClass, weightType>::ShortestPath(long long end) {
  std::list<long long> nodeList;

  CalcShortestPath(end);

  auto node = myset.find(end);
  if (node == myset.end())  // we don't have that node
    return nodeList;        // so return an empty list

  nodeList.push_front(node.Node());

  DijkstraSSSPNode<weightType> curnode = *myset.find(node.Predecessor());

  while (curnode.Predecessor() != curnode.Node()) {
    nodeList.push_front(curnode.Node());
    curnode = *myset.find(curnode.Predecessor());
  }

  return nodeList;
}

template <template <class weightType> class GraphLikeClass, class weightType>
void DijkstraSSSPInstance<GraphLikeClass, weightType>::ResetState() {
  myset.clear();
  while (pq.size()) pq.pop();
  pq.push(DijkstraSSSPNode<weightType>(source, weightType(0), source));
}

template <template <class weightType> class GraphLikeClass, class weightType>
void DijkstraSSSPInstance<GraphLikeClass, weightType>::CalcShortestPath(
    long long end) {
  weightType currWeight;

  auto tmpit = myset.find(end);
  if ((myset.find(end)) != myset.end()) return;
  // we have already visited the node

  // TODO: possibly add the following functionality to underlying classes
  /*if(end > graphPointer->MaxPossibleNode() or end <
    graphPointer->LeastPossibleNode())
    return; //the node isn't in the graph, no sense in looking for it*/

  auto tmpnode = pq.top();
  long long currIndex;
  bool exit = false;
  while (!exit && pq.size()) {
    if (pq.top().Node() == end) exit = true;
    tmpnode = pq.top();
    pq.pop();
    if (myset.find(tmpnode.Node()) == myset.end()) {
      myset.insert(tmpnode);
      currWeight = tmpnode.Weight();
      currIndex = tmpnode.Node();

      for (auto it = graphPointer->begin(currIndex);
           it != graphPointer->end(currIndex); ++it) {
        if ((myset.find(it->Node()) == myset.end())) {
          DijkstraSSSPNode<weightType> newNode(
              it->Node(), currWeight + it->Weight(), tmpnode.Node());
          pq.push(newNode);
        }
      }
    }
  }
}

template <template <class weightType> class GraphLikeClass, class weightType>
DijkstraSSSPInstance<GraphLikeClass, weightType> NewDijkstraSSSPInstance(
    const GraphLikeClass<weightType>& g, long long source) {
  return DijkstraSSSPInstance<GraphLikeClass, weightType>(g, source);
}

#endif
