#include "../../../contest/header.hpp"

/*
	Dinic with Scaling:
		Max-flow O(VE * log(MAX_CAP)), but usually slower than regular Dinic.

	Constraints:
		Vertices are labeled from 0 to n (inclusive).
		Edge capacities must fit int (flow returned is long long).

	Usage:
		Set MAXV if necessary.
		Call init passing n, the source and the sink.
		Add edges to the graph by calling put_edge(_undirected).
		Call max_flow to get the total flow. Then, individual edge flows can be retrieved in the graph.
		Note that flow will be negative in return edges.
*/

namespace dinic
{
struct edge
{
	int dest, cap, re, flow;
};

const int inf = 0x3f3f3f3f;
const int MAXV = 312345;

int n, s, t, lim, d[MAXV], q[MAXV], next[MAXV];
vector<vector<edge>> graph;

void init(int _n, int _s, int _t)
{
	n = _n, s = _s, t = _t;
	graph = vector<vector<edge>>(n + 1);
}

void put_edge(int u, int v, int cap)
{
	graph[u].push_back({v, cap, (int)graph[v].size(), 0});
	graph[v].push_back({u, 0, (int)graph[u].size() - 1, 0});
}

void put_edge_undirected(int u, int v, int cap)
{
	graph[u].push_back({v, cap, (int)graph[v].size(), 0});
	graph[v].push_back({u, cap, (int)graph[u].size() - 1, 0});
}

bool bfs()
{
	int qb = 0, qe = 0;
	q[qe++] = s;
	memset(d, 0x3f, sizeof(int) * (n + 1));
	d[s] = 0;
	while (qb < qe)
	{
		int a = q[qb++];
		if (a == t)
			return true;
		for (int i = 0; i < (int)graph[a].size(); i++)
		{
			edge &e = graph[a][i];
			if (e.cap - e.flow >= lim && d[e.dest] == inf)
				d[q[qe++] = e.dest] = d[a] + 1;
		}
	}

	return false;
}

int dfs(int a, int flow)
{
	if (a == t)
		return flow;
	for (int &i = next[a]; i < (int)graph[a].size(); i++)
	{
		edge &e = graph[a][i];
		if (d[a] + 1 == d[e.dest] && e.cap - e.flow >= lim /* >= 1 ? */)
		{
			int x = dfs(e.dest, min(flow, e.cap - e.flow));
			if (x == 0)
				continue;
			e.flow += x;
			graph[e.dest][e.re].flow -= x;
			return x;
		}
	}

	d[a] = inf;
	return 0;
}

long long max_flow()
{
	long long total_flow = 0;
    for (lim = (1 << 30); lim >= 1; lim >>= 1)
		while (bfs())
		{
			memset(next, 0, sizeof(int) * (n + 1));
			while (int path_flow = dfs(s, inf))
				total_flow += path_flow;
		}

	return total_flow;
}
} // namespace dinic
