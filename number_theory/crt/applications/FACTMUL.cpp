// https://www.spoj.com/problems/FACTMUL/
#include "../crt.cpp"
#define MOD1 186583
#define MOD2 587117
#define MOD 109546051211
int main() {
  int n;
  scanf("%d", &n);
  ll fat1 = 1, fat2 = 1;
  ll res1 = 1, res2 = 1;
  for (int i = 2; i <= n; i++) {
    fat1 = (fat1 * i) % MOD1;
    res1 = (res1 * fat1) % MOD1;
    fat2 = (fat2 * i) % MOD2;
    res2 = (res2 * fat2) % MOD2;
  }
  printf("%lld\n", crt(res1, MOD1, res2, MOD2));
}