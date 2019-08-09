#include "../../contest/header.hpp"

/*
	Strongly connected components in O(V + E):
		Finds all strongly connected components of a graph.
        A strongly connected component is a maximal set of vertices such that
        every vertex can reach every other vertex in the component.
        The graph where the SCCs are considered vertices is a DAG.

	Constraints:
		Vertices are labeled from 1 to n (inclusive).

	Usage:
		Create the struct setting the maximum vertex label (n) and the graph adjacency list (graph).
		Aftewards, ncomp has the number of SCCs in the graph and scc[i] indicates the SCC i
        belongs to (1 <= scc[i] <= ncomp).
		
        sorted is a topological ordering of the graph, byproduct of the algorithm.
        if edge a -> b exists, a appears before b in the sorted list.
*/


struct scc_decomp
{
    vector<int> *graph;
    vector<vector<int>> tgraph;
    vector<int> scc;
    vector<bool> been;
    int ncomp;
    list<int> sorted;

    scc_decomp(int n, vector<int> graph[]) : graph(graph), tgraph(n + 1), scc(n + 1, 0), been(n + 1, false), ncomp(0)
    {
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < graph[i].size(); j++)
                tgraph[graph[i][j]].push_back(i);

        for (int i = 1; i <= n; i++)
			if(!been[i])
				dfs(i);

		for(int a : sorted)
			if(scc[a] == 0)
			{
                ncomp++;
				dfst(a);
			}
    }

    void dfs(int a)
    {
        been[a] = true;
        for(int i = 0; i < graph[a].size(); i++)
            if(!been[graph[a][i]])
                dfs(graph[a][i]);
        sorted.push_front(a);
    }
    
    void dfst(int a)
    {
        been[a] = true;
        scc[a] = ncomp;
        for(int i = 0; i < tgraph[a].size(); i++)
            if(scc[tgraph[a][i]] == 0)
                dfst(tgraph[a][i]);
    }
};
