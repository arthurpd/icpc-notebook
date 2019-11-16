// https://codeforces.com/contest/1253/problem/F
#include "../max_path_query.cpp"

struct edge
{
	int u, v;
	ll w;

	bool operator<(edge rhs)
	{
		return w < rhs.w;
	}
};

void solve_queries(int n, vector<edge> e, int q)
{
	vector<vector<int>> graph(n);
	vector<vector<ll>> cost(n);
	for (int i = 0; i < n - 1; i++)
	{
		graph[e[i].u].push_back(e[i].v);
		cost[e[i].u].push_back(e[i].w);

		graph[e[i].v].push_back(e[i].u);
		cost[e[i].v].push_back(e[i].w);
	}

	lca_preprocess lca(0, n - 1, graph, cost);
	for (int i = 0; i < q; i++)
	{
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		cout << lca.lca(a, b).second << endl;
	}
}

struct union_find
{
	vector<int> p, size;
	union_find(int n) : p(n), size(n, 1)
	{
		iota(p.begin(), p.end(), 0);
	}

	int find(int a)
	{
		return (p[a] == a) ? a : (p[a] = find(p[a]));
	}

	void join(int a, int b)
	{
		a = find(a);
		b = find(b);
		if (a == b)
			return;
		if (size[a] < size[b])
			swap(a, b);
		p[b] = a;
		size[a] += size[b];
	}
};

int main()
{
	cin.sync_with_stdio(0);
	cin.tie(0);

	int n, m, k, nq, a;
	ll x;
	cin >> n >> m >> k >> nq;
	vector<edge> e(m);
	vector<vector<int>> graph(n);
	vector<vector<ll>> cost(n);
	for (int i = 0; i < m; i++)
	{
		cin >> e[i].u >> e[i].v >> e[i].w;
		e[i].u--;
		e[i].v--;
		graph[e[i].u].push_back(e[i].v);
		cost[e[i].u].push_back(e[i].w);

		graph[e[i].v].push_back(e[i].u);
		cost[e[i].v].push_back(e[i].w);
	}

	vector<ll> d(n, infll);
	vector<int> p(n, -1);
	priority_queue<pair<ll, int>> q;
	for (int i = 0; i < k; i++)
	{
		d[i] = 0;
		p[i] = i;
		q.push({d[i], i});
	}

	while (!q.empty())
	{
		tie(x, a) = q.top();
		q.pop();
		if (x != -d[a])
			continue;

		for (int i = 0; i < sz(graph[a]); i++)
			if (d[a] + cost[a][i] < d[graph[a][i]])
			{
				d[graph[a][i]] = d[a] + cost[a][i];
				p[graph[a][i]] = p[a];
				q.push({-d[graph[a][i]], graph[a][i]});
			}
	}

	vector<edge> mste;
	for (int i = 0; i < m; i++)
	{
		if (p[e[i].u] != p[e[i].v])
			mste.push_back({p[e[i].u], p[e[i].v], d[e[i].u] + d[e[i].v] + e[i].w});
	}

	vector<edge> tree;
	sort(mste.begin(), mste.end());
	union_find uf(k);
	for (int i = 0; i < sz(mste); i++)
		if (uf.find(mste[i].u) != uf.find(mste[i].v))
		{
			tree.push_back(mste[i]);
			uf.join(mste[i].u, mste[i].v);
		}

	solve_queries(k, tree, nq);
}
