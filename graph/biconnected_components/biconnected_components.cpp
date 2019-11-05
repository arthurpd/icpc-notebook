#include "../../contest/header.hpp"

/*
	Finding bridges, articulation points and biconnected components in
		O(V + E):
		A bridge is an edge whose removal splits the graph in two 
		connected components.
		An articulation point is a vertex whose removal splits the 
		graph in two connected components.

		A biconnected component (or 2VCC) is a maximal subgraph where 
		the removal of any vertex doesn't
        make the subgraph disconnected. In other words, it is a 
		maximal 2-vertex-connected (2VC) subgraph.

        A 2-connected graph is a 2VC one, except that a---b is 
		considered 2VC but not 2-connected.

    Useful theorems:

        A 2-edge connected (2EC) graph is a graph without bridges. 
		Any 2-connected graph is also 2EC.

        Let G be a graph on at least 2 vertices. The following 
		propositions are equivalent:
            * (i) G is 2-connected;
            * (ii) any two vertices are in a cycle; (a cycle can't 
			       repeat vertices)
            * (iii) any two edges are in a cycle and δ(G) ≥ 2;
            * (iv) for any three vertices x,y et z, there is a 
			       (x,z)-path containing y.
        Let G be a graph on at least 3 vertices. The following 
		propositions are equivalent:
            * (i) G is 2-edge-connected;
            * (ii) any edge is in a cycle;
            * (iii) any two edges are in a tour and δ ≥ 1;
            * (iv) any two vertices are in a tour 
			       (a tour can repeat vertices)

		If G is 2-connected and not bipartite, all vertices belong to 
		some odd cycle. And any two vertices are in a odd cycle (not 
		really proven).

        If G is 2-edge-connected (proof by AC):
            For any two vertices x, y and one edge e, there is a 
			(x, y)-walk containing e without repeating edges.

        A graph admits a strongly connected orientation if and only
		if it is 2EC.
        A strong orientation of a given bridgeless undirected graph 
		may be found in linear time by performing a depth first search 
		of the graph, orienting all edges in the depth first search 
		tree away from the tree root, and orienting all the remaining 
		edges (which must necessarily connect an ancestor and a 
        descendant in the depth first search tree) from the 
		descendant to the ancestor.

	Constraints:
		***undirected*** graph.
		Vertices are labeled from 0 to n (inclusive).
		Graph is connected (but for unconnected just replace single 
		dfs call with a loop).

	Usage:
		Create the struct setting the starting vertex (a), the maximum 
		vertex label (n),
	    the graph adjacency list (graph) and a callback f to apply on 
		the biconnected components.
		Afterwards, art[i] == true if i is an articulation point.
		If the pair {a, i} is on the bridges list, then the edge 
		{a, graph[a][i]} is a bridge.
        The callback must receive a vector of edges {a, b} that are
		in the same biconnected component.
		Remember that for a single vertex, the biconnected callback 
		will not be called.

    Sample Usage:
        auto rdm = apb(1, n, graph, [&](vector<pii> v){
		set<int> s;
		for (int i = 0; i < sz(v); i++)
		{
			s.insert(v[i].first);
			s.insert(v[i].second);
		}

		ans = max(ans, sz(s));
	    });
*/

struct apb
{
vector<int> *graph;
vector<bool> art;
vector<int> num /* dfs order of vertices starting at 1 */, low;
vector<pii> bridges;
vector<pii> st;
int id;

template<class F>
apb(int a, int n, vector<int> graph[], const F &f) : graph(graph), art(n + 1, false), num(n + 1), low(n + 1)
{
	id = 1;
	dfs(a, a, f);
}

template<class F>
void dfs(int a, int p, const F &f)
{
	low[a] = num[a] = id++;
	int comp = 0;

	for (int i = 0; i < sz(graph[a]); i++)
	{
		if (num[graph[a][i]] == 0)
		{
            int si = sz(st);
			comp++;
            st.push_back({a, graph[a][i]}); // Tree edge.

			dfs(graph[a][i], a, f);
			low[a] = min(low[a], low[graph[a][i]]);

			if (low[graph[a][i]] >= num[a])
            {
                if (a != 1)
    				art[a] = true;

                f(vector<pii>(st.begin() + si, st.end()));
                st.resize(si);
            }

			if (low[graph[a][i]] > num[a])
				bridges.push_back({a, i});
		}
		else if (graph[a][i] != p && num[graph[a][i]] < num[a]) 
        {
			// Back edge.
            low[a] = min(low[a], num[graph[a][i]]);
            st.push_back({a, graph[a][i]});
        }
	}

	if (a == p && comp > 1)
		art[a] = true;
}
};

