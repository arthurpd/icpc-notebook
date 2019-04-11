#include <bits/stdc++.h>
using namespace std;

/*
    Dinic:
        Max-flow O(V^2E)
        Bipartite Matching O(sqrt(V)E)

    Constraints:
        Vertices are labeled from 0 to n (inclusive).
        Edge capacities must fit int (flow returned is long long).

    Usage:
        Set MAXV if necessary.
        Call init passing n, the source and the sink.
        Add edges to the graph by calling put_edge.
*/

#define inf 0x3f3f3f3f

namespace dinic
{
struct edge
{
    int dest, cap, re;
};

const int MAXV = 212345;

int n, s, t, d[MAXV], q[MAXV], next[MAXV];
vector<edge> graph[MAXV];

void init(int _n, int _s, int _t)
{
    n = _n, s = _s, t = _t;
    for (int i = 0; i <= n; i++)
        graph[i].clear();
}

void put_edge(int u, int v, int cap)
{
    graph[u].push_back({v, cap, (int)graph[v].size()});
    graph[v].push_back({u, 0, (int)graph[u].size() - 1});
}

void put_edge_undirected(int u, int v, int cap)
{
    graph[u].push_back({v, cap, (int)graph[v].size()});
    graph[v].push_back({u, cap, (int)graph[u].size() - 1});
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
            if (e.cap > 0 && d[e.dest] == inf)
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
        if (d[a] + 1 == d[e.dest] && e.cap != 0)
        {
            int x = dfs(e.dest, min(flow, e.cap));
            if (x == 0)
                continue;
            e.cap -= x;
            graph[e.dest][e.re].cap += x;
            return x;
        }
    }
    d[a] = inf;
    return 0;
}

long long max_flow()
{
    long long flow = 0;
    while (bfs())
    {
        memset(next, 0, sizeof(int) * (n + 1));
        while (int path_flow = dfs(s, inf))
            flow += path_flow;
    }
    return flow;
}
} // namespace dinic
