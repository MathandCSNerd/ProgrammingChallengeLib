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
  InfNum() : finite(true) {}

  InfNum(const InfNum<type>& that) : finite(that.finite), num(that.num) {}

  InfNum(const type& that) { *this = that; }

  InfNum(const type& that, const bool& fin) : finite(fin), num(that) {}

  InfNum& operator=(const type& that) {
    Set(that);
    return *this;
  }

  InfNum& operator=(const InfNum<type>& that) {
    num = that.num;
    finite = that.finite;
    return *this;
  }

  InfNum operator+(const InfNum<type>& that) const {
    return InfNum(num + that.num, finite and that.finite);
  }

  InfNum operator+(const type& that) const {
    return InfNum(num + that, finite);
  }

  bool operator<(const InfNum<type>& that) const {
    return finite && (!that.finite || num < that.num);
  }

  bool operator==(const InfNum<type>& that) const {
    return (!finite and !that.finite) ||
           ((finite and that.finite) and num == that.num);
  }

  bool operator==(const type& that) const { return *this == InfNum(that); }

  bool operator!=(const type& that) const { return !(*this == InfNum(that)); }

  void MarkInfinite() { finite = false; }
  void MarkFinite() { finite = true; }

  void Set(type newNum) {
    num = newNum;
    MarkFinite();
  }

  type& GetNum() { return num; }

  const type& CGetNum() const { return num; }

  bool IsFinite() const { return finite; }
  bool IsInfinite() const { return !finite; }

  template <class numType>
  friend std::ostream& operator<<(std::ostream& out,
                                  const InfNum<numType>& that);

 private:
  bool finite;
  type num;
};

template <class type>
std::ostream& operator<<(std::ostream& out, const InfNum<type>& that) {
  if (!that.finite)
    out << "inf";
  else
    out << that.num;
  return out;
}

using InfInt = InfNum<long long>;
using InfFloat = InfNum<long double>;

#endif
