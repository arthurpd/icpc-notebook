#include "../../contest/header.hpp"

/*
	Transitive Closure:
		Given a directed graph adjacency matrix, computes closure, 
		where closure[i][j] = 1 if there is a path from i to j
		in the graph.
		Closure is computed in O(N^3 / 64) due to bitset.
		Also supports adding an edge to the graph and
		updating the closure accordingly in O(N^2 / 64).

	Constraints:
		Vertices are labeled from 0 to MAXN - 1 (inclusive).

	Performance:
		Solves something that should be 1000*300^3 = 27 * 10^9
		in 0.6 s (which is consistent with the approximation N^3 / 64
		since dividing by 64 we get 4 * 10^8).
*/

template<int MAXN>
struct transitive_closure
{
	vector<bitset<MAXN>> closure;

	template<class T>
	transitive_closure(T adj_matrix) : closure(MAXN)
	{
		for (int i = 0; i < MAXN; i++)
			for (int j = 0; j < MAXN; j++)
				closure[i][j] = adj_matrix[i][j];

		for (int i = 0; i < MAXN; i++)
			for (int j = 0; j < MAXN; j++)
				if (closure[j][i])
					closure[j] |= closure[i];
	}

	void add_edge(int a, int b)
	{
		if (closure[a][b])
			return;
		
		closure[a].set(b);
		closure[a] |= closure[b];

		for (int i = 0; i < MAXN; i++)
			if (closure[i][a])
				closure[i] |= closure[a];
	}
};

