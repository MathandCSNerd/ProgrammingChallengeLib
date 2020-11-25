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


class MultiDimArray:
  """A class which represent a multidimensional array"""
  _size=None
  _contents=None
  _shape=None
  _dimMult=None
  shape=None
  def __init__(self, newsize, newshape, newcontents):
    if len(newshape) == 0:
      raise ValueError('shape tuple cannot be empty')
    if newsize != len(newcontents):
      raise ValueError('array size does not conform to provided dimensions')
    self._shape = newshape
    self.shape = newshape
    self._size = newsize
    self._contents = newcontents
    self._dimMult=[1]*len(self._shape)
    for i in range(len(self._shape)-2, -1, -1):
      self._dimMult[i]*=(self._dimMult[i+1])*self._shape[i+1]

  def _copyArr(self, otherShape, otherContents):
    arr = MultiDimArray(otherShape,otherContents)

  def _validateKey(self, key):
    if len(self._shape) < len(key):
      return False
    for i in range(len(key)):
      if self._shape[i] <= key[i]:
        return False
    return True

  def _keyToIndex(self, key):
    if type(key) == int:
      key = [key]
    if not self._validateKey(key):
      raise IndexError("index does not exist in array")
    x=0
    for i in range(len(key)-1, -1, -1):
      x += key[i]*self._dimMult[i]
    return x

  def getSliceItem(self,key):
    arr = []
    start = key.start
    stop = key.stop
    step = key.step
    if start == None:
      start = 0
    if stop == None:
      stop = self._shape[0]
    if step == None:
      step = 1
    if type(self[start]) != MultiDimArray:
      for i in range(start, stop, step):
        arr.append(self[i])
      newShape = [len(arr)]
    else:
      for i in range(start, stop, step):
        arr += self[i]._contents[:]
        #print(self[i]._contents[:])
      newShape = (self[start].shape[:], stop - start)
    return MultiDimArray(len(arr), newShape, arr)

  def __getitem__(self, key):
    if type(key) == slice:
      return self.getSliceItem(key)
    index = self._keyToIndex(key)
    if type(key) == int:
      key = [key]
    retShape = self._shape[len(key):]
    if len(self._shape) == len(key):
      return self._contents[index]
    size=1
    for i in retShape:
      size *= i
    return MultiDimArray(size, retShape, self._contents[index:index+size])

  def __setitem__(self, key, value):
    index = self._keyToIndex(key)
    self._contents[index] = value


def zeros(shape):
  return full(shape,0)

def full(shape, value):
  if len(shape) == 0:
    raise ValueError('shape tuple cannot be empty')
  size = 1
  for i in shape:
    if i < 1:
      raise ValueError('no index can be of size < 1')
    size *= i
  contents = [value]*size
  #for testing purposes
  #tmpi=0
  #for i in range(len(contents)):
  #  contents[i]+=str(tmpi)
  #  tmpi+=1
  return MultiDimArray(size, shape, contents)
