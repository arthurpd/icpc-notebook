// https://www.spoj.com/problems/HLP_RAMS/
#include "../../../../contest/header.hpp"
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    // Lucas consequence: C(M,N)%2 is even when exits an indice i where
    // Mb[i] < Nb[i]
    ll n;
    scanf("%lld", &n);
    ll cnt_1 = __builtin_popcountll(n);
    ll odd = (1 << cnt_1);
    ll even = n + 1 - odd;
    printf("%lld %lld\n", even, odd);
  }
}