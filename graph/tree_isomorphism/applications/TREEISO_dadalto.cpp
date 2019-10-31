#include "../../../contest/header.hpp"

vector<vector<int>> graph;
vector<vector<int>> sub_size;
vector<bool> block;

int dfs_centroid(int a, int p, int sz, pii &centroid, int &val)
{
	int sum = 0, mx = 0, pidx = -1;
	for (int i = 0; i < sz(graph[a]); i++)
		if (graph[a][i] != p && !block[graph[a][i]])
		{
			int x = dfs_centroid(graph[a][i], a, sz, centroid, val);

			sub_size[a][i] = x;
			mx = max(x, mx);
			sum += x;
		}
		else if (graph[a][i] == p && !block[graph[a][i]])
			pidx = i;

	if (pidx != -1)
	{
		sub_size[a][pidx] = sz - sum - 1;
		mx = max(mx, sub_size[a][pidx]);
	}

	if (mx < val)
	{
		val = mx;
		centroid = {a, a};
	}

	if (mx == val)
		centroid.second = a;

	return sum + 1;
}

void put_edge(int a, int b)
{
	graph[a].push_back(b);
	sub_size[a].push_back(0);
	graph[b].push_back(a);
	sub_size[b].push_back(0);
}

int tab_id;
map<vector<int>, int> tab;

int invariant(int a, int p)
{
	vector<int> v;
	v.reserve(sz(graph[a]));
	for (int i = 0; i < sz(graph[a]); i++)
		if (graph[a][i] != p && !block[graph[a][i]])
			v.push_back(invariant(graph[a][i], a));
	sort(v.begin(), v.end());
	int &x = tab[v];
	if (x == 0)
		x = ++tab_id;

	return x;
}

bool isometric(int a, int b, int sz)
{
	int val_a = inf;
	pair<int, int> centroid_a;
	dfs_centroid(a, a, sz, centroid_a, val_a);

	int val_b = inf;
	pair<int, int> centroid_b;
	dfs_centroid(b, b, sz, centroid_b, val_b);

	int x = invariant(centroid_a.first, centroid_a.first);

	if (x == invariant(centroid_b.first, centroid_b.first) || x == invariant(centroid_b.second, centroid_b.second))
		return true;
	return false;
}

int main()
{
	cin.sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while (t--)
	{
		int n, a, b;
		cin >> n;
		tab_id = 0;
		tab.clear();
		graph.assign(2*n+1, vector<int>());
		sub_size.assign(2*n+1, vector<int>());
		block.assign(2*n+1, 0);

		for (int i = 1; i < n; i++)
		{
			cin >> a >> b;
			put_edge(a, b);
		}
		for (int i = 1; i < n; i++)
		{
			cin >> a >> b;
			put_edge(n + a, n + b);
		}

		cout << (isometric(1, n + 1, n) ? "YES" : "NO") << endl;
	}
}
