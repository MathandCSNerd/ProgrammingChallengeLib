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

def get_oct_x(i):
  return math.ceil(math.sqrt(float(i) / 3))

def oct_sum_n(i):
  return i * (3 * i - 2)


def get_hept_x(i):
  return math.ceil(math.sqrt(float(i) * float(2) / 5))

def hept_sum_n(i):
  return (i * (5 * i - 3)) / 2


def get_hex_x(i):
  return math.ceil(math.sqrt(float(i) / 2))

def hex_sum_n(i):
  return 2 * i * i - i


def get_pent_x(i):
  return math.ceil(math.sqrt(float(i) * float(2) / 3))

def pent_sum_n(i):
  return (3 * (i * i) - i) / 2


def get_tri_x(i):
  return math.floor(math.sqrt(i * 2))

def tri_sum_n(i):
  return ((i * (i + 1)) / 2)


def is_oct(i):
  temp = get_oct_x(i)
  return oct_sum_n(temp) == i

def is_hept(i):
  temp = get_hept_x(i)
  return hept_sum_n(temp) == i

def is_hex(i):
  temp = get_hex_x(i)
  return hex_sum_n(temp) == i

def is_pent(i):
  temp = get_pent_x(i)
  return pent_sum_n(temp) == i

def is_tri(i):
  temp = get_tri_x(i)
  return tri_sum_n(temp) == i

def is_square(i):
  temp = math.sqrt(i)
  return (temp * temp) == i



