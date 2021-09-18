// https://codeforces.com/contest/1083/problem/E
#include "../line_container.cpp"
struct rect {
  ll x, y, c;
  bool operator<(rect rhs) const { return x < rhs.x; }
};
#define MAXN 1123456
ll tab[MAXN];
rect r[MAXN];
int n;
int main(void) {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%lld %lld %lld", &r[i].x, &r[i].y, &r[i].c);
  sort(r + 1, r + n + 1);
  line_container l;
  l.add(0, 0);
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    // tab[i] = -0x3f3f3f3f3f3f3f3fll;
    // for (int j = 0; j < i; j++)
    // tab[i] = max(tab[i], tab[j] - r[j].x * r[i].y + r[i].x * r[i].y -
    // r[i].c);
    //
    // With convex hull trick:
    // max k * x + m
    // k = - r[j].x
    // m = tab[j]
    tab[i] = l.query(r[i].y) + r[i].x * r[i].y - r[i].c;
    ans = max(ans, tab[i]);
    l.add(-r[i].x, tab[i]);
  }
  printf("%lld\n", ans);
}
