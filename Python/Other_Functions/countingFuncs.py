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

def n_choose_k(n, k):
  if n < k:
    n, k = k, n
  return math.factorial(n) // (math.factorial(n-k) * math.factorial(k))

def n_perm_k(n, k):
  if n < k:
    n, k = k, n
  return math.factorial(n) // math.factorial(n-k)

def binomial(n, k, p):
  return math.pow(p, k) * math.pow(1 - p, n - k) * n_choose_k(n, k)

