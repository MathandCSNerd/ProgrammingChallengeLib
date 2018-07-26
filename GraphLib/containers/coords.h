/* Copyright 2018 Matthew Macallister
 *
 * This file is part of ProgrammingChallengeLib.
 *
 * ProgrammingChallengeLib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ProgrammingChallengeLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ProgrammingChallengeLib.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef COORD_CLASS
#define COORD_CLASS

#include <set>

template <class number>
class coords : public std::pair<number, number> {
 public:
  const number& X() const { return std::pair<number, number>::first; }
  const number& Y() const { return std::pair<number, number>::second; }

  void Set(const number x, const number y) {
    std::pair<number, number>::first = x;
    std::pair<number, number>::second = y;
  }
};

#endif
