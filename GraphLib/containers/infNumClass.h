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

#ifndef NON_FINITE_NUM_CLASS
#define NON_FINITE_NUM_CLASS

#include <iostream>

template <class type>
class InfNum {
 public:
  InfNum() : infinite(true) {}

  InfNum(const InfNum<type>& that) : infinite(that.infinite), num(that.num) {}

  InfNum(const type& that) { *this = that; }

  InfNum(const type& that, const bool& fin) : infinite(fin), num(that) {}

  InfNum& operator=(const type& that) {
    Set(that);
    return *this;
  }

  InfNum& operator=(const InfNum<type>& that) {
    num = that.num;
    infinite = that.infinite;
    return *this;
  }

  InfNum operator+(const InfNum<type>& that) const {
    /*int answer = true;
    if (infinite == that.infinite)  // both are finite or infinite
      answer = infinite;

    else if (IsFinite())       // this is finite
      answer = that.infinite;  // the other is not

    else                  // either the second is finite
      answer = infinite;  // or both are opposite finite

    return InfNum(num + that.num, answer);*/

    // note: the behaviour of addition is undefined for adding
    // infinity to negative infinity
    return InfNum(num + that.num,
                  (IsInfinite() || that.IsInfinite()) +
                      (IsNegInfinite() || that.IsNegInfinite()) * -1);
  }

  InfNum operator+(const type& that) const {
    return InfNum(num + that, infinite);
  }

  bool operator<(const InfNum<type>& that) const {
    /*if(IsFinite() && that.IsFinite())
      return num < that.num;
    else
      return infinite < that.infinite;*/
    //-1 < 0 < 1 just as
    // negative infinite < infinite < infinite

    return ((IsFinite() && that.IsFinite() && num < that.num) or
            infinite < that.infinite);
    // return infinite && (!that.infinite || num < that.num);
  }

  bool operator==(const InfNum<type>& that) const {
    return (infinite == that.infinite) and (!IsFinite() or (num == that.num));
  }

  bool operator==(const type& that) const { return *this == InfNum(that); }

  bool operator!=(const type& that) const { return !(*this == InfNum(that)); }

  void MarkInfinite() { infinite = true; }
  void MarkFinite() { infinite = false; }
  void MarkNegInfinite() { infinite = -1; }

  void Set(type newNum) {
    num = newNum;
    MarkFinite();
  }

  type& GetNum() { return num; }

  const type& CGetNum() const { return num; }

  bool IsFinite() const { return infinite == 0; }
  bool IsInfinite() const { return infinite == 1; }
  bool IsNegInfinite() const { return infinite == -1; }

  bool IsInfinity() const { return infinite == 1; }
  bool IsNegInfinity() const { return infinite == -1; }

  template <class numType>
  friend std::ostream& operator<<(std::ostream& out,
                                  const InfNum<numType>& that);

 private:
  int infinite;
  type num;
};

template <class type>
std::ostream& operator<<(std::ostream& out, const InfNum<type>& that) {
  if (that.IsInfinity())
    out << "inf";
  else if (that.IsNegInfinity())
    out << "-inf";
  else
    out << that.num;
  return out;
}

using InfInt = InfNum<long long>;
using InfFloat = InfNum<long double>;

#endif
