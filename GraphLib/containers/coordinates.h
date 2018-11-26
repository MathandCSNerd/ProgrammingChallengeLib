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

#ifndef COORD_CLASS
#define COORD_CLASS

#include <iostream>
#include <utility>
#include <vector>

template <class number>
class Coordinates;

template <class number>
std::ostream& operator<<(std::ostream& out, const Coordinates<number>& that);

template <class number>
class Coordinates {
 public:
  Coordinates() { Set({0, 0}); }
  Coordinates(long long a, long long b) { Set({a, b}); }
  Coordinates(std::initializer_list<number> coordList) { Set(coordList); }

  number& X() { return myCoords[1]; }
  number& Y() { return myCoords[0]; }

  number& Row() { return myCoords[0]; }
  number& Col() { return myCoords[1]; }

  const number& CRow() const { return myCoords[0]; }
  const number& CCol() const { return myCoords[1]; }

  number Get(size_t place) const {
    if (place < Size()) return myCoords[place];
  }

  number& operator()(size_t place) {
    if (place < Size()) return myCoords[place];
  }

  void Resize(size_t i){
    myCoords.resize(i);
  }

  size_t Size() const { return myCoords.size(); }

  void Set(std::initializer_list<number> coordList) {
    myCoords.clear();
    myCoords.reserve(coordList.size());

    for (auto it : coordList) myCoords.push_back(it);
  }

  void Set(const number row, const number col) { Set({row, col}); }

  void SetXY(const number x, const number y) { Set({y, x}); }

  number CmpCoords(const Coordinates<number>& b) const {
    if (Size() != b.Size()) return Size() - b.Size();
    for (size_t i = 0; i < Size(); ++i) {
      if (myCoords[i] != b.myCoords[i]) return myCoords[i] - b.myCoords[i];
    }
    return 0;
  }

  bool operator<(const Coordinates<number>& b) const {
    return CmpCoords(b) < 0;
  }
  bool operator>(const Coordinates<number>& b) const {
    return CmpCoords(b) > 0;
  }

  bool operator==(const Coordinates<number>& b) const {
    return CmpCoords(b) == 0;
  }
  bool operator!=(const Coordinates<number>& b) const { return !(*this == b); }

  friend std::ostream& operator<<<number>(std::ostream& out,
                                          const Coordinates<number>& that);

 private:
  std::vector<number> myCoords;
};

template <class number>
std::ostream& operator<<(std::ostream& out, const Coordinates<number>& that) {
  out << "(";
  if (that.myCoords.size()) {
    out << that.myCoords[0];
    for (auto it = that.myCoords.begin() + 1; it != that.myCoords.end(); ++it)
      out << ", " << *it;
  }
  out << ")";
  return out;
}


template <class number>
bool IterateCoords(Coordinates<number>& myarr, const Coordinates<number>& testarr){
  size_t i;

  for (i = 0; i < myarr.Size() && (myarr(i) == testarr.Get(i)-1); ++i)
    ;

  if (i == myarr.Size())
    return false;

  else {
    ++myarr(i);
    if(i != 0){
      myarr(0) = 0;
      for (--i; i > 0; --i) (myarr(i)) = 0;
    }
  }
  return true;
}


#endif
