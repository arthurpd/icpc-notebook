/*Problem:
 * https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2559*/
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template <typename T>
struct point {
  typedef point<T> P;
  T x, y;
  explicit point(T x = 0, T y = 0) : x(x), y(y) {}
  // Double version: bool operator<(P p) const { return  fabs(x - p.x) <
  // EPS ? y < p.y : x < p.x; }
  bool operator<(P p) const { /*return tie(x, y) < tie(p.x, p.y);*/
    return y != p.y ? y > p.y : x < p.x;
  }
  // Double version: bool operator==(P p) const { return fabs(x - p.x) <
  // EPS && fabs(y - p.y) < EPS; }
  bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
  P operator+(P p) const { return P(x + p.x, y + p.y); }
  P operator-(P p) const { return P(x - p.x, y - p.y); }
  T dot(P p) const { return x * p.x + y * p.y; }
  T cross(P p) const { return x * p.y - y * p.x; }
  T cross(P a, P b) const { return (a - *this).cross(b - *this); }
};
template <typename T>
bool cmp(point<T> a, point<T> b) {
  if (a.cross(b) != 0) return a.cross(b) > 0;
  return a.x * a.x + a.y * a.y < b.x * b.x + b.y * b.y;
}
template <typename T>
vector<point<T> > CH(vector<point<T> > points) {
  point<T> pivot = points[0];
  for (auto p : points) pivot = min(pivot, p);
  for (int i = 0; i < (int)points.size(); i++)
    points[i] = points[i] - pivot;
  sort(points.begin(), points.end(), cmp<ll>);
  for (int i = 0; i < (int)points.size(); i++)
    points[i] = points[i] + pivot;
  points.push_back(points[0]);
  vector<point<T> > ch;
  for (auto p : points) {
    // Trocar segunda comparacao pra <= para discartar pontos do meio de
    // arestas no ch Double: trocar segunda comparação por < EPS (descarta
    // pontos em arestas)
    while (ch.size() > 1 && !(p == ch[ch.size() - 2]) &&
           ch[ch.size() - 2].cross(ch[ch.size() - 1], p) <= 0)
      ch.pop_back();
    ch.push_back(p);
  }
  ch.pop_back();
  return ch;
}
int main() {
  int t;
  scanf("%d", &t);
  for (int cse = 1; cse <= t; cse++) {
    int x, n;
    scanf("%d %d", &x, &n);
    vector<point<ll> > p(n);
    for (int i = 0; i < n; i++) {
      scanf("%lld %lld", &p[i].x, &p[i].y);
    }
    vector<point<ll> > ch = CH(p);
    printf("%d %d\n", x, (int)ch.size());
    vector<point<ll> > res;
    res.push_back(ch[0]);
    for (int i = ch.size() - 1; i > 0; i--) res.push_back(ch[i]);
    for (int i = 0; i < (int)ch.size(); i++)
      printf("%lld %lld\n", res[i].x, res[i].y);
  }
}
