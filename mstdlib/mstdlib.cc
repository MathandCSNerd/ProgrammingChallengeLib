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

/*
 *  mattstdlib.cc
 *
 *  Copyright (C) 2018 Matthew Mac Allister
 *
 *  This file contains definitions for some standard math functions
 *  as well as a couple others.
 */

#include "mstdlib.h"

namespace mstdlib{

//**************************
// simple math functions
//**************************
long long gcd(long long a, long long b) {
  if (!b)
    return a;
  else
    return gcd(b, a % b);
}

long long lcm(long long a, long long b) {
  if (a || b) {
    long long tmp = a * b;
    if (tmp < 0) tmp *= -1;
    return tmp / gcd(a, b);
  } else {
    return 0;
  }
}

long double log(long double base, long double num) {
  return log10l(num) / log10l(base);
}

void PAssign(long long& var1, long long& var2, long long val1, long long val2) {
  var1 = val1;
  var2 = val2;
}

std::vector<long long> xgcd(long long a, long long b) {
  using namespace std;
  vector<long long> vec;
  long long s = 0, old_s = 1;
  long long t = 1, old_t = 0;
  long long r = b, old_r = a;
  long long q;
  while (r) {
    q = old_r / r;
    PAssign(old_r, r, r, old_r - q * r);
    PAssign(old_s, s, s, old_s - q * s);
    PAssign(old_t, t, t, old_t - q * t);
  }
  vec.push_back(old_r);
  vec.push_back(old_s);
  vec.push_back(old_t);
  return vec;
}

long long InverseMod(long long a, long long b) {
  auto l = xgcd(a, b);
  if (l[1] < 0) l[1] += b;
  return l[1];
}

// TODO: would probably be a better idea to do the ol' sucessive
// squaring algorithm it would be more accurate at least
long long IntPow(long long base, long long exp) {
  return (long long)(floorl(powl(base, exp) + 0.5));
}

//**************************
// simple common functions
//**************************
void swap(long long& a, long long& b) {
  long long tmp(a);
  a = b;
  b = tmp;
}

void Simplify(long long& a, long long& b) {
  long long tmp = gcd(a, b);
  a /= tmp;
  b /= tmp;
}

int CountDigits(unsigned long long i) {
  int ret = (ceil(log10l(i)));
  if (ret == (log10l(i))) ++ret;
  return ret;
}

//**************************
// counting functions
//**************************
long long Factorial(int x) {
  long long sum = 1;
  for (int i = x; i > 1; --i) sum *= i;
  return sum;
}

long long NChoosek(long long n, long long k) {
  return Factorial(n) / (Factorial(n - k) * Factorial(k));
}

long long NPermk(long long n, long long k) { return Factorial(n) / (Factorial(n - k)); }

long long PrecisenChoosek(long long n, long long k) {
  long long m;
  if (k < n - k)
    m = (n - k);
  else
    m = k;

  k = n - m;
  long long sumn = 1;
  long long sumd = 1;

  int i = m + 1, i2 = 1;
  while (i <= n && i2 <= k) {
    sumn *= i++;
    sumd *= i2++;
    Simplify(sumn, sumd);
  }
  return sumn / sumd;
}

long long PrecisenPermk(long long n, long long k) {
  long long sum = 1;
  for (int i = n; i > (n - k); --i) sum *= i;
  return sum;
}

long double Binomial(int k, int n, long double p) {
  return powl(p, k) * powl(1 - p, n - k) * PrecisenChoosek(n, k);
}

//**************************
// summing functions
//**************************
long long Sum(long long n) { return (n * (n + 1)) / 2; }

long long SquareSum(long long n) { return (n * (n + 1) * (2 * n + 1)) / 6; }

long long CubeSum(long long n) { return (n * n * (n + 1) * (n + 1)) / 4; }

long long SumBy(long long n, long long m) { return m * Sum(n / m); }

//**************************
// primes and factoring
//**************************
bool LongIsPrime(long long x) {
  if (x == 2)
    return true;
  else if (!(x % 2) || x < 2)
    return false;

  for (long long i = 3; i <= ceil(sqrt(x)) + 1 && i < x; i += 2)
    if (!(x % i)) return false;

  return true;
}

bool IsCachePrime(int x) {
  const static int MAXPSIZE = 100000;
  static bool cPrime[MAXPSIZE];
  static bool isPrime[MAXPSIZE];
  static bool first = true;
  if (first) {
    memset(cPrime, 0, sizeof(bool) * MAXPSIZE);
    memset(isPrime, 0, sizeof(bool) * MAXPSIZE);
    first = false;
  }
  if (x < 2) return false;
  if (x == 2) return true;
  if (x < MAXPSIZE) {
    if (!cPrime[x]) {
      isPrime[x] = LongIsPrime(x);
      cPrime[x] = true;
    }
    return isPrime[x];
  }
  return LongIsPrime(x);
}

bool IsPrime(long long x, const std::vector<long long>& primeSet) {
  if (!(x % 2)) return false;

  auto it = primeSet.end();
  --it;
  if (*(it) >= x)
    return binary_search(primeSet.begin(), primeSet.end(),
                         x);
  else {
    //TODO: add the 3 argument pow function from python
    // if(pow(2,x-1,x) != 1) //fermat primality test
    //  return false;
    auto l = std::move(PFactor(x, primeSet));
    return l.size() == 1 and l.begin()->second == 1;
  }
}

std::vector<long long> listPrimeSieve(long long MAX_NUM) {
  std::vector<long long> primeList;
  // 1.15 is due to the maximum error in the approximate prime counting function
  primeList.reserve(1.15 * ((long double)MAX_NUM / logl(MAX_NUM)));
  long i;
  auto it = primeList.begin();
  primeList.push_back(2);
  for (i = 3; i <= MAX_NUM; i += 2) {
    for (it = primeList.begin(); it != primeList.end() && ((i % (*it))); ++it)
      ;
    if (it == primeList.end()) primeList.push_back(i);
  }
  return primeList;
}


bool* arrPrimeSieve(long long MAX_NUM) {
  bool* arr = new bool[MAX_NUM];
  memset(arr, true, MAX_NUM * sizeof(bool));

  for (long long i = 4; i < MAX_NUM; i += 2) arr[i] = false;
  for (long long i = 3; i <= sqrt(MAX_NUM); i += 2) {
    if (arr[i])
      for (long long i2 = i * 2; i2 < MAX_NUM; i2 += i) arr[i2] = false;
  }
  return arr;
}

std::vector<long long> PrimeArrToVec(bool* parr, long long MAX_NUM) {
  using namespace std;
  vector<long long> pset;
  if (MAX_NUM >= 2) pset.push_back(2);
  for (long long i = 3; i < MAX_NUM; i += 2)
    if (parr[i]) pset.push_back(i);
  return pset;
}

std::vector<long long> NormalPrimeSieve(long long MAX_NUM) {
  bool* arr = arrPrimeSieve(MAX_NUM);
  return std::move(PrimeArrToVec(arr, MAX_NUM));
}

std::pair<long long, long long> DoFactDiv(long long& x, const long long i) {
  using namespace std;
  pair<long long, long long> tmp;
  long long count = 0;
  while (x % i == 0) {
    ++count;
    x /= i;
  }
  tmp.first = i;
  tmp.second = count;
  return tmp;
}

std::list<std::pair<long long, long long>> Factor(long long x) {
  using namespace std;
  list<pair<long long, long long>> factors;
  if (x && !(x % 2)) factors.push_back(DoFactDiv(x, 2));
  for (long long i = 3; i < (long long)(sqrt(x) + 1); i += 2) {
    if (!(x % i)) factors.push_back(DoFactDiv(x, i));
  }
  if (x && x != 1) factors.push_back(DoFactDiv(x, x));
  return factors;
}

std::list<std::pair<long long, long long>> PFactor(
    long long x, const std::vector<long long>& primeList) {
  using namespace std;
  list<pair<long long, long long>> factors;
  long long sq = sqrtl(x) + 0.5;
  for (auto it = primeList.begin(); it != primeList.end() && (*it <= (sq));
       ++it) {
    if (!(x % (*it))) factors.push_back(DoFactDiv(x, *it));
  }
  if (x && x != 1) factors.push_back(DoFactDiv(x, x));
  return factors;
}

long long EulerPhi(std::list<std::pair<long long, long long>>& l) {
  long long prod = 1;
  long long a, p;
  for (auto it = l.begin(); it != l.end(); ++it) {
    a = it->first;
    p = it->second;
    prod *= (pow(a, p) - pow(a, p - 1));
  }
  return prod;
}

long long EulerPhi(long long x) {
  if (x < 1) return 0;

  auto l = std::move(Factor(x));

  return EulerPhi(l);
}

std::list<long long> FactorsToDivisors(
    std::list<std::pair<long long, long long>>& l) {
  using namespace std;
  long long* exps = new long long[l.size()];
  long long* tmps = new long long[l.size()];
  unsigned long long i;
  long long prod;
  list<long long> newl;

  for (i = 0; i < l.size(); ++i) tmps[i] = 0;

  i = -1;
  for (auto it : l) exps[++i] = it.second;

  do {
    i = -1;
    prod = 1;
    for (auto it : l) prod *= IntPow(it.first, tmps[++i]);
    newl.push_back(prod);
  } while (IterateArr(exps, exps + l.size(), tmps));

  delete[] exps;
  delete[] tmps;

  return newl;
}

long long DivisorCount(long long x, const std::vector<long long>& primeList) {
  auto l = PFactor(x, primeList);
  long long prod = 1;
  for (auto it : l) prod *= (it.second + 1);
  return prod;
}

long long DivisorCount(long long x) {
  auto l = Factor(x);
  long long prod = 1;
  for (auto it : l) prod *= (it.second + 1);
  return prod;
}

long long DivisorSum(long long x, const std::vector<long long>& primeList) {
  auto l = PFactor(x, primeList);
  long long prod = 1;
  for (auto it : l)
    prod *= ((powl(it.first, it.second + 1) - 1) / (it.first - 1));
  return prod;
}

long long DivisorSum(std::list<std::pair<long long, long long>>& l){
  long long prod = 1;
  for (auto it : l)
    prod *= ((powl(it.first, it.second + 1) - 1) / (it.first - 1));
  return prod;
}

//**************************
// figurate numbers functions
//**************************
long long GetOctX(long long i) { return ceil(sqrt(float(i) / 3)); }
long long OctSumN(long long i) { return i * (3 * i - 2); }

long long GetHeptX(long long i) { return ceil(sqrt(float(i) * float(2) / 5)); }
long long HeptSumN(long long i) { return (i * (5 * i - 3)) / 2; }

long long GetHexX(long long i) { return ceil(sqrt(float(i) / 2)); }
long long HexSumN(long long i) { return 2 * i * i - i; }

long long GetPentX(long long i) { return ceil(sqrt(float(i) * float(2) / 3)); }
long long PentSumN(long long i) { return (3 * (i * i) - i) / 2; }

long long GetTriX(long long i) { return floor(sqrt(i * 2)); }
long long TriSumN(long long i) { return ((i * (i + 1)) / 2); }

bool IsOct(long long i) {
  long long temp = GetOctX(i);
  return OctSumN(temp) == i;
}
bool IsHept(long long i) {
  long long temp = GetHeptX(i);
  return HeptSumN(temp) == i;
}
bool IsHex(long long i) {
  long long temp = GetHexX(i);
  return HexSumN(temp) == i;
}
bool IsPent(long long i) {
  long long temp = GetPentX(i);
  return PentSumN(temp) == i;
}
bool IsTri(long long i) {
  long long temp = GetTriX(i);
  return TriSumN(temp) == i;
}
bool IsSquare(long long i) {
  long long temp = sqrt(i);
  return (temp * temp) == i;
}

//**************************
// other math functions
//**************************
long long DigitSum(long long x) {
  long long sum = 0;
  while (x) {
    sum += (x % 10);
    x /= 10;
  }
  return sum;
}

//**************************
// non math functions
//**************************
bool IterateBin(bool* myarrbegin, bool* myarrend) {
  bool* i;

  // the only reason for this loop is retaining the final case
  for (i = myarrbegin; i < myarrend && (*i); ++i)
    ;

  if (i == myarrend)
    return false;

  else {
    (*i) = 1;
    for (--i; i >= myarrbegin; --i) (*i) = 0;
  }
  return true;
}

bool IterateStrin(std::string& str) {
  size_t i;

  for (i = 0; i < str.length() && (str[i] == '1'); ++i)
    ;

  if (i == str.length())
    return false;

  else {
    str[i] = '1';
    if (i) {
      for (--i; i >= 1; --i) str[i] = '0';
      str[0] = '0';
    }
  }
  return true;
}

bool IterateArr(long long* myarrbegin, long long* myarrend,
                long long* testarr) {
  long long* i;

  for (i = myarrbegin; i < myarrend && (*i == *(i - myarrbegin + testarr)); ++i)
    ;

  if (i == myarrend)
    return false;

  else {
    ++(*(i - myarrbegin + testarr));
    for (--i; i >= myarrbegin; --i) (*(i - myarrbegin + testarr)) = 0;
  }
  return true;
}

long long MkNum(int start, int end, int* myarr) {
  long long num = 0;
  --start;
  while (++start <= end) {
    num *= 10;
    num += myarr[start];
  }
  return num;
}

int* MkArr(unsigned long long num, int& size) {
  int len = CountDigits(num);
  size = len;
  int* digits = new int[len];

  int i = len;
  while (num) {
    digits[--i] = num % 10;
    num /= 10;
  }
  return digits;
}

unsigned long long MkPalNum(unsigned long long x) {
  unsigned long long num = x;
  while (x) {
    num *= 10;
    num += x % 10;
    x /= 10;
  }
  return num;
}

unsigned long long MkPalNum2(unsigned long long x) {
  unsigned long long num = x;
  x /= 10;
  while (x) {
    num *= 10;
    num += x % 10;
    x /= 10;
  }
  return num;
}

unsigned long long RevNum(unsigned long long x) {
  unsigned long long num = 0;
  while (x) {
    num *= 10;
    num += x % 10;
    x /= 10;
  }
  return num;
}

bool IsPal(unsigned long long x) { return RevNum(x) == x; }

std::vector<long long> SetToVec(std::set<long long>& myset) {
  using namespace std;
  vector<long long> myvec(myset.size());
  copy(myset.begin(), myset.end(), myvec.begin());
  return myvec;
}

std::vector<bool> GetBinaryString(long long x, bool pad, size_t padlen) {
  using namespace std;
  vector<bool> vec, retvec;
  while (x) {
    vec.push_back(x % 2);
    x /= 2;
  }
  if (pad)
    while (vec.size() + retvec.size() < padlen) retvec.push_back(0);
  while (vec.size()) {
    retvec.push_back(vec.back());
    vec.pop_back();
  }
  return retvec;
}

long long FromBinaryString(const std::vector<bool>& binstr) {
  long long retval = 0;

  for (auto it : binstr) {
    retval *= 2;
    retval += it;
  }
  return retval;
}

} // namespace mstdlib
