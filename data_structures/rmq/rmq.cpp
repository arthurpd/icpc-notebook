#include "../../contest/header.hpp"
/*
        Range Min(Max) Query
                Maximum of range in vector with O(n log n) preprocessing
                and O(1) query.

        Usage:
                Create passing vector.
                Call query with 0 <= a <= b <= n-1.

        Author: Arthur Pratti Dadalto
*/
template <class T>
struct rmq {
  vector<vector<T>> jmp;
  rmq(const vector<T> &v) {
    int n = sz(v);
    int lgn = 31 - __builtin_clz(n + 1);
    jmp.assign(lgn + 1, vector<int>(n, 0));
    jmp[0] = v;
    for (int i = 1; i <= lgn; i++)
      for (int j = 0; j < n; j++)
        jmp[i][j] =
            max(jmp[i - 1][j], jmp[i - 1][min(n - 1, j + (1 << (i - 1)))]);
  }
  T query(int a, int b) {
    int k = 31 - __builtin_clz(b - a + 1);
    return max(jmp[k][a], jmp[k][b - (1 << k) + 1]);
  }
};
