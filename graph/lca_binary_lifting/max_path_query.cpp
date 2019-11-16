#include "../../contest/header.hpp"

/*
	LCA:
		Solve lowest common ancestor queries in O(log(n))
		with O(n*log(n)) preprocessing time and O(n*log(n))
		memory.
		Additionally, when solving LCA between two nodes,
		also returns the maximum edge cost in the path
		between them.
	
	Usage:
		See LCA.

	Author: Arthur Pratti Dadalto
*/

struct lca_preprocess
{
	int lgn;
	vector<int> h;
	vector<vector<int>> p;
	vector<vector<ll>> c;

	void dfs(int a, const vector<vector<int>> &graph, const vector<vector<ll>> &cost)
	{
		for (int i = 0; i < sz(graph[a]); i++)
			if (graph[a][i] != p[0][a])
			{
				h[graph[a][i]] = h[a] + 1;
				p[0][graph[a][i]] = a;
				c[0][graph[a][i]] = cost[a][i];
				dfs(graph[a][i], graph, cost);
			}
	}

	lca_preprocess(int root, int n, const vector<vector<int>> &graph, const vector<vector<ll>> &cost) : h(n + 1)
	{
		lgn = 31 - __builtin_clz(n + 1);
		p.assign(lgn + 1, vector<int>(n + 1, 0));
		c.assign(lgn + 1, vector<ll>(n + 1, 0));

		p[0][root] = root;
		h[root] = 0;
		dfs(root, graph, cost);

		for (int i = 1; i <= lgn; i++)
			for (int j = 0; j <= n; j++)
			{
				p[i][j] = p[i - 1][p[i - 1][j]];
				c[i][j] = max(c[i - 1][j], c[i - 1][p[i - 1][j]]);
			}
	}

	// Pair of LCA and the maximum edge cost on the a-b path.
	pair<int, ll> lca(int a, int b)
	{
		if (h[a] < h[b])
			swap(a, b);

		ll res = 0;
		for (int i = lgn; i >= 0; i--)
			if (h[p[i][a]] >= h[b])
			{
				res = max(res, c[i][a]);
				a = p[i][a];
			}

		if (a == b)
			return {a, res};

		for (int i = lgn; i >= 0; i--)
			if (p[i][a] != p[i][b])
			{
				res = max(res, c[i][a]);
				a = p[i][a];

				res = max(res, c[i][b]);
				b = p[i][b];
			}

		return {p[0][a], max(c[0][b], max(res, c[0][a]))};
	}
};
