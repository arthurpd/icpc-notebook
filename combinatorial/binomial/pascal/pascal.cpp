
#include "../../../contest/header.hpp"
/*
        [DESCRIPTION]
         Pre-computing all binomial coefficient (% MOD) up to
     C(MAXN, MAXN) into a matrix using pascal's triangle.

        [COMPLEXITY]
         O(n^2) to Pre-computing
     O(1) to lookup
 */
#define MAXN 3123
#define MOD 1000000007
long long C[MAXN][MAXN];
void init_ncr() {
  C[0][0] = 1;
  for (int n = 1; n < MAXN; ++n) {
    C[n][0] = C[n][n] = 1;
    for (int k = 1; k < n; ++k)
      C[n][k] = (C[n - 1][k - 1] + C[n - 1][k]) % MOD;
  }
}
