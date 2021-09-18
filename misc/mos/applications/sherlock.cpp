// https://www.hackerearth.com/pt-br/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/practice-problems/algorithm/sherlock-and-inversions/
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define db(x)  // cerr << #x << " = " << x << endl;
#define INF 0x3f3f3f3f3f3f3f3f
#define fi first
#define se second
#define vi vector<int>
#define vll vector<ll>
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vii vector<pii>
#define ll long long
#define ull unsigned long long
typedef long double ld;
#define MAXN 112345
#define sz(x) x.size()
constexpr int logn = 20;
constexpr int maxn = 1 << logn;
ll hilbertorder(int x, int y) {
  ll d = 0;
  for (int s = 1 << (logn - 1); s; s >>= 1) {
    bool rx = x & s, ry = y & s;
    d = d << 2 | rx * 3 ^ static_cast<int>(ry);
    if (!ry) {
      if (rx) {
        x = maxn - x;
        y = maxn - y;
      }
      swap(x, y);
    }
  }
  return d;
}
struct query {
  int l, r, id;
  ll ord() const { return hilbertorder(l, r); }
};
int n, q;
int vals[MAXN];
ll ans[MAXN];
ll curr;
ll BIT[MAXN];
vector<query> vet_q;
void update(int p, int delta) {
  while (p <= MAXN) {
    BIT[p] += delta;
    p += p & -p;
  }
}
ll pref(int p) {
  ll res = 0;
  while (p > 0) {
    res += BIT[p];
    p -= p & -p;
  }
  return res;
}
ll less_than(int v) { return pref(v - 1); }
ll greater_than(int v) { return pref(n) - pref(v); }
void add_l(int p) {
  int v = vals[p];
  update(v, 1);
  curr += less_than(v);
}
void add_r(int p) {
  int v = vals[p];
  update(v, 1);
  curr += greater_than(v);
}
void remove_l(int p) {
  int v = vals[p];
  update(v, -1);
  curr -= less_than(v);
}
void remove_r(int p) {
  int v = vals[p];
  update(v, -1);
  curr -= greater_than(v);
}
void output(int id) { ans[id] = curr; }
void mos(int n, vector<query> q) {
  int bsize = 1 + n / sqrt(sz(q));
  sort(q.begin(), q.end(), [&](const query &lhs, const query &rhs) {
    return lhs.ord() < rhs.ord();
  });
  int l = 1, r = 0;  // int l = 0, r = -1; (if indices starts at 0)
  for (int i = 0; i < sz(q); i++) {
    while (l > q[i].l) add_l(--l);
    while (r < q[i].r) add_r(++r);
    while (l < q[i].l) remove_l(l++);
    while (r > q[i].r) remove_r(r--);
    output(q[i].id);
  }
}
int main() {
  scanf("%d%d", &n, &q);
  vi input(n + 1);
  set<int> s;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &input[i]);
    s.insert(input[i]);
  }
  int id = 1;
  map<int, int> compress;
  for (int v : s) {
    compress[v] = id;
    ++id;
  }
  for (int i = 1; i <= n; i++) {
    vals[i] = compress[input[i]];
  }
  for (int i = 0; i < q; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    vet_q.pb({l, r, i});
  }
  mos(n, vet_q);
  for (int i = 0; i < q; i++) {
    printf("%lld\n", ans[i]);
  }
}