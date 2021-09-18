// https://codeforces.com/contest/1236/problem/F
#include "../modular_arithmetic.cpp"
#define MAXN 512345
#define mod_num mod_num<1000000007>
vector<int> graph[MAXN];
int been[MAXN];
vector<int> st;
vector<vector<int>> rings;
vector<pii> edges;
mod_num vertex_rings_factor[MAXN];
void dfs(int a, int p) {
  been[a] = 1;
  st.push_back(a);
  for (int i = 0; i < sz(graph[a]); i++) {
    if (graph[a][i] != p) {
      if (been[graph[a][i]] == 0)
        dfs(graph[a][i], a);
      else if (been[graph[a][i]] == 1) {
        vector<int> tmp;
        for (int j = sz(st) - 1; st[j] != graph[a][i]; j--)
          tmp.push_back(st[j]);
        tmp.push_back(graph[a][i]);
        rings.push_back(tmp);
      }
    }
  }
  st.pop_back();
  been[a] = 2;
}
bool intersect(const vector<int> &v1, const vector<int> &v2) {
  for (int i = 0; i < sz(v1); i++)
    if (find(v2.begin(), v2.end(), v1[i]) != v2.end()) return true;
  return false;
}
int main() {
  cin.sync_with_stdio(0);
  cin.tie(0);
  int n, m, a, b;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> a >> b;
    edges.push_back({min(a, b), max(a, b)});
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  dfs(1, 1);
  vector<mod_num> pot2div(max(11, n + 1));
  pot2div[0] = mod_num(1);
  pot2div[1] = pot2div[0] / mod_num(2);
  for (int i = 2; i < sz(pot2div); i++)
    pot2div[i] = pot2div[i - 1] * pot2div[1];
  mod_num sum_rings_factors(0);
  for (int i = 0; i < sz(rings); i++) {
    sum_rings_factors += pot2div[sz(rings[i])];
    for (int x : rings[i]) {
      vertex_rings_factor[x] += pot2div[sz(rings[i])];
    }
  }
  vector<mod_num> intersecting_rings_factors(sz(rings));
  for (int i = 0; i < sz(rings); i++)
    for (int x : rings[i])
      intersecting_rings_factors[i] +=
          vertex_rings_factor[x] - pot2div[sz(rings[i])];
  mod_num ex =
      (mod_num(2) ^ 0) * mod_num(n) / mod_num(2) - mod_num(m) / mod_num(4);
  for (int i = 0; i < sz(rings); i++) ex += pot2div[sz(rings[i])];
  mod_num ex2(0);
  mod_num ev2 = mod_num(n) * mod_num(n - 1) / (mod_num(2) ^ 2) +
                mod_num(n) / (mod_num(2) ^ 1);
  mod_num ee2(0);
  for (int i = 0; i < m; i++) {
    ee2 += pot2div[2];
    ee2 += mod_num(sz(graph[edges[i].first]) + sz(graph[edges[i].second]) -
                   2) *
           pot2div[3];
    ee2 += mod_num(m - (sz(graph[edges[i].first]) +
                        sz(graph[edges[i].second]) - 1)) *
           pot2div[4];
  }
  mod_num er2(0);
  for (int i = 0; i < sz(rings); i++) {
    er2 += pot2div[sz(rings[i])];
    er2 += pot2div[sz(rings[i]) - 1] * intersecting_rings_factors[i];
    er2 += pot2div[sz(rings[i])] *
           (sum_rings_factors - intersecting_rings_factors[i] -
            pot2div[sz(rings[i])]);
  }
  mod_num eve;
  for (int i = 1; i <= n; i++) {
    eve += mod_num(sz(graph[i])) * pot2div[2];
    eve += mod_num(m - sz(graph[i])) * pot2div[3];
  }
  mod_num eer;
  for (int j = 0; j < sz(rings); j++) {
    int k = sz(rings[j]);
    eer += mod_num(sz(rings[j])) * pot2div[sz(rings[j])];
    for (int x : rings[j]) {
      eer += mod_num(sz(graph[x]) - 2) * pot2div[sz(rings[j]) + 1];
      k += sz(graph[x]) - 2;
    }
    eer += mod_num(m - k) * pot2div[sz(rings[j]) + 2];
  }
  mod_num evr;
  for (int i = 1; i <= n; i++) {
    evr += vertex_rings_factor[i];
    evr += (sum_rings_factors - vertex_rings_factor[i]) * pot2div[1];
  }
  ex2 = ev2 + ee2 + er2 - mod_num(2) * eve - mod_num(2) * eer +
        mod_num(2) * evr;
  cout << (mod_num(2) ^ (1000000007)) * (ex2 - ex * ex) *
              (mod_num(2) ^ (1000000005))
       << endl;
}
