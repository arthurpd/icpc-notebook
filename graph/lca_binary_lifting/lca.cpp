#include "../../contest/header.hpp"

/*
	LCA:
		Solve lowest common ancestor queries in O(log(n))
		with O(n*log(n)) preprocessing time and O(n*log(n))
		memory.
	
	Usage:
		Initialize struct with tree root, number of vertices
		and graph. Has been tested with label in [1, n], but should
		work for labels in [0, n].

	Author: Arthur Pratti Dadalto
*/

struct lca_preprocess
{
	int lgn;
	vector<int> h;
	vector<vector<int>> p;
	vector<int> *graph;

	void dfs(int a)
	{
		for (int i = 0; i < sz(graph[a]); i++)
			if (graph[a][i] != p[0][a])
			{
				h[graph[a][i]] = h[a] + 1;
				p[0][graph[a][i]] = a;
				dfs(graph[a][i]);
			}
	}

	lca_preprocess(int root, int n, vector<int> graph[]) : h(n + 1), graph(graph)
	{
		lgn = 31 - __builtin_clz(n + 1);
		p.assign(lgn + 1, vector<int>(n + 1, 0));

		p[0][root] = root;
		h[root] = 0;
		dfs(root);

		for (int i = 1; i <= lgn; i++)
			for (int j = 0; j <= n; j++)
				p[i][j] = p[i - 1][p[i - 1][j]];
	}

	int lca(int a, int b)
	{
		if (h[a] < h[b])
			swap(a, b);
		for (int i = lgn; i >= 0; i--)
			if (h[p[i][a]] >= h[b])
				a = p[i][a];

		if (a == b)
			return a;

		for (int i = lgn; i >= 0; i--)
			if (p[i][a] != p[i][b])
			{
				a = p[i][a];
				b = p[i][b];
			}

		return p[0][a];
	}

	int dist(int a, int b)
	{
		return h[a] + h[b] - 2 * h[lca(a, b)];
	}
};
