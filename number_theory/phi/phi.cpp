#include "../../contest/header.hpp"
/*
        Euler's totient function (PHI):
                Euler's totient function, also known as phi-function
   PHI(n), counts the number of integers between 1 and n inclusive, which
                are coprime to n. Two numbers are coprime if their greatest
                common divisor equals 1 (1 is considered to be coprime to
   any number).


        Source: modified from https://cp-algorithms.com/algebra/
                                                        phi-function.html
                and
   https://github.com/kth-competitive-programming/kactl/blob/
                master/content/number-theory/phiFunction.h

        Usage:
                Some useful properties:
                - If p is a prime number, PHI(p)=p-1.
                - If a and b are relatively prime, PHI(ab)=PHI(a)*PHI(b).
                - In general, for not coprime a and b,
                        PHI(ab)=PHI(a)*PHI(b)*d/PHI(d), with d=gcd(a,b)
   holds.
                - PHI(PHI(m)) <= m / 2
                - Euler's theorem: a^PHI(m) === 1 (mod m), for a and m
   coprime
                - For a and m coprime: a^n === a^(n % PHI(m)) (mod m)
                - For arbitrary x,m and n >= log_2(m):
                        x^n === x^(PHI(m)+[n % PHI(m)]) (mod m)
                The one above allows computing modular exponentiation for
                really large exponents.
                - If d is a divisor of n, then there are phi(n/d) numbers
                  i <= n for which gcd(i,n)=d
                - sum_{d|n} phi(d) = n
                - sum_{1 <= k <= n, gcd(k,n)=1} k = n * phi(n) / 2, for n >
   1
*/
// Use this one for few values of phi.
int phi(int n) {
  int result = n;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      while (n % i == 0) n /= i;
      result -= result / i;
    }
  }
  if (n > 1) result -= result / n;
  return result;
}
namespace totient {
const int MAXV = 1000001;  // Takes ~0.03 s for 10^6.
int phi[MAXV];
void init() {
  for (int i = 0; i < MAXV; i++) phi[i] = i & 1 ? i : i / 2;
  for (int i = 3; i < MAXV; i += 2)
    if (phi[i] == i)
      for (int j = i; j < MAXV; j += i) phi[j] -= phi[j] / i;
}
}  // namespace totient
