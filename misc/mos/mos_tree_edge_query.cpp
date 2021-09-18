#include "../../graph/lca/lca.cpp"
/*
        Refer to the vertex queries option for more info.
        This version is different since it is made to handle queries on
        the cost of the edges in a path.

        To do that, transfer the cost to the vertex down in the rooted
        tree and use this.

        Remember to use a valid value for the root (even if it never will
        be in a query).
        Also remember some queries will be empty.

        Author: Arthur Pratti Dadalto
*/
struct query {
  int l, r, id, lc;
};
template <class F>
void mos_tree(int root, int n, vector<pii> pq, vector<int> graph[],
              const F &add, const F &remove, const F &output) {
  int a, b;
  lca_preprocess lca(root, n, graph);
  vector<int> st(n + 1, 0), en(n + 1, 0), v(2 * n + 3, 0), cnt(n + 1, 0),
      s;
  int id = 0;
  s.push_back(root);
  while (!s.empty()) {
    a = s.back();
    s.pop_back();
    if (st[a])
      v[en[a] = ++id] = a;
    else {
      v[st[a] = ++id] = a;
      s.push_back(a);
      for (int i = 0; i < sz(graph[a]); i++)
        if (graph[a][i] != lca.p[0][a]) s.push_back(graph[a][i]);
    }
  }
  vector<query> q;
  for (int i = 0; i < sz(pq); i++) {
    tie(a, b) = pq[i];
    if (st[a] > st[b]) swap(a, b);
    int y = lca.lca(a, b);
    if (a == y)
      q.push_back({st[a], st[b], i, st[y]});
    else
      q.push_back({en[a], st[b], i, -1});
  }
  int bsize = 1 + (2 * n) / sqrt(sz(q));
  sort(q.begin(), q.end(), [&](const query &lhs, const query &rhs) {
    if (lhs.l / bsize != rhs.l / bsize)
      return (lhs.l / bsize < rhs.l / bsize);
    return lhs.r < rhs.r;
  });
  auto consider = [&](int i) {
    cnt[v[i]]++;
    if (cnt[v[i]] % 2 == 1)
      add(v[i]);
    else
      remove(v[i]);
  };
  int l = 1, r = 0;
  for (int i = 0; i < sz(q); i++) {
    while (l > q[i].l) consider(--l);
    while (r < q[i].r) consider(++r);
    while (l < q[i].l) consider(l++);
    while (r > q[i].r) consider(r--);
    if (q[i].lc != -1)  // Remove LCA weight if necessary.
      consider(q[i].lc);
    output(q[i].id);
    if (q[i].lc != -1) consider(q[i].lc);
  }
}
