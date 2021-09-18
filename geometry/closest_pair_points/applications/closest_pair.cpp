// https://www.spoj.com/problems/CLOPPAIR/
#include "../closest_pair.cpp"
point p[MAXN];
int main(void) {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; p[i].id = i, i++)
    scanf("%lld %lld", &p[i].x, &p[i].y);
  closest_pair::closest_pair(p, n);
  printf("%d %d %.6lf\n", closest_pair::idx[0], closest_pair::idx[1],
         sqrt(closest_pair::ans));
}
