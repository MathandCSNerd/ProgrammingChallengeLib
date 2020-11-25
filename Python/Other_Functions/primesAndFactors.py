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

def _fermat_primality_test(x):
  return (pow(2, x - 1, x) != 1)

def _is_obvious_non_prime(x):
  return (x != 2 and ((x % 2) == 0 or x < 2)) or _fermat_primality_test(x)

def is_prime_sieveless(a):
  if _is_obvious_non_prime(a):
    return False
  for i in range(3,int(math.ceil(math.sqrt(a)))+1,2):
    if a % i == 0:
      return False
  return True

def _do_fact_div(number, divisor):
  count = 0
  while number % divisor == 0:
    count+=1
    number /= divisor
  return (count, number)

def factor_sieveless(x):
  l=[]
  if(x%2 == 0):
    count,x = _do_fact_div(x,2)
    l.append((2,count))

  for i in range(3,(int(sqrt(x)+1)),2):
    if(x == 0):
      break
    if x % i == 0:
      count,x = _do_fact_div(x,i)
      l.append((i,count))
  if(x != 0 and x != 1):
    l.append((x,1))
  return l

def list_factor(x, primes):
  factors=[]
  for i in primes:
    if x % i == 0:
      count,x = _do_fact_div(x,i)
      factors.append((i,count))
  if x != 0 and x != 1:
    factors.append((x,1))
  return factors

def euler_phi(factors):
  product = 1
  for i in factors:
    product *= (i[0]**i[1]-i[0]**(i[1]-1))
  return int(product)

def _arr_prime_sieve(max_num):
  max_num+=1 #easier than adding one everywhere
  l=[True]*(max_num)
  l[0] = False
  l[1] = False
  for i in range(4,max_num,2):
    l[i] = False
  for i in range(3,max_num,2):
    if l[i] == True:
      for i2 in range(2*i,max_num,i):
        l[i2] = False
  return l

def _prime_arr_to_list(arr):
  return_list = []
  for i in range(len(arr)):
    if arr[i] == True:
      return_list.append(i)
  return return_list

def get_primes(max_num):
  return _prime_arr_to_list(_arr_prime_sieve(max_num))

def divisor_count_factors(factors):
  prod = 1
  for it in l:
    prod *= (factors[1] + 1)
  return prod

def divisor_count(x, primeList):
  factors = list_factor(x, primeList)
  return divisor_count_factors(factors)

def divisor_sum_factors(factors):
  prod = 1
  for it in factors:
    prod *= (math.pow(it[0], it[1] + 1) - 1) / (it[0] - 1)
  return prod

def divisor_sum(x, primeList):
  factors = list_factor(x, primeList)
  return divisor_sum_factors(factors)


