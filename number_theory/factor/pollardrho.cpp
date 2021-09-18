/*
  Description:
        Pollard-rho randomized factorization algorithm. Returns prime
        factors of a number, in arbitrary order (e.g. 2299 ->
                                                                                                  {11, 19, 11}).

  Time:
        O(n^1/4) gcd calls, less for numbers with small factors.

  Source: https://github.com/kth-competitive-programming/
 */
#include "../../contest/header.hpp"
#include "../primality_test/millerRabin.cpp"
ull pollard(ull n) {
  auto f = [n](ull x) { return (mod_mul(x, x, n) + 1) % n; };
  if (!(n & 1)) return 2;
  for (ull i = 2;; i++) {
    ull x = i, y = f(x), p;
    while ((p = __gcd(n + y - x, n)) == 1) x = f(x), y = f(f(y));
    if (p != n) return p;
  }
}
vector<ull> factorize(ull n) {
  if (n == 1) return {};
  if (isPrime(n)) return {n};
  ull x = pollard(n);
  auto l = factorize(x), r = factorize(n / x);
  l.insert(l.end(), all(r));
  return l;
}
