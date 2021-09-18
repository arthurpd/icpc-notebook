// https://codeforces.com/contest/1179/problem/D
#include "../line_container.cpp"
#define MAXN 512345
vector<int> graph[MAXN];
int n;
void put_edge(int a, int b) {
  graph[a].push_back(b);
  graph[b].push_back(a);
}
ll sub_size[MAXN];
ll ans;
ll tab[MAXN];
void dfs(int a, int p) {
  sub_size[a] = 1;
  for (int i = 0; i < graph[a].size(); i++) {
    if (graph[a][i] != p) {
      dfs(graph[a][i], a);
      sub_size[a] += sub_size[graph[a][i]];
    }
  }
  tab[a] = sub_size[a] * (n - sub_size[a]);
  for (int i = 0; i < graph[a].size(); i++) {
    if (graph[a][i] != p) {
      tab[a] = max(tab[a], tab[graph[a][i]] +
                               (sub_size[a] - sub_size[graph[a][i]]) *
                                   (n - sub_size[a]));
    }
  }
  line_container l;
  l.add(0, 0);
  for (int i = 0; i < graph[a].size(); i++) {
    // ans = max(ans , tab[graph[a][i]]);
    // for (int j = i - 1; j >= 0; j--)
    // {
    // 	ans = max(ans , tab[graph[a][i]] + tab[graph[a][j]] -
    // sub_size[graph[a][i]] * sub_size[graph[a][j]]);
    // }
    ans = max(ans, l.query(sub_size[graph[a][i]]) + tab[graph[a][i]]);
    l.add(-sub_size[graph[a][i]], tab[graph[a][i]]);
  }
}
int main(void) {
  int a, b;
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    scanf("%d %d", &a, &b);
    put_edge(a, b);
  }
  if (n == 2) {
    printf("2\n");
    return 0;
  }
  int root;
  for (int i = 1; i < n; i++)
    if (graph[i].size() > 1) root = i;
  dfs(root, root);
  cout << (ans) + (n)*1ll * (n - 1) / 2 << endl;
}
