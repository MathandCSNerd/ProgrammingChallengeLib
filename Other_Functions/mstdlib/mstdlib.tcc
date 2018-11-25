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

#ifdef MATTSTDLIB_MSTDLIB_H

namespace mstdlib {

//**************************
// simple math functions
//**************************
template <class numType>
numType gcd(numType a, numType b) {
  if (!b)
    return a;
  else
    return gcd(b, a % b);
}

template <class numType>
numType lcm(numType a, numType b) {
  if (a || b) {
    numType tmp = a * b;
    if (tmp < 0) tmp *= -1;
    return tmp / gcd(a, b);
  } else {
    return 0;
  }
}

template <class numType>
numType log(numType base, numType num) {
  return log10l(num) / log10l(base);
}

template <class numType>
void PAssign(numType& var1, numType& var2, numType val1, numType val2) {
  var1 = val1;
  var2 = val2;
}

template <class numType>
std::vector<numType> xgcd(numType a, numType b) {
  using namespace std;
  vector<numType> vec;
  numType s = 0, old_s = 1;
  numType t = 1, old_t = 0;
  numType r = b, old_r = a;
  numType q;
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

template <class numType>
numType InverseMod(numType a, numType b) {
  auto l = xgcd(a, b);
  if (l[1] < 0) l[1] += b;
  return l[1];
}

template <class numType>
numType IntPow(numType base, numType exp) {
  // return (numType)(floorl(powl(base, exp) + 0.5));
  return pow(base, exp, ULLONG_MAX);
}

template <class numType>
numType pow(numType base, numType exp, numType mod) {
  if (base < 1) return 0;
  if (!exp) return 1;
  numType curr = base, result = 1;

  while (exp) {
    if (exp % 2) result = (result * curr) % mod;
    exp /= 2;
    curr = (curr * curr) % mod;
  }
  return result;
}

//**************************
// simple common functions
//**************************
template <class numType>
void swap(numType& a, numType& b) {
  numType tmp(a);
  a = b;
  b = tmp;
}

template <class numType>
void Simplify(numType& a, numType& b) {
  numType tmp = gcd(a, b);
  a /= tmp;
  b /= tmp;
}

template <class numType>
numType CountDigits(numType i) {
  numType ret = (ceil(log10l(i)));
  if (ret == (log10l(i))) ++ret;
  return ret;
}

//**************************
// counting functions
//**************************
template <class numType>
numType Factorial(numType x) {
  numType sum = 1;
  for (numType i = x; i > 1; --i) sum *= i;
  return sum;
}

template <class numType>
numType NChoosek(numType n, numType k) {
  if (n < k) swap(n, k);
  return Factorial(n) / (Factorial(n - k) * Factorial(k));
}

template <class numType>
numType NPermk(numType n, numType k) {
  return Factorial(n) / (Factorial(n - k));
}

template <class numType>
numType PrecisenChoosek(numType n, numType k) {
  if (n < k) swap(n, k);

  numType m;
  if (k < n - k)
    m = (n - k);
  else
    m = k;

  k = n - m;
  numType sumn = 1;
  numType sumd = 1;

  numType i = m + 1, i2 = 1;
  while (i <= n && i2 <= k) {
    sumn *= i++;
    sumd *= i2++;
    Simplify(sumn, sumd);
  }
  return sumn / sumd;
}

template <class numType>
numType PrecisenPermk(numType n, numType k) {
  numType sum = 1;
  for (numType i = n; i > (n - k); --i) sum *= i;
  return sum;
}

template <class numType>
numType Binomial(numType k, numType n, numType p) {
  return powl(p, k) * powl(1 - p, n - k) * PrecisenChoosek(n, k);
}

//**************************
// summing functions
//**************************
template <class numType>
numType Sum(numType n) {
  return (n * (n + 1)) / 2;
}

template <class numType>
numType SquareSum(numType n) {
  return (n * (n + 1) * (2 * n + 1)) / 6;
}

template <class numType>
numType CubeSum(numType n) {
  return (n * n * (n + 1) * (n + 1)) / 4;
}

template <class numType>
numType SumBy(numType n, numType m) {
  return m * Sum(n / m);
}

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

//**************************
// figurate numbers functions
//**************************
template <class numType>
numType GetOctX(numType i) {
  return ceil(sqrt(float(i) / 3));
}
template <class numType>
numType OctSumN(numType i) {
  return i * (3 * i - 2);
}

template <class numType>
numType GetHeptX(numType i) {
  return ceil(sqrt(float(i) * float(2) / 5));
}
template <class numType>
numType HeptSumN(numType i) {
  return (i * (5 * i - 3)) / 2;
}

template <class numType>
numType GetHexX(numType i) {
  return ceil(sqrt(float(i) / 2));
}
template <class numType>
numType HexSumN(numType i) {
  return 2 * i * i - i;
}

template <class numType>
numType GetPentX(numType i) {
  return ceil(sqrt(float(i) * float(2) / 3));
}
template <class numType>
numType PentSumN(numType i) {
  return (3 * (i * i) - i) / 2;
}

template <class numType>
numType GetTriX(numType i) {
  return floor(sqrt(i * 2));
}
template <class numType>
numType TriSumN(numType i) {
  return ((i * (i + 1)) / 2);
}

template <class numType>
bool IsOct(numType i) {
  numType temp = GetOctX(i);
  return OctSumN(temp) == i;
}
template <class numType>
bool IsHept(numType i) {
  numType temp = GetHeptX(i);
  return HeptSumN(temp) == i;
}
template <class numType>
bool IsHex(numType i) {
  numType temp = GetHexX(i);
  return HexSumN(temp) == i;
}
template <class numType>
bool IsPent(numType i) {
  numType temp = GetPentX(i);
  return PentSumN(temp) == i;
}
template <class numType>
bool IsTri(numType i) {
  numType temp = GetTriX(i);
  return TriSumN(temp) == i;
}
template <class numType>
bool IsSquare(numType i) {
  numType temp = sqrt(i);
  return (temp * temp) == i;
}

//**************************
// other math functions
//**************************
template <class numType>
numType DigitSum(numType x) {
  numType sum = 0;
  while (x) {
    sum += (x % 10);
    x /= 10;
  }
  return sum;
}

template <class numType>
numType SquareDigitSum(numType x) {
  numType sum = 0;
  while (x) {
    sum += (x % 10) * (x % 10);
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

template <class numType>
bool IterateArr(numType* myarrbegin, numType* myarrend, numType* testarr) {
  numType* i;

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

template <class numType>
bool ChooseNFromK(std::vector<numType>& arr, numType maxNum) {
  size_t i;

  for (i = 0; i < arr.size() && (arr[i] >= (maxNum - i - 1)); ++i)
    ;

  if (i == arr.size())
    return false;

  else {
    ++arr[i];
    if (i) {
      for (--i; i >= 1; --i) arr[i] = arr[i + 1] + 1;
      if (arr.size() > 1) arr[0] = arr[1] + 1;
    }
  }
  return true;
}

template <class numType>
numType MkNum(numType start, numType end, numType* myarr) {
  numType num = 0;
  --start;
  while (++start <= end) {
    num *= 10;
    num += myarr[start];
  }
  return num;
}

template <class numType>
numType* MkArr(numType num, numType& size) {
  numType len = CountDigits(num);
  size = len;
  numType* digits = new numType[len];

  numType i = len;
  while (num) {
    digits[--i] = num % 10;
    num /= 10;
  }
  return digits;
}

template <class numType>
numType MkPalNum(numType x) {
  numType num = x;
  while (x) {
    num *= 10;
    num += x % 10;
    x /= 10;
  }
  return num;
}

template <class numType>
numType MkPalNum2(numType x) {
  numType num = x;
  x /= 10;
  while (x) {
    num *= 10;
    num += x % 10;
    x /= 10;
  }
  return num;
}

template <class numType>
numType RevNum(numType x) {
  numType num = 0;
  while (x) {
    num *= 10;
    num += x % 10;
    x /= 10;
  }
  return num;
}

template <class numType>
bool IsPal(numType x) {
  return RevNum(x) == x;
}

template <class numType>
std::vector<numType> SetToVec(std::set<numType>& myset) {
  using namespace std;
  vector<numType> myvec(myset.size());
  copy(myset.begin(), myset.end(), myvec.begin());
  return myvec;
}

template <class numType>
std::vector<bool> GetBinaryString(numType x, bool pad, size_t padlen) {
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

template <class numType>
numType FromBinaryString(const std::vector<bool>& binstr) {
  numType retval = 0;

  for (auto it : binstr) {
    retval *= 2;
    retval += it;
  }
  return retval;
}

template <class numType>
bool IsInSet(numType x, std::set<numType>& mySet) {
  return mySet.find(x) != mySet.end();
}

}  // namespace mstdlib

#endif
