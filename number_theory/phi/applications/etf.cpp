// https://www.spoj.com/problems/ETF/
#include "../phi.cpp"
int main(void) {
  int T, n;
  scanf("%d", &T);
  totient::init();
  while (T--) {
    scanf("%d", &n);
    // printf("%d\n", totient::phi[n]);
    printf("%d\n", phi(n));
  }
}
