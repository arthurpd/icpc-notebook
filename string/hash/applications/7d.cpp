// https://codeforces.com/contest/7/problem/D
#include "../hash.cpp"
char tmp[5123456];
int main(void) {
  string s;
  scanf("%s", tmp);
  s = tmp;
  int n = sz(s);
  vector<int> tab(n + 1);
  hash_interval hash(s, 137, 1000000007);
  reverse(s.begin(), s.end());
  hash_interval rev_hash(s, 137, 1000000007);
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    if (hash.get(0, (i - 1) / 2) == rev_hash.get(n - i, n - (i + 2) / 2))
      tab[i] = tab[i / 2] + 1;
    else
      tab[i] = 0;
    ans += tab[i];
  }
  cout << ans << endl;
}
