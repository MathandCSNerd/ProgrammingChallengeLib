#Copyright 2020 Matthew Macallister
#
#This file is part of ProgrammingChallengeLib.
#
#ProgrammingChallengeLib is free software: you can redistribute it and/or
#modify it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#ProgrammingChallengeLib is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with ProgrammingChallengeLib.  If not, see
#<https://www.gnu.org/licenses/>.


from collections import deque


class _queue(deque):
  def pop(self):
    return self.popleft()


def _star_first_search(graph, source, myq, leftwise_order):
  WHITE, GRAY, BLACK = (0, 1, 2)

  order = []
  predecessor = [-1] * graph.get_size()
  distance = [-1] * graph.get_size()
  colour = [WHITE] * graph.get_size()

  colour[source] = GRAY
  distance[source] = 0
  predecessor[source] = -1
  myq.append(source)

  while len(myq) > 0:
    u = myq.pop()
    if leftwise_order:
      edges = graph.get_edges_from(u)[::-1]
    else:
      edges = graph.get_edges_from(u)
    for v in edges:
      if colour[v] == WHITE:
        colour[v] = GRAY
        distance[v] = distance[u] + 1
        predecessor[v] = u
        myq.append(v)
    order.append(u)
  return order, predecessor, distance


def depth_first_search(graph, source, leftwise_order = True):
  return _star_first_search(graph, source, [], leftwise_order)


def breadth_first_search(graph, source, rightwise_order = True):
  return _star_first_search(graph, source, _queue(), not rightwise_order)

