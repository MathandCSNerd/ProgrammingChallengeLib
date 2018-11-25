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

#include <iostream>
#include "../mstdlib/mstdlib.h"

using namespace std;
using namespace mstdlib;

int main() {
  int a = 4, b = 8;

  //calculates the gcd and lcm of 8 and 124
  cout << gcd(8, 124) << endl;
  cout << lcm(8, 124) << endl;

  //log base 2 of 128
  cout << log(2, 128) << endl;

  //the inverse of 8, modulo 124
  cout << InverseMod(8, 124) << endl;

  //raises 2 to the 8th power in an efficient manner
  cout << IntPow((unsigned long long)2, (unsigned long long)8) << endl;

  //divides a and b by their gcd for use with fractions
  Simplify(a, b);
  cout << a << ' ' << b << endl;

  //counts the number of digits in a
  cout << CountDigits(a) << endl;

  //calculates 3 factorial
  cout << Factorial(3) << endl;

  //returns nCk, and nPk
  //does so in a manner which emphasises precision
  cout << PrecisenChoosek(2, 5) << endl;
  cout << PrecisenPermk(2, 5) << endl;

  //calculates binomial pmf
  cout << Binomial(2, 5, 2) << endl;

  //performs the sum from 1 to 6
  //O(1) time
  cout << Sum(6) << endl;

  //performs the sum 1^2+2^2+...6^2
  //O(1) time
  cout << SquareSum(6) << endl;

  //performs the sum 1^3+2^3+...6^3
  //O(1) time
  cout << CubeSum(6) << endl;

  //performs the sum from 1+3+5 (1 to 6 by twos)
  //O(1) time
  cout << SumBy(6, 2) << endl;

  //checks if 8 is a prime number
  cout << IsPrime(8) << endl;

  //returns a vector of primes up to 10
  auto l = NormalPrimeSieve(10);
  for (auto it : l) cout << it << ' ';
  cout << endl;

  //returns the prime factorization of 10
  auto fac = Factor(10);
  for (auto it : fac) cout << "(" << it.first << ", " << it.second << ") ";
  cout << endl;

  //returns the divisor sum of 10 (using the prime factorization)
  cout << DivisorSum(fac) << endl;

  //checks if 10 is a triangular number
  cout << IsTri(10) << endl;

  //finds the digit sum of 23 (2+3)
  //  and the square digit sum of 23 (2^2 + 3^2)
  cout << DigitSum(23) << ' ' << SquareDigitSum(23) << endl;
  return 0;
}
