// https://codeforces.com/contest/1257/problem/D
#include "../rmq.cpp"
int main() {
  cin.sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> m;
    vector<pii> h(m);
    for (int i = 0; i < m; i++) cin >> h[i].first >> h[i].second;
    sort(h.begin(), h.end());
    vector<pii> heros;
    for (int i = 0; i < m; i++) {
      while (heros.size() > 0 && h[i].second >= heros.back().second)
        heros.pop_back();
      heros.push_back(h[i]);
    }
    rmq<int> rm(a);
    int ans = 0;
    int cur = 0;
    while (cur != n) {
      int bot = 0, top = sz(heros) - 1;
      while (bot < top) {
        int mid = (bot + top + 1) / 2;
        if (rm.query(cur, min(n - 1, cur + heros[mid].second - 1)) >
            heros[mid].first)
          bot = mid;
        else
          top = mid - 1;
      }
      set<int> candidates = {bot, min(bot + 1, sz(heros) - 1)};
      int mx = 0;
      for (int cand : candidates) {
        int i;
        for (i = 0; cur + i < n && i < heros[cand].second &&
                    heros[cand].first >= a[cur + i];
             i++)
          ;
        mx = max(mx, i);
      }
      // debug(candidates);
      // debug(mx);
      if (mx == 0) {
        ans = -1;
        break;
      } else {
        ans++;
        cur += mx;
      }
    }
    cout << ans << endl;
  }
}
