#include "../../contest/header.hpp"

/*
	Centroid Decomposition:
		Solve tree problems by divide and conquer splitting the tree repeatedly on centroid.
		Centroid is the vertex with smallest <largerst subtree>.
		O(n log n if process is O(sz))

	Usage:
		Call put_edge to initialize the tree edges.
		Then call decomp(i, n) for any vertex i in the tree, with n being the number of vertices.
		Function process will be called for a centroid <a> with subtree total size sz.
			In process you can use:
			graph[a][i] - graph adjacency list
			block[a] - true if you should ignore the vertex.
			sub_size[a][i] - subtree size for edge a -> graph[a][i] (considering only non-blocked parts).
		
		if process can be O(sz + h * log) where h is subtree height it is a lot better constant than
		O(sz * log)

	PRINT APPLICATION WITH THIS.

	Author: Arthur Pratti Dadalto
*/

#define MAXN 112345

void process(int a, int sz);

vector<int> graph[MAXN];
vector<int> sub_size[MAXN];
bool block[MAXN];

int dfs_centroid(int a, int p, int sz, int &centroid, int &val)
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
		val = mx, centroid = a;

	return sum + 1;
}

void decomp(int a, int sz)
{
	int val = inf;
	dfs_centroid(a, a, sz, a, val);

	process(a, sz);

	block[a] = true;
	for (int i = 0; i < sz(graph[a]); i++)
		if (!block[graph[a][i]])
			decomp(graph[a][i], sub_size[a][i]);
}

void put_edge(int a, int b)
{
	graph[a].push_back(b);
	sub_size[a].push_back(0);
	graph[b].push_back(a);
	sub_size[b].push_back(0);
}
