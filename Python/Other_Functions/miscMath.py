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


import math

def simplify_frac(a, b):
  tmp = math.gcd(a, b)
  return (a/tmp, b/tmp)

def count_digits(i):
  return len(str(i))

def sum_to_n_by_m(n, m):
  return sum_to_n(n/m)*m

def sum_to_n(n):
  return (n*(n+1))/2

def square_sum_to_n(n):
  return (n * (n + 1) * (2 * n + 1)) / 6

def cube_sum_to_n(n):
  return (n * n * (n + 1) * (n + 1)) / 4

def digit_sum(x):
  sam = 0
  for let in str(x):
    sam += int(let)
  return sam

def square_digit_sum(x):
  sam = 0
  for let in str(x):
    sam += int(let)**2
  return sam


