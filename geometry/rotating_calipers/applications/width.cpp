// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3552
// IMPORTANT: need to change convex hull code to pass (no collinear
// points).
#include "../convex_polygon_width.cpp"
int main(void) {
  int n, t = 1;
  while (cin >> n && n) {
    vector<point<ll>> p(n);
    for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;
    auto ch = CH(p);
    double ans = convex_polygon_width(ch);
    printf("Case %d: %.2lf\n", t++, ans);
  }
}
