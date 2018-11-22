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

#ifndef LIST_GRAPH_GENERIC_EDGE_NODE
#define LIST_GRAPH_GENERIC_EDGE_NODE

template <class type>
class GenericEdgeNode {
 public:
  GenericEdgeNode(int newNode, const type& newWeight)
      : node(newNode), weight(newWeight) {}
  GenericEdgeNode(int newNode) : node(newNode) {}
  int Node() const { return node; }
  type Weight() const { return weight; }
  void SetWeight(type newWeight) { weight = newWeight; }
  void SetNode(int newNode) { node = newNode; }

  void Set(int newNode, type newWeight) {
    SetWeight(newWeight);
    SetNode(newNode);
  }

  bool operator<(const GenericEdgeNode& that) const { return node < that.node; }
  bool operator==(const GenericEdgeNode& that) const {
    return node == that.node;
  }

 private:
  int node;
  type weight;
};

#endif
