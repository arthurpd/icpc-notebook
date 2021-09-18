// https://codeforces.com/contest/1251/problem/F
#include "../ntt.cpp"
#define MAXN 312345
vector<ll> pot(vector<ll> b, ll e) {
  vector<ll> ans = {1};
  for (; e; b = conv(b, b), e /= 2)
    if (e & 1) ans = conv(ans, b);
  return ans;
}
int main() {
  int t = 1;
  while (t--) {
    int n, k, a;
    scanf("%d %d", &n, &k);
    vector<int> tab(MAXN, 0);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a);
      tab[a]++;
    }
    vector<ll> ans(4 * MAXN);
    vector<int> b(k);
    for (int i = 0; i < k; i++) scanf("%d", &b[i]);
    sort(b.begin(), b.end());
    int k1 = 0, k2 = 0, j = 0;
    vector<ll> p = {1};
    for (int i = 0; i < k; i++) {
      for (; j < b[i]; j++)
        if (tab[j] >= 2)
          k2++;
        else if (tab[j] == 1)
          k1++;
      p = conv(p, conv(pot({1, 2}, k1), pot({1, 2, 1}, k2)));
      k1 = 0, k2 = 0;
      for (int l = 0; l < sz(p); l++)
        ans[l + b[i] + 1] = (p[l] + ans[l + b[i] + 1]) % mod;
    }
    int q;
    scanf("%d", &q);
    while (q--) {
      scanf("%d", &a);
      printf("%lld\n", ans[a / 2]);
    }
  }
}
