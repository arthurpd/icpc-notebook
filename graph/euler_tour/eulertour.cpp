/*
    [DEFINITION]
        a) Eulerian Path: visits every edge only once, but can repeat vertices.
        b) Eulerian Cycle: is a eulerian path that is a cycle (start vertice == end vertice)
        OBS: We disconsider vertices that have indegree==outdegree==0 (we call them as useless vertices)

    [CONDITIONS] 
        [Undirected graph]
            [Path/Cycle]
            a) The number of vertices with odd degrees is 2(Eulerian Path) or 0(Eulerian cycle) 
            b) The graph of useful vertices (see OBS above) should be connected
            If either of the above condition fails Euler Path/Cycle can't exist.
        [Directed graph] 
            [Cycle]
                a) All vertices should have (indegree==outdegree)
                b) The UNDIRECTED version of the graph of useful vertices (see OBS above) should be connected
            [Path]
                a) Equal to Cycle's conditions, but:
                b) There should be a vertex in the graph which has (indegree+1==outdegree)
                d) There should be a vertex in the graph which has (indegree==outdegree+1)
            If either of the above condition fails Euler Path/Cycle can't exist.
        OBS: The "connected" condition it's not explicit tested by the algorithm because it's enough checking the size
        of the found path.

   [COMPLEXITY] O(V + E)

   [USAGE]  
        You should initialize the following global variables      
            [vertices]
                * 0-indexed
                * It's fine to include useless vertices
                
            [edges]
                * In undirected graphs be sure that you created just one edge and u,v have this
                edge in the outs vector.

            [n] number of total vertices (including useless)
            [m] number of total edges
                
        You should call init() before call euler_tour(n_edges), the n_edges argument is how many edges
        you are expecting to traverse in the euler_tour/walk.
        
        [return]
            An integer vector that represents the vertices' indexes of the found cycle (when exists)
            or the found path (when exists). If none was found, an empty vector is returned.
            You can change the return value to be an integer vector that represent the edges' indexes.
            OBS: You can check if the returned value is a path by checking if ret.front() != ret.back()

        [reset]
            If the problem has several testcases, don't forget to reset global vars

 */

#include "../../contest/header.hpp"

namespace euler
{

#define MAXM 112345
#define MAXN 112345

struct edge {
	int u, v, id;
};

struct vertice {
	vi outs;  // edges indexes
	int in_degree = 0; // not used with undirected graphs
};

int n, m;
edge edges[MAXM];
vertice vertices[MAXN];
vi::iterator its[MAXN];
bool used_edge[MAXM];

void init()
{
	for (int i = 0; i < n; i++)
	{
		its[i] = vertices[i].outs.begin();
	}
}

vi euler_tour(int n_edges, int src) {
	vi ret_vertices;
	//vi ret_edges;
	vector<pii> s = {{src, -1}};
	while(!s.empty()) 
    {
		int x = s.back().first;
		int e = s.back().second;
		auto &it = its[x], end = vertices[x].outs.end();

		while(it != end && used_edge[*it]) 
            ++it;

		if(it == end) 
        { 
            ret_vertices.push_back(x);
			//ret_edges.push_back(e);
            s.pop_back(); 
        }
		else 
        { 
			auto edge = edges[*it];
            int v = edge.u == x ? edge.v:edge.u;
            s.push_back({v, *it});
            used_edge[*it] = true; 
        }
	}
	if (sz(ret_vertices) != n_edges+1)
		ret_vertices.clear(); // No Eulerian cycles/paths.
	/*
	if (sz(ret_edges) != n_edges)
		ret_edges.clear(); // No Eulerian cycles/paths.
	*/
	
	// Check if is cycle ret_vertices.front() == ret_vertices.back()

	reverse(all(ret_vertices));
	return ret_vertices;
	
	/*
	reverse(all(ret_edges));
	return ret_edges;
	*/
}

}
