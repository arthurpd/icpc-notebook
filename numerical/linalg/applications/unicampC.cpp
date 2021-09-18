// https://codeforces.com/group/kZPk3ZTzR5/contest/249481
#include "../../../number_theory/mod_inverse/mod_inverse.cpp"
#include "../../bigint/bigint.cpp"
#include "../../frac/frac.cpp"
#include "../../linalg/mat.cpp"
int n, k;
#define frac frac<BigInt>
#define mat mat<frac>
#define vec vec<frac>
bool been[20][20][20];
frac tab[20][20][20];
frac pd(int cur, int nex, int pack) {
  if (pack == 0 || cur == 0) return cur == nex ? frac(1) : frac(0);
  if (been[cur][nex][pack]) return tab[cur][nex][pack];
  been[cur][nex][pack] = true;
  frac p_success(cur, n);
  return tab[cur][nex][pack] =
             p_success * pd(cur - 1, nex, pack - 1) +
             (frac(1) - p_success) * pd(cur, nex, pack - 1);
}
int main() {
  cin >> n >> k;
  mat p(n + 1, n + 1);
  for (int i = 0; i <= n; i++)
    for (int j = i; j >= 0; j--) p[n - i][n - j] = pd(i, j, k);
  mat q(n, n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) q[i][j] = p[i][j];
  mat id(n, n);
  for (int i = 0; i < n; i++) id[i][i] = frac(1);
  debug(p);
  debug(q);
  debug(id - q);
  mat N = (id - q).inverse();
  frac t(0);
  for (int i = 0; i < n; i++) t = t + N[0][i];
  debug(N);
  debug(t);
  BigInt mod(1000000007ll);
  cout << (t.a / t.b) << " " << ((t.a % t.b) * mod_inverse(t.b, mod)) % mod
       << endl;
}
