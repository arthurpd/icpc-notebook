// https://codeforces.com/contest/626/problem/E
#include "../ternary_search_discrete.cpp"
int main() {
  cin.sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a.begin(), a.end());
  vector<ll> pref(n + 1);
  for (int i = 1; i <= n; i++) pref[i] = pref[i - 1] + a[i - 1];
  pii sol = {0, 0};
  double val = -infll;
  for (int i = 0; i < n; i++) {
    auto f = [&a, &i, &n, &pref](int x) {
      return (pref[n] - pref[n - x] + pref[i + 1] - pref[i - x] -
              (2ll * x + 1) * a[i]) /
             (2.0 * x + 1.0);
    };
    int x = ternary_search(f, 0, min(i, n - i - 1));
    if (f(x) > val) {
      val = f(x);
      sol = {i, x};
    }
  }
  cout << (2 * sol.second + 1) << endl;
  for (int i = sol.first; i >= sol.first - sol.second; i--)
    cout << a[i] << " ";
  for (int i = n - 1; i >= n - sol.second; i--) cout << a[i] << " ";
  cout << endl;
}
