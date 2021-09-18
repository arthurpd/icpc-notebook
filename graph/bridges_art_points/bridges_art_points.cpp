#include "../../contest/header.hpp"
/*
        Finding bridges and articulation points in O(V + E):
                A bridge is an edge whose removal splits the graph in two
                connected components.
                An articulation point is a vertex whose removal splits the
                graph in two connected components.
                This can also be adapted to generate the biconnected
                components of a graph, since the articulation points split
                components.


        Constraints:
                ***undirected*** graph.
                Vertices are labeled from 0 to n (inclusive).
                Graph is connected (otherwise it doesn't make sense).

        Usage:
                Create the struct setting the starting vertex (a), the
   maximum vertex label (n) and the graph adjacency list (graph).
                Aftewards, art[i] == true if i is an articulation point.
                If the pair {a, i} is on the bridges list, then the edge
                {a, graph[a][i]} is a bridge.
*/
struct apb {
  vector<int> *graph;
  vector<bool> art;
  vector<int> num /* dfs order of vertices starting at 1 */, low;
  vector<pii> bridges;
  int id;
  apb(int a, int n, vector<int> graph[])
      : graph(graph), art(n + 1, false), num(n + 1), low(n + 1) {
    id = 1;
    dfs(a, a);
  }
  void dfs(int a, int p) {
    low[a] = num[a] = id++;
    int comp = 0;
    for (int i = 0; i < graph[a].size(); i++) {
      if (num[graph[a][i]] == 0) {
        comp++;
        dfs(graph[a][i], a);
        low[a] = min(low[a], low[graph[a][i]]);
        if (a != 1 && low[graph[a][i]] >= num[a]) art[a] = true;
        if (low[graph[a][i]] > num[a]) bridges.push_back({a, i});
      } else if (graph[a][i] != p && num[graph[a][i]] < low[a])
        low[a] = num[graph[a][i]];
    }
    if (a == p && comp > 1) art[a] = true;
  }
};
