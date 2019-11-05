//https://www.urionlinejudge.com.br/judge/pt/problems/view/1229
#include "../../../contest/header.hpp"
 
vector<vi> graph_a, graph_b;
int label;
map<vi, int> map_labels;
 
 
pii get_roots(vector<vi> &graph)
{
    queue<int> q;
    vi vis(sz(graph));
    vi degree(sz(graph));
 
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
 
int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        graph_a.clear();
        graph_a.resize(n + 1);
        graph_b.clear();
        graph_b.resize(n + 1);
        map_labels.clear();
        label = 0;
        for (int i = 0; i < n - 1; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            graph_a[u].push_back(v);
            graph_a[v].push_back(u);
        }
        for (int i = 0; i < n - 1; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            graph_b[u].push_back(v);
            graph_b[v].push_back(u);
        }
 
        pii roots_a = get_roots(graph_a);
        pii cano_a = {canonical(roots_a.first, 0, graph_a), canonical(roots_a.second, 0, graph_a)};
 
        pii roots_b = get_roots(graph_b);
        pii cano_b = {canonical(roots_b.first, 0, graph_b), canonical(roots_b.second, 0, graph_b)};
        
        if (cano_a.first == cano_b.first || 
            cano_a.first == cano_b.second ||
            cano_a.second == cano_b.first ||
            cano_a.second == cano_b.second)
            printf("S\n");
        else
            printf("N\n");
    }
    
} 