// https://codeforces.com/contest/438/problem/C
#include "../2d.cpp"
#define point point<ll>
#define segment segment<ll>
#define MAXN 212
const ll mod = 1e9 + 7;
point p[MAXN];
int n;
bool been[MAXN][MAXN];
ll tab[MAXN][MAXN];
ll polyside = 0;
ll pd(int l, int r) {
  if (been[l][r]) return tab[l][r];
  been[l][r] = true;
  bool ok = true;
  for (int k = 0; k < n; k++) {
    if (l != k && l != (k + 1) % n && r != k && r != (k + 1) % n) {
      segment s1 = segment(p[l], p[r]);
      segment s2 = segment(p[k], p[(k + 1) % n]);
      if (s2.intersect(s1).size()) {
        ok = false;
      }
    }
    if (l != k && r != k) {
      segment s1 = segment(p[l], p[r]);
      segment s2 = segment(p[k], p[k]);
      if (s2.intersect(s1).size()) {
        ok = false;
      }
    }
  }
  if (!ok) {
    return tab[l][r] = 0;
  }
  if (r - l <= 1) return tab[l][r] = 1;
  ll retv = 0;
  for (int i = l + 1; i < r; i++)
    if ((polyside * p[r].cross(p[l], p[(l + 1) % n]) <= 0 ||
         polyside * p[l].cross(p[(l + 1) % n], p[i]) >= 0) &&
        (polyside * p[(r - 1 + n) % n].cross(p[r], p[l]) <= 0 ||
         polyside * p[(r - 1 + n) % n].cross(p[r], p[i]) >= 0)) {
      if (polyside * p[r].cross(p[l], p[i]) >= 0)
        retv = (retv + pd(l, i) * pd(i, r)) % mod;
    }
  return tab[l][r] = retv;
}
int main(void) {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;
  point p0(0, 0);
  ll sum = 0;
  for (int i = 0; i < n; i++) sum += p0.cross(p[i], p[(i + 1) % n]);
  polyside = (sum > 0) ? 1 : -1;
  cout << pd(0, n - 1) << endl;
}
