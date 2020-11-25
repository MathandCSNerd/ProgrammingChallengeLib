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

def lcm(a, b):
  if a != 0 or b != 0:
    tmp = a*b
    if tmp < 0:
      tmp *= -1
    return tmp / math.gcd(a,b)
  return 0

def xgcd(a, b):
  s, old_s = (0,1)
  t, old_t = (1,0)
  r, old_r = (b,a)
  while r != 0:
    q = old_r / r
    old_r, r = (r, old_r - q * r)
    old_s, s = (s, old_s - q * s)
    old_t, t = (t, old_t - q * t)
  return (old_r, old_s, old_t)

def inverse_mod(a, b):
  x = xgcd(a,b)[1]
  if x < 0:
    x += b
  return x


