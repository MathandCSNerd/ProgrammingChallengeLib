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
from sssp import *
from graphContainers import *


inp = [ int(x) for x in input().split(" ") ]
while not (inp[0] == 0 and inp[1] == 0 and inp[2] == 0 and inp[3] == 0):
  #mygraph = DirectedGraph(inp[0])
  mygraph = SparseDirectedGraph(inp[0])
  for i in range(inp[1]):
    inp2 = [ int(x) for x in input().split(" ") ]
    #don't replace shorter edges with longer
    if not mygraph.is_connected(inp2[0], inp2[1]) or inp2[2] < mygraph.get_weight(inp2[0], inp2[1]):
      mygraph.add_connection(inp2[0], inp2[1], inp2[2])
  for i in range(inp[2]):
    inp3 = input()
    if i == 0:
      a,b,c = dstra_sssp(mygraph, inp[3], int(inp3))
    else:
      a,b,c = dstra_sssp(mygraph, inp[3], int(inp3), b, c)
    if a == math.inf:
      print("Impossible")
    else:
      print(a)
  inp = [ int(x) for x in input().split(" ") ]
  if (not (inp[0] == 0 and inp[1] == 0 and inp[2] == 0 and inp[3] == 0)):
    print()

