#include "../../contest/header.hpp"
/*
        Number Theoretic Transform:
                FFT allows multiplication of two polynomials in O(n log n)
                where you need the coeficients modulo some specific prime.

        Usage:
                Can be used for convolutions modulo specific nice primes
                of the form (b * 2^a + 1), where the convolution result
                has size at most $2^a$.
                Inputs must be in [0, mod).

        Source: https://cp-algorithms.com/algebra/fft.html
*/
const ll mod = (119 << 23) + 1, root = 62;  // = 998244353
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
ll modpow(ll b, ll e) {
  ll ans = 1;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) ans = ans * b % mod;
  return ans;
}
typedef vector<ll> vl;
void ntt(vl &a, vl &rt, vl &rev, int n) {
  for (int i = 0; i < n; i++)
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k)
      for (int j = 0; j < k; j++) {
        ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
        a[i + j + k] = (z > ai ? ai - z + mod : ai - z);
        ai += (ai + z >= mod ? z - mod : z);
      }
}
vl conv(const vl &a, const vl &b) {
  if (a.empty() || b.empty()) return {};
  int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
  vl L(a), R(b), out(n), rt(n, 1), rev(n);
  L.resize(n), R.resize(n);
  for (int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << B) / 2;
  ll curL = mod / 2, inv = modpow(n, mod - 2);
  for (int k = 2; k < n; k *= 2) {
    ll z[] = {1, modpow(root, curL /= 2)};
    for (int i = k; i < 2 * k; i++) rt[i] = rt[i / 2] * z[i & 1] % mod;
  }
  ntt(L, rt, rev, n);
  ntt(R, rt, rev, n);
  for (int i = 0; i < n; i++)
    out[-i & (n - 1)] = L[i] * R[i] % mod * inv % mod;
  ntt(out, rt, rev, n);
  return {out.begin(), out.begin() + s};
}
