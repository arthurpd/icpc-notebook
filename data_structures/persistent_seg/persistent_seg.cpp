#include "../../contest/header.hpp"
/*
        Persistent Segment Tree:
                Segment tree that stores all previous versions of itself.
                Every operation is O(log(r-l))
                Uses O(n*log(r-l)) memory, where n is the number of
   updates.

        Usage:
                A new root is created for every persistent update
   (p_update) and returned. Queries can be performed on any root as if it
   were a usual segment tree. You should keep a list of roots. Something
   like: vector<node *> roots = {new node()};
                        roots.push_back(p_update(roots.back(), 0,
                                                                         2*MAXV,
   a[i] + MAXV, v + 1));

        Constraints:
                Segment tree range [l, r] must be such that 0 <= l <= r.

        Author: Arthur Pratti Dadalto
*/
struct node {
  int val;
  node *left, *right;
  node(int x = 0) : val(x), left(NULL), right(NULL) {}
  node(node *l, node *r) : left(l), right(r) {
    val = (left ? left->val : 0) + (right ? right->val : 0);
  }
  int get(int l, int r, int a, int b) {
    if (l == a && r == b) return val;
    int mid = (l + 0ll + r) / 2;
    if (b <= mid)
      return left ? left->get(l, mid, a, b) : 0;
    else if (a > mid)
      return right ? right->get(mid + 1, r, a, b) : 0;
    else
      return (left ? left->get(l, mid, a, mid) : 0) +
             (right ? right->get(mid + 1, r, mid + 1, b) : 0);
  }
};
node *p_update(node *prev, int l, int r, int a, int x) {
  if (l == r) return new node(x);
  int mid = (l + 0ll + r) / 2;
  if (a <= mid)
    return new node(p_update(prev ? prev->left : NULL, l, mid, a, x),
                    prev ? prev->right : NULL);
  else
    return new node(prev ? prev->left : NULL,
                    p_update(prev ? prev->right : NULL, mid + 1, r, a, x));
}
