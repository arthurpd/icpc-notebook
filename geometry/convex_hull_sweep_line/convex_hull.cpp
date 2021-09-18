
#include "../../contest/header.hpp"
/*
        Convex hull:
                Computes lower and upper convex hull for a set of points in
                O(n * log n).
                Using lower and upper convex hull you can also check if a
                point belongs
                to the polygon in O(log n) with the point_in_ch function.

        Usage:
                Upper/lower hulls start at lowest x (tie broken by lowest
   y) and end at highest x (tie broken by highest y). Points can be
   collinear, but convex hull will not contain collinear points.

        Author: Arthur Pratti Dadalto
*/
struct point {
  ll x, y;
  explicit point(ll x = 0, ll y = 0) : x(x), y(y) {}
  ll cross(point p1, point p2) {
    return (p1.x - x) * (p2.y - y) - (p2.x - x) * (p1.y - y);
  }
  bool operator<(const point &rhs) const {
    return tie(x, y) < tie(rhs.x, rhs.y);
  }
};
void convex_hull(vector<point> p, vector<point> &upper,
                 vector<point> &lower) {
  sort(p.begin(), p.end());
  auto build = [&p](vector<point> &ch, ll tp) {
    ch.push_back(p[0]), ch.push_back(p[1]);
    for (int i = 2; i < sz(p); i++) {
      while (ch.size() >= 2 &&
             tp * ch[sz(ch) - 2].cross(ch.back(), p[i]) >= 0)
        ch.pop_back();
      ch.push_back(p[i]);
    }
  };
  build(upper, 1);
  build(lower, -1);
}
// Optional.
// Checks if point o is inside the convex hull area in O(log n).
// Also returns true if point is on the convex hull perimeter.
bool point_in_ch(point o, vector<point> &upper, vector<point> &lower) {
  if (o.x < upper[0].x || o.x > upper.back().x) return false;
  auto check = [o](vector<point> &ch, ll tp) {
    int i = lower_bound(ch.begin(), ch.end(), o,
                        [](point a, point b) { return a.x < b.x; }) -
            ch.begin();
    if ((i != 0 && tp * ch[i - 1].cross(ch[i], o) > 0) ||
        (i + 1 < sz(ch) && tp * ch[i].cross(ch[i + 1], o) > 0) ||
        (i + 2 < sz(ch) && tp * ch[i + 1].cross(ch[i + 2], o) > 0))
      return false;
    return true;
  };
  return check(upper, 1) && check(lower, -1);
}
