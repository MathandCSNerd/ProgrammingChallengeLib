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

#ifndef DSTRA
#define DSTRA

#include <queue>
#include <set>
#include "directedGraph.h"

template <class weightType>
class DstraNode {
 public:
  DstraNode(const long long& newNode) : node(newNode) {}

  DstraNode(const long long& newNode, const weightType& newWeight)
      : node(newNode), weight(newWeight) {}

  DstraNode(const long long& newNode, const weightType& newWeight,
            const long long& newPredecessor)
      : node(newNode), weight(newWeight), predecessor(newPredecessor) {}

  bool operator<(const DstraNode& that) const { return that.weight < weight; }

  DstraNode& operator=(const DstraNode& that) {
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

// comparator used for causing the set of searched nodes to be sorted by node
// rather than weight
template <class weightType>
auto cmp = [](const DstraNode<weightType>& a, const DstraNode<weightType>& b) {
  return a.Node() < b.Node();
};

template <class weightType>
const std::list<long long> GetPath(
    const DstraNode<weightType>& node,
    typename std::set<DstraNode<weightType>, decltype(cmp<weightType>)>&
        myset) {
  std::list<long long> nodeList;
  nodeList.push_front(node.Node());

  DstraNode<weightType> curnode = *myset.find(node.Predecessor());

  while (curnode.Predecessor() != curnode.Node()) {
    nodeList.push_front(curnode.Node());
    curnode = *myset.find(curnode.Predecessor());
  }

  return nodeList;
}

template <class weightType>
void ResetDstraState(
    long long& start,
    typename std::set<DstraNode<weightType>, decltype(cmp<weightType>)>& myset,
    typename std::priority_queue<DstraNode<weightType>>& pq) {
  myset.clear();
  while (pq.size()) pq.pop();
  pq.push(DstraNode<weightType>(start, weightType(0), start));
}

// I decided the decision of retrieving path and returning
// of path can be done with the same var
// This way it's simpler and less likely to run into user-error.
// The best way I could think of to do that is using a pointer.
// The reason a reference couldn't achieve this task is due to
// lack of ability to use a default argument.
template <template <class weightType> class GraphLikeClass, class weightType>
weightType Dstra(long long start, long long end,
                 const GraphLikeClass<weightType>& g,
                 std::list<long long>* path = nullptr);

// TODO: change dstra to have arbitrary node-label-type and
// MotionPlanningGrid::iterator::Node() to return an int pair
//
// the arbitrary node label type can be done using a class as
// a stand-in for long long which sets default values just like
template <template <class weightType> class GraphLikeClass, class weightType>
weightType Dstra(long long start, long long end,
                 const GraphLikeClass<weightType>& g,
                 std::list<long long>* path) {
  using namespace std;
  static weightType currWeight;
  static set<DstraNode<weightType>, decltype(cmp<weightType>)> myset(
      cmp<weightType>);
  static priority_queue<DstraNode<weightType>> pq;
  if (start >= 0) {
    ResetDstraState(start, myset, pq);
    if (path != nullptr) return 0;
  }

  auto tmpit = myset.find(end);
  if ((myset.find(end)) != myset.end()) {
    if (path != nullptr) (*path) = (GetPath(*tmpit, myset));
    return tmpit->Weight();
  }

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

      for (auto it = g.begin(currIndex); it != g.end(currIndex); ++it) {
        if ((myset.find(it->Node()) == myset.end())) {
          DstraNode<weightType> newNode(it->Node(), currWeight + it->Weight(),
                                        tmpnode.Node());
          pq.push(newNode);
        }
      }
    }
  }

  if (myset.find(end) == myset.end())
    return -1;
  else {
    if (path != nullptr) (*path) = ((GetPath(*myset.find(end), myset)));

    return myset.find(end)->Weight();
  }
}

#endif
