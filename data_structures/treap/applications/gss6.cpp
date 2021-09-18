// https://www.spoj.com/problems/GSS6/
#include "../../../contest/header.hpp"
namespace treap {
struct node {
  node *l = 0, *r = 0;
  int val;  // Any value associated with node.
  ll tab;
  ll sum;
  ll pref;
  ll suf;
  int p;      // Node heap priority.
  int c = 1;  // Node subtree size.
  node(int val)
      : val(val),
        tab(val),
        sum(val),
        pref(max(0, val)),
        suf(max(0, val)),
        p(rand()) {}
  void recalc();
};
int cnt(node *n) { return n ? n->c : 0; }
ll get_sum(node *n) { return n ? n->sum : 0; }
ll get_pref(node *n) { return n ? n->pref : 0; }
ll get_suf(node *n) { return n ? n->suf : 0; }
ll get_tab(node *n) { return n ? n->tab : -infll; }
void node::recalc()  // To augment with extra data you should mostly add
                     // stuff to this function.
{
  c = cnt(l) + cnt(r) + 1;
  sum = get_sum(l) + get_sum(r) + val;
  pref = max(get_pref(l), get_sum(l) + get_pref(r) + val);
  suf = max(get_suf(r), get_sum(r) + get_suf(l) + val);
  tab = max(max(get_tab(l), get_tab(r)), get_suf(l) + val + get_pref(r));
}
// Apply function f on each tree node in order.
template <class F>
void each(node *n, F f) {
  if (n) {
    each(n->l, f);
    f(n->val);
    each(n->r, f);
  }
}
// Split treap rooted at n in two treaps containing [0, k) and [k, ...)
pair<node *, node *> split(node *n, int k) {
  if (!n) return {NULL, NULL};
  if (cnt(n->l) >= k)  // "n->val >= k" for lower_bound(k)
  {
    auto pa = split(n->l, k);
    n->l = pa.second;
    n->recalc();
    return {pa.first, n};
  } else {
    auto pa = split(n->r, k - cnt(n->l) - 1);  // and just "k"
    n->r = pa.first;
    n->recalc();
    return {n, pa.second};
  }
}
// Merge treaps l and r keeping order (l first).
node *merge(node *l, node *r) {
  if (!l) return r;
  if (!r) return l;
  if (l->p > r->p) {
    l->r = merge(l->r, r);
    l->recalc();
    return l;
  } else {
    r->l = merge(l, r->l);
    r->recalc();
    return r;
  }
}
// Insert treap rooted at n into position pos of treap rooted at t.
// Also used to insert one node (e.g. root = ins(root, new node(10), 3))
node *ins(node *t, node *n, int pos) {
  auto pa = split(t, pos);
  return merge(merge(pa.first, n), pa.second);
}
// Remove node at position pos from treap rooted at t.
node *rem(node *t, int pos) {
  node *a, *b, *c;
  tie(a, b) = split(t, pos);
  tie(b, c) = split(b, 1);
  delete b;
  return merge(a, c);
}
// Do a query in range [l, r].
node *query(node *t, int l, int r) {
  node *a, *b, *c;
  tie(a, b) = split(t, l);
  tie(b, c) = split(b, r - l + 1);
  printf("%lld\n", b->tab);
  return merge(merge(a, b), c);
}
// Example application: move the range [l, r) to index k.
void move(node *&t, int l, int r, int k) {
  node *a, *b, *c;
  tie(a, b) = split(t, l);
  tie(b, c) = split(b, r - l);
  if (k <= l)
    t = merge(ins(a, b, k), c);
  else
    t = merge(a, ins(c, b, k - r));
}
}  // namespace treap
int main(void) {
  treap::node *root = nullptr;
  int n, q, x, y;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &x);
    root = treap::ins(root, new treap::node(x), i);
  }
  char tp;
  scanf("%d", &q);
  for (int i = 0; i < q; i++) {
    scanf(" %c", &tp);
    if (tp == 'I') {
      scanf("%d %d", &x, &y);
      x--;
      root = treap::ins(root, new treap::node(y), x);
    } else if (tp == 'D') {
      scanf("%d", &x);
      x--;
      root = treap::rem(root, x);
    } else if (tp == 'R') {
      scanf("%d %d", &x, &y);
      x--;
      root = treap::rem(root, x);
      root = treap::ins(root, new treap::node(y), x);
    } else {
      scanf("%d %d", &x, &y);
      x--;
      y--;
      root = treap::query(root, x, y);
    }
  }
}
