#include "../../contest/header.hpp"

/*
	Global Min Cut O(n^3):
		Given an undirected weighted graph, find the minimum cut
		regardless of which set of vertices it splits.
	
	Usage:
		Vertices from 0 to n-1. Give adjecency matrix of weights.
		Function returns total cost of min cut and set of vertices
		forming one side of the cut.
		Sum of edge weights must fit int.
*/

pair<int, vector<int>> mincut(int n, vector<vector<int>> g /*adj matrix*/)
{
	int best_cost = inf;
	vector<int> best_cut;

	vector<int> v[n];
	for (int i = 0; i < n; ++i)
		v[i].assign(1, i);
	int w[n];
	bool exist[n], in_a[n];
	memset(exist, true, sizeof(exist));
	for (int ph = 0; ph < n - 1; ++ph)
	{
		memset(in_a, false, sizeof(in_a));
		memset(w, 0, sizeof(w));
		for (int it = 0, prev; it < n - ph; ++it)
		{
			int sel = -1;
			for (int i = 0; i < n; ++i)
				if (exist[i] && !in_a[i] && (sel == -1 || w[i] > w[sel]))
					sel = i;
			if (it == n - ph - 1)
			{
				if (w[sel] < best_cost)
					best_cost = w[sel], best_cut = v[sel];
				v[prev].insert(v[prev].end(), v[sel].begin(), v[sel].end());
				for (int i = 0; i < n; ++i)
					g[prev][i] = g[i][prev] += g[sel][i];
				exist[sel] = false;
			}
			else
			{
				in_a[sel] = true;
				for (int i = 0; i < n; ++i)
					w[i] += g[sel][i];
				prev = sel;
			}
		}
	}

	return pair<int, vector<int>>(best_cost, best_cut);
}

