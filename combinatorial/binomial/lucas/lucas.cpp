#include "../../../contest/header.hpp"
#include "../../../number_theory/mod_inverse/mod_inverse.cpp"
/*
        [DESCRIPTION]
         Lucas' theorem to calculate C(N, M) % P where N, M be
         non-negative integers and P a prime.

     Write N and M in the base P:
         Np= n_kp^k +...+ n_1p + n_0 and Mp = m_kp^k +...+ m_1p + m_0.
     Then C(N, M) === Prod(C(n_i, m_i)) % P

        [CONSEQUENCE]
         A binomial coefficient C(N, M) is divisible by a prime P iff
         there is an index i where
         Np[i] < Mp[i] which leads to C(Nb[i], Mb[i]) = 0.
         Hence, C(N, M) % P = 0

        [USAGE]
         Pre-compute all factorials (mod P) up to the P prime chosen.
         all the function choseModP.
         You can also pre-compute all factorials' modular inverses to
         boost the performance.

        [COMPLEXITY]
         O(log_p(N) * mod_inverse())
 */
ll chooseModP(ll n, ll m, int p, vector<ll> &fact) {
  ll c = 1;
  while (n || m) {
    ll a = n % p, b = m % p;
    if (a < b) return 0;
    c = c * fact[a] % p * mod_inverse<ll>(fact[b], p) % p *
        mod_inverse<ll>(fact[a - b], p) % p;
    n /= p;
    m /= p;
  }
  return c;
}