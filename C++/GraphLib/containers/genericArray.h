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

#ifndef GENERIC_ARRAY
#define GENERIC_ARRAY
#include <algorithm>
#include <list>

#include <iostream>

template <class type>
class GenericArray {
 protected:
  int size;
  int rsize;
  std::vector<type*> arr;
  type dummy;

  virtual int CalcRSize(int n) const = 0;
  virtual int CoordsToIndex(int row, int col) const = 0;

 public:
  class iterator;

  GenericArray();
  GenericArray(int newsize);
  GenericArray(const GenericArray<type>& that);
  const GenericArray& operator=(const GenericArray<type>& that);
  virtual ~GenericArray();
  void ChangeSize(int newsize);
  const type& Get(int x, int y) const;
  const type& GetIndex(int x) const;
  void Alloc(int x);
  void Set(int x, int y, const type& val);
  void SetIndex(int x, const type& val);
  type& Access(int x, int y);
  type& operator()(int x, int y);
  void Unset(int x, int y);
  bool Exists(int x, int y) const;
  int Size() const;
  int RSize() const;
  void FastSet(std::list<type> mylist);
  void FastSet(type** myArr);
  int FindNextIndex(int row, int index) const;

  iterator begin(int row) const;
  iterator end(int row) const;

  // requires extraction and addition operators
  // remember SFINAE so feel free to ignore these
  void Output() const;
  GenericArray<type>& ElementWiseAdd(const GenericArray<type>& that);
  GenericArray<type>& operator+=(const GenericArray<type>& that);
};

// this iterator iterates over edges, not neccessarily all indices
template <class type>
class GenericArray<type>::iterator : public std::forward_iterator_tag {
 private:
  int row;
  int index;
  GenericArray<type> const* data;

 public:
  int Node() const { return index; }
  const type& Weight() const { return data->Get(row, index); }
  iterator() : index(0), row(0), data(nullptr) {}
  iterator(int newRow, int newIndex, const GenericArray<type>* dataPtr)
      : row(newRow), index(newIndex), data(dataPtr) {}
  iterator& operator=(const iterator& that) {
    index = that.index;
    row = that.row;
    data = that.data;
    return *this;
  }
  iterator(const iterator& that) { *this = that; }

  const iterator* operator->() const { return this; }

  bool operator==(const iterator& that) const {
    return index == that.index && row == that.row;
  }
  bool operator!=(const iterator& that) const { return !(*this == that); }

  iterator& operator++() {
    index = data->FindNextIndex(row, index);
    return *this;
  }
};

template <class type>
GenericArray<type>::GenericArray() {
  size = 0;
  rsize = 0;
}

template <class type>
GenericArray<type>::GenericArray(int newsize) {
  ChangeSize(newsize);
}

template <class type>
GenericArray<type>::GenericArray(const GenericArray<type>& that) {
  (*this) = that;
}

template <class type>
const GenericArray<type>& GenericArray<type>::operator=(
    const GenericArray<type>& that) {
  ChangeSize(that.size);
  FastSet(that.arr);
  return *this;
}

template <class type>
GenericArray<type>::~GenericArray() {
  for (int i = 0; i < rsize; ++i) delete arr[i];
}

template <class type>
void GenericArray<type>::ChangeSize(int newsize) {
  size = newsize;
  rsize = CalcRSize(size);
  arr.resize(rsize);
  for (int i = 0; i < rsize; ++i) arr[i] = nullptr;
}

template <class type>
const type& GenericArray<type>::Get(int x, int y) const {
  return GetIndex(CoordsToIndex(x, y));
}

template <class type>
const type& GenericArray<type>::GetIndex(int x) const {
  return *arr[x];
}

template <class type>
void GenericArray<type>::Alloc(int x) {
  if (arr[x] == nullptr) arr[x] = new type;
}

template <class type>
void GenericArray<type>::Set(int x, int y, const type& val) {
  SetIndex(CoordsToIndex(x, y), val);
}

template <class type>
void GenericArray<type>::SetIndex(int x, const type& val) {
  Alloc(x);
  *(arr[x]) = val;
}

template <class type>
type& GenericArray<type>::Access(int x, int y) {
  return *arr[(CoordsToIndex(x, y))];
}

template <class type>
type& GenericArray<type>::operator()(int x, int y) {
  return Access(x, y);
}

template <class type>
void GenericArray<type>::Unset(int x, int y) {
  delete[] arr[CoordsToIndex(x, y)];
  arr[CoordsToIndex(x, y)] = nullptr;
}

template <class type>
bool GenericArray<type>::Exists(int x, int y) const {
  auto index = CoordsToIndex(x, y);
  if(index < 0 or index >= rsize)
    return false;
  return arr[index] != nullptr;
  //return arr[CoordsToIndex(x, y)] != nullptr;
}

template <class type>
int GenericArray<type>::Size() const {
  return size;
}

template <class type>
int GenericArray<type>::RSize() const {
  return rsize;
}

template <class type>
void GenericArray<type>::FastSet(std::list<type> mylist) {
  int i = -1;
  for (auto it = mylist.begin(); (it != mylist.end()) && (++i < rsize); ++it)
    SetIndex(i, **it);
}

template <class type>
void GenericArray<type>::FastSet(type** myArr) {
  for (int i = 0; ++i < rsize; ++i) SetIndex(i, *myArr[i]);
}

template <class type>
typename GenericArray<type>::iterator GenericArray<type>::begin(int x) const {
  return iterator(x, FindNextIndex(x, -1), this);
}

template <class type>
typename GenericArray<type>::iterator GenericArray<type>::end(int x) const {
  return iterator(x, size, this);
}

template <class type>
int GenericArray<type>::FindNextIndex(int row, int index) const {
  ++index;
  while (!Exists(row, index) && index < size) {
    ++index;
  }
  return index;
}

template <class type>
void GenericArray<type>::Output() const {
  using namespace std;
  for (int i = 0; i < size; ++i) {
    for (int i2 = 0; i2 < size; ++i2) {
      if (Exists(i, i2))
        cout << Get(i, i2);
      else
        cout << "-";
      cout << ' ';
    }
    cout << endl;
  }
}

template <class type>
GenericArray<type>& GenericArray<type>::ElementWiseAdd(
    const GenericArray<type>& that) {
  for (int i = 0; i < rsize && i < that.rsize; ++i) (*arr[i]) += (*that.arr[i]);
  return *this;
}

template <class type>
GenericArray<type>& GenericArray<type>::operator+=(
    const GenericArray<type>& that) {
  return ElementWiseAdd(that);
}

#endif
