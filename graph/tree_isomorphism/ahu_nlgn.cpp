#include "../../contest/header.hpp"
/*
    [DEFINITION]
        AHU-Algorithm to check if trees are isomorphic.

    [COMPLEXITY] 
        O(NlgN) // Map of strings argument + comparison-based sort

    [USAGE]
        Call get_roots function to retrieve the pairs of centers for 
        each tree (if the tree has just one center the pair will show 
        it twice).
        Call canonical function for each tree beginning from each 
        possible center (two at most).
        A tree is isomorphic to another iff they share one canonical 
        value.

    [RESET]
        If the problem has several test cases, don't forget to reset 
        the global vars 'label' and 'map_labels'
*/
 
int label;
map<vector<int>, int> map_labels;
 
pii get_roots(vector<vector<int>> &graph)
{
    queue<int> q;
    vector<int> vis(sz(graph));
    vector<int> degree(sz(graph));
 
    for (int i = 0; i < sz(graph); i++)
    {
        if (sz(graph[i]) == 1)
            q.push(i);
        degree[i] = sz(graph[i]);
    }
 
    int last = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
 
        if (vis[u]) continue;
        vis[u] = 1;
 
        last = u;
 
        for (int v : graph[u])
        {
            if (degree[v] == 1)
            {
                return {u, v};
            }
            if (!vis[v])
            {
                degree[u]--;
                degree[v]--;
 
                if (degree[v] == 1)
                    q.push(v);
            }
        }
            
    }
 
    return {last, last};
}
 
int canonical(int u, int p, vector<vi> &graph)
{
    vi children_labels;
    for (int v : graph[u])
    {
        if (v != p)
            children_labels.push_back(canonical(v, u, graph));
    }
 
    sort(all(children_labels));
    if (map_labels.count(children_labels) == 0)
        map_labels[children_labels] = label++;
    return map_labels[children_labels];
}