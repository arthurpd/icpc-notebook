/*
    Problem: D from https://codeforces.com/contest/497
*/
#include "../convex_mikowski_sum.cpp"
typedef long double ld;
typedef point<ld> P;
int main() {
  vector<P> A, B;
  P CA, CB;
  int n, m;
  cin >> CA.x >> CA.y >> n;
  A.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> A[i].x >> A[i].y;
    A[i] = A[i] - CA;
  }
  cin >> CB.x >> CB.y >> m;
  B.resize(m);
  for (int i = 0; i < m; i++) {
    cin >> B[i].x >> B[i].y;
    B[i] = B[i] - CB;
  }
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      vector<P> v1(2), v2(2);
      v1[0] = A[i];
      v1[1] = A[(i + 1) % n];
      v2[0] = B[j] * -1;
      v2[1] = B[(j + 1) % m] * -1;
      vector<P> pl = convex_minkowski_sum(v1, v2);
      bool in = 0, out = 0;
      for (int k = 0; k < sz(pl); k++) {
        P p1 = pl[k], p2 = pl[(k + 1) % sz(pl)];
        if ((CA - CB).dist() >
            segment<ld>(p1, p2).dist(point<ld>(0, 0)) - EPS) {
          in = 1;
        }
        if ((CA - CB).dist() < (pl[k]).dist() + EPS) {
          out = 1;
        }
        if (in && out) {
          cout << "YES" << endl;
          return 0;
        }
      }
    }
  printf("NO\n");
}