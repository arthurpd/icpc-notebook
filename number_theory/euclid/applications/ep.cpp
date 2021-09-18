// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1045
#include "../euclid.cpp"
int main(void) {
  int a, b, x, y;
  while (scanf("%d %d", &a, &b) != EOF) {
    int d = gcd(a, b, x, y);
    printf("%d %d %d\n", x, y, d);
  }
}
