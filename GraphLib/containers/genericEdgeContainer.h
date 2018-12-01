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

// TODO: make set,unset,exists all pure virtual
// make 3 child classes for set, vector, and list
// make a second version for multigraph with the list type
//  use set insert
//  ensure the vector is constantly sorted and use lower_bound
//  as far as the list is concerned... use list insert and list find I guess...
//  set should overwrite first if the entry exists

#ifndef EDGE_CONT
#define EDGE_CONT

#include "edgeNode.h"

// for Output function
#include <iostream>

template <class STLContainerType, class weightType>
class EdgeContainer {
 public:
  typedef typename STLContainerType::iterator iterator;

  EdgeContainer();
  EdgeContainer(const int newsize);
  EdgeContainer(const EdgeContainer<STLContainerType, weightType>& that);
  const EdgeContainer& operator=(const EdgeContainer& that);
  virtual ~EdgeContainer();
  void ChangeSize(int newsize);
  int Size() const;
  virtual void Set(int x, int y, const weightType& val);
  virtual void Unset(int x, int y);
  virtual bool Exists(int x, int y) const;
  virtual GenericEdgeNode<weightType>& Access(int x, int y);
  iterator begin(int row) const;
  iterator end(int row) const;

  void Output() const;

 protected:
  virtual void AddEdge(int x, int y, const weightType& val);  // = 0;
  virtual iterator FindEdge(int x, int y) const = 0;
  STLContainerType* myContainer;

 private:
  int size;
};

template <class STLContainerType, class weightType>
EdgeContainer<STLContainerType, weightType>::EdgeContainer()
    : myContainer(nullptr), size(0) {}

template <class STLContainerType, class weightType>
EdgeContainer<STLContainerType, weightType>::EdgeContainer(int newsize)
    : size(newsize), myContainer(new STLContainerType[newsize]) {}

template <class STLContainerType, class weightType>
EdgeContainer<STLContainerType, weightType>::EdgeContainer(
    const EdgeContainer<STLContainerType, weightType>& that)
    : myContainer(NULL) {
  *this = that;
}

template <class STLContainerType, class weightType>
const EdgeContainer<STLContainerType, weightType>&
EdgeContainer<STLContainerType, weightType>::operator=(
    const EdgeContainer<STLContainerType, weightType>& that) {
  ChangeSize(that.size);
  for (int i = 0; i < size; ++i) myContainer[i] = that.myContainer[i];
}

template <class STLContainerType, class weightType>
EdgeContainer<STLContainerType, weightType>::~EdgeContainer() {
  delete[] myContainer;
}

template <class STLContainerType, class weightType>
void EdgeContainer<STLContainerType, weightType>::ChangeSize(int newsize) {
  delete[] myContainer;
  size = newsize;
  myContainer = new STLContainerType[size];
}

template <class STLContainerType, class weightType>
int EdgeContainer<STLContainerType, weightType>::Size() const {
  return size;
}

template <class STLContainerType, class weightType>
void EdgeContainer<STLContainerType, weightType>::Set(int x, int y,
                                                      const weightType& val) {
  auto it = FindEdge(x, y);
  if (it != myContainer[x].end()) {
    if (val < it->Weight()) it->SetWeight(val);
  } else
    AddEdge(x, y, val);
}

template <class STLContainerType, class weightType>
void EdgeContainer<STLContainerType, weightType>::Unset(int x, int y) {
  auto it = FindEdge(x, y);
  if (it != myContainer[x].end()) myContainer[x].erase(it);
}

template <class STLContainerType, class weightType>
bool EdgeContainer<STLContainerType, weightType>::Exists(int x, int y) const {
  auto it = FindEdge(x, y);
  return (it != myContainer[x].end());
}

template <class STLContainerType, class weightType>
GenericEdgeNode<weightType>&
EdgeContainer<STLContainerType, weightType>::Access(int x, int y) {
  return *FindEdge(x, y);
}

template <class STLContainerType, class weightType>
typename EdgeContainer<STLContainerType, weightType>::iterator
EdgeContainer<STLContainerType, weightType>::begin(int row) const {
  return myContainer[row].begin();
}

template <class STLContainerType, class weightType>
typename EdgeContainer<STLContainerType, weightType>::iterator
EdgeContainer<STLContainerType, weightType>::end(int row) const {
  return myContainer[row].end();
}

template <class STLContainerType, class weightType>
void EdgeContainer<STLContainerType, weightType>::Output() const {
  for (int i = 0; i < size; ++i) {
    std::cout << i << ":  ";
    for (auto it : myContainer[i])
      std::cout << "(" << it.Node() << ", " << it.Weight() << ")  ";
    std::cout << std::endl;
  }
}

template <class STLContainerType, class weightType>
void EdgeContainer<STLContainerType, weightType>::AddEdge(
    int x, int y, const weightType& val) {
  myContainer[x].push_back(GenericEdgeNode<weightType>(y, val));
}

#endif
