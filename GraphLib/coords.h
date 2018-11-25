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

#include <utility>

// This class mostly exists for readability purposes.
// In esscense it's just a slightly clearer interface
// on top of a pair for its specific purpose.
template <class number>
class CoordinatePair {
 public:
  CoordinatePair() { Set(0, 0); }
  CoordinatePair(long long a, long long b) { Set(a, b); }

  number& X() { return myCoords.second; }
  number& Y() { return myCoords.first; }

  number& Row() { return myCoords.first; }
  number& Col() { return myCoords.second; }

  const number& CRow() const { return myCoords.first; }
  const number& CCol() const { return myCoords.second; }

  void Set(const number row, const number col) {
    myCoords.first = row;
    myCoords.second = col;
  }

  void SetXY(const number x, const number y) {
    myCoords.first = y;
    myCoords.second = x;
  }

  bool operator<(const CoordinatePair<number>& b) const {
    return myCoords < b.myCoords;
  }
  bool operator==(const CoordinatePair<number>& b) const {
    return myCoords == b.myCoords;
  }
  bool operator>(const CoordinatePair<number>& b) const {
    return myCoords > b.myCoords;
  }
  bool operator!=(const CoordinatePair<number>& b) const {
    return myCoords != b.myCoords;
  }

  template <class numberType>
  friend std::ostream& operator<<(std::ostream& out,
                                  const CoordinatePair<number>& that);

 private:
  std::pair<number, number> myCoords;
};

template <class numberType>
std::ostream& operator<<(std::ostream& out,
                         const CoordinatePair<numberType>& that) {
  out << "(" << that.CRow() << ", " << that.CCol() << ")";
  return out;
}

#endif
