#include <bits/stdc++.h>
using namespace std;

/*
	Hopcroft-Karp:
		Bipartite Matching O(sqrt(V)E)

	Constraints:
		Vertices are labeled from 1 to l + r (inclusive).
		DO NOT use vertex 0.
		Vertices 1 to l belong to left partition.
		Vertices l + 1 to l + r belong to right partition.

	Usage:
		Set MAXV if necessary.
		Call init passing l and r.
		Add edges to the graph from left side to right side.
		Call hopcroft to get the matching size.
		Then, each vertex v has its pair indicated in p[v] (or 0 for not paired).
*/

namespace hopcroft
{
const int inf = 0x3f3f3f3f;
const int MAXV = 112345;

vector<vector<int>> graph;
int d[MAXV], q[MAXV], p[MAXV], l, r;

void init(int _l, int _r)
{
	l = _l, r = _r;
	graph = vector<vector<int>>(l + r + 1);
}

bool bfs()
{
	int qb = 0, qe = 0;
	memset(d, 0x3f, sizeof(int) * (l + 1));
	for (int i = 1; i <= l; i++)
		if (p[i] == 0)
			d[i] = 0, q[qe++] = i;

	while (qb < qe)
	{
		int a = q[qb++];
		if (a == 0)
			return true;
		for (int i = 0; i < graph[a].size(); i++)
			if (d[p[graph[a][i]]] == inf)
				d[q[qe++] = p[graph[a][i]]] = d[a] + 1;
	}

	return false;
}

bool dfs(int a)
{
	if (a == 0)
		return true;
	for (int i = 0; i < graph[a].size(); i++)
		if (d[a] + 1 == d[p[graph[a][i]]])
			if (dfs(p[graph[a][i]]))
			{
				p[a] = graph[a][i];
				p[graph[a][i]] = a;
				return true;
			}

	d[a] = inf;
	return false;
}

int hopcroft()
{
	memset(p, 0, sizeof(int) * (l + r + 1));
	int matching = 0;
	while (bfs())
	{
		for (int i = 1; i <= l; i++)
			if (p[i] == 0)
				if (dfs(i))
					matching++;
	}

	return matching;
}
} // namespace hopcroft
