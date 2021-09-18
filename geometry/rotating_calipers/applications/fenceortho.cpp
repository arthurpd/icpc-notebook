// https://open.kattis.com/problems/fenceortho
// IMPORTANT: need to change convex hull code to pass (no collinear
// points).
#include "../convex_polygon_bounding_box.cpp"
int main(void) {
  int n;
  while (cin >> n && n) {
    vector<point<ll>> p(n);
    for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;
    auto ch = CH(p);
    double ans = min_bounding_box_perimeter(ch);
    printf("%.20lf\n", ans);
  }
}
