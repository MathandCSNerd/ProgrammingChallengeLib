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

#ifdef MATTSTDLIB_PRIMES_AND_FACTORS_H

namespace mstdlib {

//**************************
// primes and factoring
//**************************
template <class numType>
bool FermatPrimalityTest(numType x) {
  return (pow(2, x - 1, x) != 1);
}

template <class numType>
bool IsObviousNonPrime(numType x) {
  return (!(x % 2) || x < 2) || FermatPrimalityTest(x);
}

template <class numType>
bool IsPrime(numType x) {
  if (x == 2)
    return true;
  else if (IsObviousNonPrime(x))
    return false;

  for (numType i = 3; i <= ceil(sqrt(x)) + 1 && i < x; i += 2)
    if (!(x % i)) return false;

  return true;
}

template <class numType>
bool IsPrime(numType x, const std::vector<numType>& primeSet) {
  if (!(x % 2)) return false;

  auto it = primeSet.end();
  --it;
  if (*(it) >= x)
    return binary_search(primeSet.begin(), primeSet.end(), x);
  else {
    if (IsObviousNonPrime(x)) return false;
    auto l = std::move(PFactor(x, primeSet));
    return l.size() == 1 and l.begin()->second == 1;
  }
}

template <class numType>
bool IsCachePrime(numType x) {
  const static numType MAXPSIZE = 100000;
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
      isPrime[x] = IsPrime(x);
      cPrime[x] = true;
    }
    return isPrime[x];
  }
  return IsPrime(x);
}

template <class numType>
std::vector<numType> ListPrimeSieve(numType MAX_NUM) {
  std::vector<numType> primeList;
  // 1.15 is due to the maximum error in the approximate prime counting function
  primeList.reserve(1.15 * ((numType)MAX_NUM / logl(MAX_NUM)));
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

template <class numType>
bool* ArrPrimeSieve(numType MAX_NUM) {
  bool* arr = new bool[MAX_NUM];
  memset(arr, true, MAX_NUM * sizeof(bool));

  for (numType i = 4; i < MAX_NUM; i += 2) arr[i] = false;
  for (numType i = 3; i <= sqrt(MAX_NUM); i += 2) {
    if (arr[i])
      for (numType i2 = i * 2; i2 < MAX_NUM; i2 += i) arr[i2] = false;
  }
  return arr;
}

template <class numType>
std::vector<numType> PrimeArrToVec(bool* parr, numType MAX_NUM) {
  using namespace std;
  vector<numType> pset;
  if (MAX_NUM >= 2) pset.push_back(2);
  for (numType i = 3; i < MAX_NUM; i += 2)
    if (parr[i]) pset.push_back(i);
  return pset;
}

template <class numType>
std::vector<numType> NormalPrimeSieve(numType MAX_NUM) {
  bool* arr = ArrPrimeSieve(MAX_NUM);
  return std::move(PrimeArrToVec(arr, MAX_NUM));
}

template <class numType>
std::pair<numType, numType> DoFactDiv(numType& x, const numType i) {
  using namespace std;
  pair<numType, numType> tmp;
  numType count = 0;
  while (x % i == 0) {
    ++count;
    x /= i;
  }
  tmp.first = i;
  tmp.second = count;
  return tmp;
}

template <class numType>
std::list<std::pair<numType, numType>> Factor(numType x) {
  using namespace std;
  list<pair<numType, numType>> factors;
  if (x && !(x % 2)) factors.push_back(DoFactDiv(x, 2));
  for (numType i = 3; i < (numType)(sqrt(x) + 1); i += 2) {
    if (!(x % i)) factors.push_back(DoFactDiv(x, i));
  }
  if (x && x != 1) factors.push_back(DoFactDiv(x, x));
  return factors;
}

template <class numType>
std::list<std::pair<numType, numType>> PFactor(
    numType x, const std::vector<numType>& primeList) {
  using namespace std;
  list<pair<numType, numType>> factors;
  numType sq = sqrtl(x) + 0.5;
  for (auto it = primeList.begin(); it != primeList.end() && (*it <= (sq));
       ++it) {
    if (!(x % (*it))) factors.push_back(DoFactDiv(x, *it));
  }
  if (x && x != 1) factors.push_back(DoFactDiv(x, x));
  return factors;
}

template <class numType>
numType EulerPhi(std::list<std::pair<numType, numType>>& l) {
  numType prod = 1;
  numType a, p;
  for (auto it = l.begin(); it != l.end(); ++it) {
    a = it->first;
    p = it->second;
    prod *= (std::pow(a, p) - std::pow(a, p - 1));
  }
  return prod;
}

template <class numType>
numType EulerPhi(numType x) {
  if (x < 1) return 0;

  auto l = std::move(Factor(x));

  return EulerPhi(l);
}

template <class numType>
std::list<numType> FactorsToDivisors(
    std::list<std::pair<numType, numType>>& l) {
  using namespace std;
  numType* exps = new numType[l.size()];
  numType* tmps = new numType[l.size()];
  numType i;
  numType prod;
  list<numType> newl;

  for (i = 0; i < l.size(); ++i) tmps[i] = 0;

  i = -1;
  for (auto it : l) exps[++i] = it.second;

  do {
    i = -1;
    prod = 1;
    for (auto it : l) prod *= numTypePow(it.first, tmps[++i]);
    newl.push_back(prod);
  } while (IterateArr(exps, exps + l.size(), tmps));

  delete[] exps;
  delete[] tmps;

  return newl;
}

template <class numType>
numType DivisorCount(numType x, const std::vector<numType>& primeList) {
  auto l = PFactor(x, primeList);
  numType prod = 1;
  for (auto it : l) prod *= (it.second + 1);
  return prod;
}

template <class numType>
numType DivisorCount(numType x) {
  auto l = Factor(x);
  numType prod = 1;
  for (auto it : l) prod *= (it.second + 1);
  return prod;
}

template <class numType>
numType DivisorSum(numType x, const std::vector<numType>& primeList) {
  auto l = PFactor(x, primeList);
  numType prod = 1;
  for (auto it : l)
    prod *= ((powl(it.first, it.second + 1) - 1) / (it.first - 1));
  return prod;
}

template <class numType>
numType DivisorSum(std::list<std::pair<numType, numType>>& l) {
  numType prod = 1;
  for (auto it : l)
    prod *= ((powl(it.first, it.second + 1) - 1) / (it.first - 1));
  return prod;
}

}  // namespace mstdlib

#endif
