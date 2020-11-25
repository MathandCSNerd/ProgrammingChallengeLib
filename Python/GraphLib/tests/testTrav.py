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


from simpleGraphTraversal import *
from graphContainers import *

mygraph = DirectedGraph(6)
mygraph.add_connection(0,5)
mygraph.add_connection(0,4)
mygraph.add_connection(5,4)
mygraph.add_connection(4,3)
mygraph.add_connection(3,2)
mygraph.add_connection(2,1)

#mygraph.add_connection(0,1)
#mygraph.add_connection(0,2)
#mygraph.add_connection(1,2)
#mygraph.add_connection(2,3)
#mygraph.add_connection(3,4)
#mygraph.add_connection(4,5)
print(depth_first_search(mygraph,0))
print(breadth_first_search(mygraph,0))
