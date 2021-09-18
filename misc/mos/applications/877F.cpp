// https://codeforces.com/contest/877/problem/F
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
#define sz(x) x.size()
#define MAXN 112345
struct query {
  int l, r, id;
};
int n, k;
int type[MAXN];
ll prefix[MAXN];
ll target[MAXN];
ll ans[MAXN];
ll wanted[2 * MAXN], available[2 * MAXN];
ll curr;
void add_l(int p) {
  available[prefix[p]]++;
  curr += available[target[p]];
  wanted[target[p]]++;
}
void add_r(int p) {
  available[prefix[p]]++;
  wanted[target[p]]++;
  curr += wanted[prefix[p]];
}
void remove_l(int p) {
  curr -= available[target[p]];
  available[prefix[p]]--;
  wanted[target[p]]--;
}
void remove_r(int p) {
  curr -= wanted[prefix[p]];
  available[prefix[p]]--;
  wanted[target[p]]--;
}
void output(int id) { ans[id] = curr; }
void mos(int n, vector<query> q) {
  int bsize = 1 + n / sqrt(sz(q));
  sort(q.begin(), q.end(), [&](const query &lhs, const query &rhs) {
    if (lhs.l / bsize != rhs.l / bsize) return lhs.l < rhs.l;
    if ((lhs.l / bsize) & 1) return (lhs.r > rhs.r);
    return (lhs.r < rhs.r);
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
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &type[i]);
  }
  int id = 0;
  set<ll> used;
  map<ll, int> compress;
  ll curr = 0;
  for (int i = 1; i <= n; i++) {
    ll v;
    scanf("%lld", &v);
    target[i] = curr + k;
    used.insert(target[i]);
    if (type[i] == 1)
      curr += v;
    else
      curr -= v;
    prefix[i] = curr;
    used.insert(prefix[i]);
  }
  for (ll i : used) compress[i] = id++;
  for (int i = 1; i <= n; i++) {
    prefix[i] = compress[prefix[i]];
    target[i] = compress[target[i]];
  }
  int q;
  scanf("%d", &q);
  vector<query> vet_q;
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