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


import math
from graphContainers import *
from heapq import *

def _null_heuristic(x, y):
  return 0

def dstra_sssp(graph, source, end, myq=None, shortest_set=None):
  return a_star_sssp(graph, source, end, _null_heuristic, myq, shortest_set)

def a_star_sssp(graph, source, end, heuristic, myq=None, shortest_set=None):
  if myq == None:
    myq = [(0, source, -1)]
  if shortest_set == None:
    shortest_set = dict()
  if end in shortest_set:
    return shortest_set[end][0], myq, shortest_set
  u = None
  while len(myq) > 0 and len(shortest_set) < graph.get_size():
    u = heappop(myq)
    if not u[1] in shortest_set:
      shortest_set[u[1]] = (u[0], u[2])
      for edge in graph.get_edges_from(u[1]):
        if not edge in shortest_set:
          total_weight = graph.get_weight(u[1], edge) + u[0] + heuristic(u[1], edge)
          new_node = (total_weight, edge, u[1])
          heappush(myq, new_node)
      if u[1] == end:
        break
  if end in shortest_set:
    ans = shortest_set[end]
  else:
    ans = [math.inf]
  return ans[0], myq, shortest_set


def bellman_ford_sssp(graph, source, detect_negative_cycles=True):
  size = graph.get_size()
  distances = [math.inf]*size
  preds = [-1]*size
  distances[source] = 0

  for i in range(size):
    for u in range(size):
      for v in graph.get_edges_from(u):
        temp_weight = distances[u] + graph.get_weight(u, v)
        if temp_weight < distances[v]:
          distances[v] = temp_weight
          preds[v] = u

  if detect_negative_cycles:
    for i in range(size):
      new_cycle = False
      for u in range(size):
        for v in graph.get_edges_from(u):
          temp_weight = distances[u] + graph.get_weight(u, v)
          if temp_weight < distances[v]:
            distances[v] = -math.inf
            preds[v] = u
            new_cycle = True
      if not new_cycle:
        break

  return distances, preds
