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


import multiDimArray as md

class DirectedGraph:
  """A class which represents a directed graph with weighted edges"""
  _contents=None
  _size=None
  _nullval=None
  def __init__(self, newsize, nullval=None):
    self.resize(newsize)
    self._nullval = nullval

  def resize(self, newsize):
    self._contents=md.full((newsize, newsize),self._nullval)
    self._size = newsize

  def is_connected(self, x, y):
    return self.get_weight(x,y) != self._nullval

  def get_weight(self, x, y):
    return self._contents[x,y]

  def add_connection(self, x, y, val=1):
    self._contents[x,y] = val

  def rm_connection(self, x, y):
    self._contents[x,y] = self._nullval

  def get_edges_from(self, x):
    l=[]
    for i in range(self._size):
      if self.is_connected(x,i):
        l.append(i)
    return l

  def get_size(self):
    return self._size


class UndirectedGraph(DirectedGraph):
  def addConnection(self, x, y, val=1):
    super.add_connection(self, x, y, val)
    super.add_connection(self, y, x, val)

  def rmConnection(self, x, y):
    super.rm_connection(self, x, y)
    super.rm_connection(self, y, x)


class SparseDirectedGraph:
  """A class which represents a directed graph with weighted edges"""
  _contents=None
  _size=None
  def __init__(self, newsize):
    self.resize(newsize)

  def resize(self, newsize):
    self._contents=[None]*newsize
    for i in range(newsize):
      self._contents[i] = dict()
    self._size = newsize

  def is_connected(self, x, y):
    return y in self._contents[x]

  def get_weight(self, x, y):
    return (self._contents[x])[y]

  def add_connection(self, x, y, val=1):
    (self._contents[x])[y] = val

  def rm_connection(self, x, y):
    try:
      del(self._contents[x])[y]
    except:
      #I don't care that the connection already isn't in the graph
      pass

  def get_edges_from(self, x):
    return [ y for y in self._contents[x] ]

  def get_weights_from(self, x):
    return self._contents[x]

  def get_size(self):
    return self._size


class SparseUndirectedGraph(SparseDirectedGraph):
  def addConnection(self, x, y, val=1):
    super.add_connection(self, x, y, val)
    super.add_connection(self, y, x, val)

  def rmConnection(self, x, y):
    super.rm_connection(self, x, y)
    super.rm_connection(self, y, x)
