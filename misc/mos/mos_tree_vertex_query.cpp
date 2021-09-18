#include "../../graph/lca/lca.cpp"
/*
        Mo's Algorithm on trees:
                Solve Q path queries in a tree of N vertices
                in O(N * sqrt(Q) * max(insertion time, removal time)).
                Queries should be on values associated to the tree
   vertices.

        Usage:
                Pass to the function a tree root, the number of vertices
   (n), a list of queries (pq) with both ends of each path, the graph and
   functions add, remove and output, such that: add(i) must add the vertex
   labeled i to your data structure (1 <= i <= n). remove(i) must remove
   the vertex labeled i (1 <= i <= n). output(i) should answer query pq[i]
   using current state.

                This will guarantee that when answering the i-th query,
   only the vertices on the desired path are currently in your data
                structure.

        Runs in 1s for 10^5 vertices and queries on CF.

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
  while (!s.empty())  // dfs pre-pos ordering.
  {
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
      q.push_back({st[a], st[b], i, -1});
    else
      q.push_back({en[a], st[b], i, st[y]});
    // For queries of this type, the lca must be separately
    // added.
  }
  int bsize = 1 + (2 * n) / sqrt(sz(q));
  sort(q.begin(), q.end(), [&](const query &lhs, const query &rhs) {
    if (lhs.l / bsize != rhs.l / bsize)
      return (lhs.l / bsize < rhs.l / bsize);
    return lhs.r < rhs.r;
  });
  // Vertices inserted twice are removed.
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
    if (q[i].lc != -1) consider(q[i].lc);
    output(q[i].id);
    if (q[i].lc != -1) consider(q[i].lc);
  }
}
