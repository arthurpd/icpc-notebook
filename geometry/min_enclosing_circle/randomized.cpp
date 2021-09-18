#include "../2d/2d.cpp"
/*
        Minimum Enclosing Circle:
                Given a list of points, returns a circle of minimum radius
                such that all given points are within the circle.
                Runs in O(n) expected time (in practice 200 ms for 10^5
                points).

        Constraints:
                Non-empty list of points.

        Author: Arthur Pratti Dadalto
*/
#define point point<double>
#define circle circle<double>
circle min_enclosing_circle(vector<point> p) {
  shuffle(p.begin(), p.end(), mt19937(time(0)));
  point o = p[0];
  double r = 0, eps = 1 + 1e-8;
  for (int i = 0; i < sz(p); i++)
    if ((o - p[i]).dist() > r * eps) {
      o = p[i], r = 0;
      for (int j = 0; j < i; j++)
        if ((o - p[j]).dist() > r * eps) {
          o = (p[i] + p[j]) / 2;
          r = (o - p[i]).dist();
          for (int k = 0; k < j; k++)
            if ((o - p[k]).dist() > r * eps) {
              o = circumcircle(p[i], p[j], p[k]).center;
              r = (o - p[i]).dist();
            }
        }
    }
  return {o, r};
}
