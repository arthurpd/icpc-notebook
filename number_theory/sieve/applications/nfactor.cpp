// https://www.spoj.com/problems/NFACTOR/
#include "../sieve.cpp"
const int MAXN = sieve::MAXP;
int nfactor[MAXN + 1];
int main(void) {
  int T, a, b, n;
  scanf("%d", &T);
  sieve::init();
  for (int i = 2; i <= MAXN; i++) {
    int x = i;
    while (sieve::lp[x] == sieve::lp[i]) x /= sieve::lp[x];
    nfactor[i] = 1 + nfactor[x];
  }
  for (int i = 0; i < sieve::p.size(); i++)
    assert(nfactor[sieve::p[i]] == 1);
  vector<int> tab[11];
  for (int i = 1; i <= MAXN; i++)
    if (nfactor[i] <= 10) tab[nfactor[i]].push_back(i);
  while (T--) {
    scanf("%d %d %d", &a, &b, &n);
    printf("%d\n", (int)(upper_bound(tab[n].begin(), tab[n].end(), b) -
                         lower_bound(tab[n].begin(), tab[n].end(), a)));
  }
}
