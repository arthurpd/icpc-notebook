// https://codeforces.com/contest/343/problem/E

#include "../gomory_hu.cpp"

int ans;
vector<int> ord;
vector<set<pii>> graph;

tuple<int,int,int> dfs(int a, int p)
{
	tuple<int,int,int> retv = {inf, 0, 0};
	for (auto &e : graph[a])
		if (e.first != p)
		{
			retv = min(retv, dfs(e.first, a));
			retv = min(retv, {e.second, e.first, a});
		}

	return retv;
}

void solve(int a)
{
	int u, v, w;
	tie(w, u, v) = dfs(a, a);
	if (w == inf)
		ord.push_back(a);
	else
	{
		graph[u].erase({v, w});
		graph[v].erase({u, w});
		solve(u);
		solve(v);
		ans += w;
	}
}

int main(void)
{
	cin.sync_with_stdio(0);
	cin.tie(0);

	int n, m, a, b, c;
	cin >> n >> m;
	graph.assign(n, set<pii>());

	gomory_hu gh;
	for (int i = 0; i < m; i++)	
	{
		cin >> a >> b >> c;
		gh.add_edge(a - 1, b - 1, c);
	}

	auto tree_edges = gh.solve(n);

	for (int i = 1; i < n; i++)
	{
		graph[tree_edges[i].second].insert({i, (int)tree_edges[i].first});
		graph[i].insert({tree_edges[i].second, (int)tree_edges[i].first});
	}

	solve(0);

	cout << ans << endl;
	for (int i = 0; i < n; i++)
		cout << ord[i] + 1 << " ";
	cout << endl;
}
