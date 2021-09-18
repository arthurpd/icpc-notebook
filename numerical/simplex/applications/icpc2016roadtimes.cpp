// https://icpc.kattis.com/problems/roadtimes
#include "../simplex.cpp"
int edge_num[51][51];
int d[51][51];
int prox[51][51];
int main(void) {
  int n;
  cin >> n;
  int m = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      cin >> d[i][j];
      if (d[i][j] == -1)
        d[i][j] = 0x3f3f3f3f;
      else {
        if (d[i][j] > 0) edge_num[i][j] = m++;
        prox[i][j] = j;
      }
    }
  int r, u, v, t;
  cin >> r;
  int num_constraints = 2 * m + r, num_vars = m;
  // maximize c*x, s.t. a*x <= b.
  mat<double> a(num_constraints, num_vars);
  vec<double> b(num_constraints);
  vec<simplex::op> ops(num_constraints);
  vec<double> c(num_vars);
  vec<double> res(num_vars);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      if (d[i][j] > 0 && d[i][j] < 0x3f3f3f3f) {
        // d[i][j] <= x[edge_num[i][j]] <= 2 * d[i][j]
        a[2 * edge_num[i][j]][edge_num[i][j]] = 1;
        b[2 * edge_num[i][j]] = 2 * d[i][j];
        ops[2 * edge_num[i][j]] = simplex::op::le;
        a[2 * edge_num[i][j] + 1][edge_num[i][j]] = 1;
        b[2 * edge_num[i][j] + 1] = d[i][j];
        ops[2 * edge_num[i][j] + 1] = simplex::op::ge;
      }
    }
  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (d[i][k] + d[k][j] < d[i][j]) {
          d[i][j] = d[i][k] + d[k][j];
          prox[i][j] = prox[i][k];
        }
  for (int i = 0; i < r; i++) {
    cin >> u >> v >> t;
    while (u != v) {
      int w = prox[u][v];
      a[2 * m + i][edge_num[u][w]] = 1;
      u = w;
    }
    ops[2 * m + i] = simplex::op::eq;
    b[2 * m + i] = t;
  }
  cout << fixed << setprecision(12);
  int q;
  cin >> q;
  while (q--) {
    cin >> u >> v;
    cout << u << " " << v;
    c = vec<double>(num_vars);
    while (u != v) {
      int w = prox[u][v];
      c[edge_num[u][w]] = 1;
      u = w;
    }
    double ans = 0;
    vec<double>::linear_comb(c, -1, c, 0, c);
    simplex::run_simplex(num_constraints, num_vars, a, ops, b, c, res,
                         ans);
    vec<double>::linear_comb(c, -1, c, 0, c);
    cout << " " << -ans;
    simplex::run_simplex(num_constraints, num_vars, a, ops, b, c, res,
                         ans);
    cout << " " << ans << endl;
  }
}
