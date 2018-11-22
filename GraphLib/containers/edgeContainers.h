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

#ifndef EDGE_LIST
#define EDGE_LIST

#include <algorithm>
#include <list>
#include <map>
#include <vector>
#include "edgeNode.h"
#include "genericEdgeContainer.h"

template <class weightType>
class EdgeList
    : public EdgeContainer<std::list<GenericEdgeNode<weightType>>, weightType> {
 public:
  typename EdgeContainer<std::list<GenericEdgeNode<weightType>>,
                         weightType>::iterator
  FindEdge(int x, int y) const {
    return std::find(
        EdgeContainer<std::list<GenericEdgeNode<weightType>>,
                      weightType>::begin(x),
        EdgeContainer<std::list<GenericEdgeNode<weightType>>, weightType>::end(
            x),
        GenericEdgeNode<weightType>(y));
  }
};

// TODO:
// class MultiGraphEdgeList
// inherit EdgeList
// modify a couple pieces to allow for multiple edges for same nodes
// add edgecount function to return number of connection between nodes?

#endif
