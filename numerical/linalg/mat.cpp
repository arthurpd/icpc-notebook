#include "../../contest/header.hpp"
/*
        Vector and matrix operations:
                Details are given in each function.
                vec inherits from vector<T>, so there is a lot you can do
                with it.
                Also, mat inherits from vector<vec<T>>.

        Author: Arthur Pratti Dadalto

        Source: some of it from https://github.com/
                                                        kth-competitive-programming/
                                                    kactl/blob/master/content/numerical/
                                                        MatrixInverse.h
*/
template <class T>
struct vec : vector<T> {
  vec(int n) : vector<T>(n) {}
  // c = a*x + b*y
  static void linear_comb(const vec &a, T x, const vec &b, T y, vec &c) {
    for (int i = 0; i < sz(a); i++) c[i] = a[i] * x + b[i] * y;
  }
  // return a*x + b*y
  static vec linear_comb(vec a, T x, const vec &b, T y) {
    linear_comb(a, x, b, y, a);
    return a;
  }
};
template <class T>
struct mat : vector<vec<T>> {
  // Creates a zero-filled matrix of n rows and m columns.
  mat(int n, int m) : vector<vec<T>>(n, vec<T>(m)) {}
  // c = a * x + b * y
  static void linear_comb(const mat &a, T x, const mat &b, T y, mat &c) {
    for (int i = 0; i < sz(a); i++)
      for (int j = 0; j < sz(a[i]); j++)
        c[i][j] = a[i][j] * x + b[i][j] * y;
  }
  // return a * x + b * y
  static mat linear_comb(mat a, T x, const mat &b, T y) {
    linear_comb(a, x, b, y, a);
    return a;
  }
  mat operator-(const mat &b) const {
    return linear_comb(*this, T(1), b, T(-1));
  }
  mat operator+(const mat &b) const {
    return linear_comb(*this, T(1), b, T(1));
  }
  mat operator*(const T &x) { return linear_comb(*this, x, *this, T(0)); }
  // Absolutely does not work for int.
  mat operator/(const T &x) const {
    return linear_comb(*this, T(1) / x, *this, T(0));
  }
  // Multiplication of NxR matrix and a RxM matrix.
  // TODO test me on non-square.
  mat operator*(mat b) const {
    int n = (*this).size();
    int m = b[0].size();
    int r = (*this)[0].size();
    mat retv(n, m);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        for (int k = 0; k < r; k++)
          retv[i][j] = retv[i][j] + (*this)[i][k] * b[k][j];
    return retv;
  }
  // Returns inverse of matrix (assuming it is square and
  // non-singular).
  // Runs in O(n^3).
  // Absolutely does not work for int.
  mat inverse()  // TODO: test singular.
  {
    int n = sz(*this);
    mat a(n, 2 * n);     // A is Nx2N: X|I.
    vector<int> col(n);  // Will be using column pivoting,
                         // so need to remember original columns.
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) a[i][j] = (*this)[i][j];
      a[i][i + n] = T(1);
      col[i] = i;
    }
    for (int i = 0; i < n; i++) {
      int r = i, c = i;
      for (int j = i; j < n; j++)
        for (int k = i; k < n; k++)
          if (abs(a[j][k]) > abs(a[r][c])) r = j, c = k;
      // assert(abs(a[r][c]) > EPS); Uncomment to check singular
      // matrix
      swap(a[i], a[r]);
      for (int j = 0; j < n; j++)
        swap(a[j][i], a[j][c]), swap(a[j][i + n], a[j][c + n]);
      swap(col[i], col[c]);
      vec<T>::linear_comb(a[i], T(1) / a[i][i], a[i], T(0), a[i]);
      a[i][i] = T(1);
      for (int j = i + 1; j < n; j++)
        vec<T>::linear_comb(a[j], T(1), a[i], -a[j][i], a[j]);
    }
    // Right now A is:
    //
    //	1	*	*
    //	0	1	*
    //	0	0	1
    //
    // Next we remove non-1s from right to left.
    for (int i = n - 1; i > 0; i--)
      for (int j = 0; j < i; j++)
        vec<T>::linear_comb(a[j], T(1), a[i], -a[j][i], a[j]);
    mat retv(n, n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) retv[col[i]][col[j]] = a[i][j + n];
    return retv;
  }
};
