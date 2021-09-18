#include "../../contest/header.hpp"
/*
        2D Segment Tree:
                2D point update and 2D range query in O(log(n)*log(m)) per
                operation,
                where n is the number of rows and m is the number of
   columns.

                Uses O(Num_Updates * log(n)*log(m)) memory.

                Given as an example using gcd.

        Usage:
                See main and comments.

        Author: Arthur Pratti Dadalto
*/
// Number of rows and columns (inner nodes need to know this).
int n, m;
struct nodes {
  ll val;
  nodes *left, *right;
  nodes() : val(0), left(NULL), right(NULL) {}
  // Update leaf tree.
  void update(int l, int r, int a, ll x) {
    if (l == r)
      val = x;
    else {
      int mid = (l + r) / 2;
      if (a <= mid)
        (left ? left : (left = new nodes()))->update(l, mid, a, x);
      else
        (right ? right : (right = new nodes()))->update(mid + 1, r, a, x);
      val = __gcd(left ? left->val : 0, right ? right->val : 0);
    }
  }
  // Update non-leaf tree by joining the two child trees along the
  // modified path.
  void updateb(int l, int r, int a, ll x, nodes *o, nodes *p) {
    if (l == r)
      val = __gcd(o ? o->val : 0, p ? p->val : 0);
    else {
      int mid = (l + r) / 2;
      if (a <= mid)
        (left ? left : (left = new nodes()))
            ->updateb(l, mid, a, x, o ? o->left : NULL,
                      p ? p->left : NULL);
      else
        (right ? right : (right = new nodes()))
            ->updateb(mid + 1, r, a, x, o ? o->right : NULL,
                      p ? p->right : NULL);
      val = __gcd(o ? o->val : 0, p ? p->val : 0);
    }
  }
  ll get(int l, int r, int a, int b) {
    if (l == a && r == b)
      return val;
    else {
      int mid = (l + r) / 2;
      if (b <= mid)
        return left ? left->get(l, mid, a, b) : 0;
      else if (a > mid)
        return right ? right->get(mid + 1, r, a, b) : 0;
      else
        return __gcd(left ? left->get(l, mid, a, mid) : 0,
                     right ? right->get(mid + 1, r, mid + 1, b) : 0);
    }
  }
};
struct nodef {
  nodes *val;
  nodef *left, *right;
  nodef() : left(NULL), right(NULL) { val = new nodes(); }
  void update(int l, int r, int a, int b, ll x) {
    if (l == r)
      val->update(0, m - 1, b, x);
    else {
      int mid = (l + r) / 2;
      if (a <= mid)
        (left ? left : (left = new nodef()))->update(l, mid, a, b, x);
      else
        (right ? right : (right = new nodef()))
            ->update(mid + 1, r, a, b, x);
      val->updateb(0, m - 1, b, x, left ? left->val : NULL,
                   right ? right->val : NULL);
    }
  }
  ll get(int l, int r, int a, int b, int c, int d) {
    if (l == a && r == b)
      return val->get(0, m - 1, c, d);
    else {
      int mid = (l + r) / 2;
      if (b <= mid)
        return left ? left->get(l, mid, a, b, c, d) : 0;
      else if (a > mid)
        return right ? right->get(mid + 1, r, a, b, c, d) : 0;
      else
        return __gcd(left ? left->get(l, mid, a, mid, c, d) : 0,
                     right ? right->get(mid + 1, r, mid + 1, b, c, d) : 0);
    }
  }
};
int main(void) {
  ll a;
  nodef *root = new nodef();
  int q, tp, x, y, z, w;
  scanf("%d %d %d", &n, &m, &q);
  while (q--) {
    scanf("%d", &tp);
    if (tp == 1) {
      scanf("%d %d %lld", &x, &y, &a);
      root->update(0, n - 1, x, y, a);
    } else {
      scanf("%d %d %d %d", &x, &y, &z, &w);
      printf("%lld\n", root->get(0, n - 1, x, z, y, w));
    }
  }
}
