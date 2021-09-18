// https://www.spoj.com/problems/COT2/
#include "../mos_tree_vertex_query.cpp"
#define MAXN 41234
#define MAXQ 112345
vector<int> graph[MAXN];
int x[MAXN];
int ans[MAXQ];
int freq[MAXN];
int val = 0;
void add(int a) {
  if (++freq[x[a]] == 1) val++;
}
void remove(int a) {
  if (--freq[x[a]] == 0) val--;
}
void output(int i) { ans[i] = val; }
int main(void) {
  int n, m, a, b;
  scanf("%d %d", &n, &m);
  map<int, int> rdm;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &x[i]);
    rdm[x[i]] = 1;
  }
  int tmp = 0;
  for (auto &kvp : rdm) kvp.second = tmp++;
  for (int i = 1; i <= n; i++) x[i] = rdm[x[i]];
  for (int i = 1; i < n; i++) {
    scanf("%d %d", &a, &b);
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  vector<pii> q(m);
  for (int i = 0; i < m; i++) scanf("%d %d", &q[i].first, &q[i].second);
  mos_tree(n, n, q, graph, add, remove, output);
  for (int i = 0; i < sz(q); i++) printf("%d\n", ans[i]);
}
