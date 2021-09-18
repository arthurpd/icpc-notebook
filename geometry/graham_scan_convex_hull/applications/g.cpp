/*Problem:
 * https://codeforces.com/group/3qadGzUdR4/contest/101706/problem/G*/
/*Group: https://codeforces.com/group/3qadGzUdR4/members*/
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template <typename T>
struct point {
  typedef point<T> P;
  T x, y;
  int label;
  explicit point(T x = 0, T y = 0, int label = -1)
      : x(x), y(y), label(label) {}
  // Double version: bool operator<(P p) const { return  fabs(x - p.x) <
  // EPS ? y < p.y : x < p.x; }
  bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
  // Double version: bool operator==(P p) const { return fabs(x - p.x) <
  // EPS && fabs(y - p.y) < EPS; }
  bool operator==(P p) const {
    return tie(x, y) == tie(p.x, p.y) && label == p.label;
  }
  P operator+(P p) const { return P(x + p.x, y + p.y, label); }
  T dist2() const { return x * x + y * y; }
  P operator-(P p) const { return P(x - p.x, y - p.y, label); }
  T dot(P p) const { return x * p.x + y * p.y; }
  T cross(P p) const { return x * p.y - y * p.x; }
  T cross(P a, P b) const { return (a - *this).cross(b - *this); }
  long double dist() const { return sqrt((long double)dist2()); }
};
template <typename T>
bool cmp(point<T> a, point<T> b) {
  if (a.cross(b) != 0) return a.cross(b) > 0;
  return a.dist2() < b.dist2();
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
template <typename T>
T areaPol2(vector<point<T> > pol) {
  T area = 0;
  for (int i = 0; i < (int)pol.size() - 1; i++)
    area += pol[i].cross(pol[i + 1]);
  area += pol[pol.size() - 1].cross(pol[0]);
  return area;
}
int main() {
  int n;
  scanf("%d", &n);
  vector<point<ll> > p(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld %lld", &p[i].x, &p[i].y);
    p[i].label = i + 1;
  }
  vector<point<ll> > ch = CH(p);
  printf("%d\n", (int)ch.size());
  for (int i = 0; i < (int)ch.size(); i++)
    printf("%d%c", ch[i].label, " \n"[i == ch.size() - 1]);
  long double diam = 0;
  for (int i = 0; i < (int)ch.size() - 1; i++)
    diam += (ch[i] - ch[i + 1]).dist();
  diam += (ch[0] - ch[ch.size() - 1]).dist();
  printf("%.12Lf\n", diam);
  // Importante imprimir assim, double com uma casa da problema (exemplo:
  // pontos (0,0);(1,1);(0,1)
  printf("%lld", areaPol2(ch) / 2);
  if (areaPol2(ch) % 2)
    printf(".5\n");
  else
    printf(".0\n");
}
