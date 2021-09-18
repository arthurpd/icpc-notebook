// https://www.spoj.com/problems/MKTHNUM/
#include "../persistent_seg.cpp"
#define MAXN 112345
int a[MAXN];
int get_left(node *r) {
  if (r && r->left) return r->left->val;
  return 0;
}
int query(node *r1, node *r2, int l, int r, int k) {
  if (l == r) return l;
  int mid = (l + 0ll + r) / 2;
  int x = get_left(r2) - get_left(r1);
  if (k <= x)
    return query(r1 ? r1->left : r1, r2 ? r2->left : r2, l, mid, k);
  else
    return query(r1 ? r1->right : r1, r2 ? r2->right : r2, mid + 1, r,
                 k - x);
}
int main(void) {
  int MAXV = 1e9;
  int n, m;
  scanf("%d %d", &n, &m);
  vector<node *> roots = {new node()};
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    int v = roots.back()->get(0, 2 * MAXV, a[i] + MAXV, a[i] + MAXV);
    roots.push_back(
        p_update(roots.back(), 0, 2 * MAXV, a[i] + MAXV, v + 1));
  }
  for (int i = 0; i < m; i++) {
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    printf("%d\n", query(roots[x - 1], roots[y], 0, 2 * MAXV, z) - MAXV);
  }
}
