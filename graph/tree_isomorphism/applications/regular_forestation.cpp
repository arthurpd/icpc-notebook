// https://codeforces.com/contest/1252/problem/F
#include "../../../contest/header.hpp"
 
#define MAXN 4123

int n;
vector<int> graph[MAXN];
vector<int> sub_size[MAXN];
bool block[MAXN];
int chosen_vertice = -1;
int degree[MAXN];
int id_label = 1;
int vis[MAXN];
map<vector<int>, int> map_label;
vector<vi> centroids;
 
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
 
void put_edge(int a, int b)
{
	degree[a]++;
	graph[a].push_back(b);
	sub_size[a].push_back(0);
	degree[b]++;
	graph[b].push_back(a);
	sub_size[b].push_back(0);
}
 
int canonical(int u, int p = 0)
{
    vi sub_labels;
    for (int v : graph[u])
        if (v != p)
        {
            sub_labels.push_back(canonical(v, u));
        }
 
    sort(all(sub_labels));
    if (!map_label.count(sub_labels))
        map_label[sub_labels] = id_label++;
    return map_label[sub_labels];
}
 
 
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n - 1; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		put_edge(u, v);
	}
 
    int val = inf;
    dfs_centroid(1, 1, n, chosen_vertice, val);
 
	if (chosen_vertice == -1)
		return !printf("-1\n");
 
    for (int v : graph[chosen_vertice])
    {
        --degree[v];
        for (int j = 0; j < sz(graph[v]); j++)
        {
            if (graph[v][j] == chosen_vertice)
            {
                graph[v].erase(graph[v].begin() + j);
                sub_size[v].erase(sub_size[v].begin() + j);
                break;
            }
        }
    }
    
    vector<int> roots_one;
    vector<pii> roots_two;
 
    queue<int> q;
	for (int i = 1; i <= n; i++)
	{
		if (degree[i] == 1)
		{
			q.push(i);
		}
        if (degree[i] == 0)
            roots_one.push_back(i);
	}
 
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
 
        if (vis[u]) continue;
        vis[u] = 1;
 
        for (int k : graph[u])
            if (degree[k] == 1)
            {
                roots_two.push_back({u, k});
                vis[k] = 1;
                break;
            }
 
        bool last = true;
		for (int v : graph[u])
		{
			if (degree[v] && v != chosen_vertice)
			{
                last = false;
				degree[v]--;
                degree[u]--;
 
				if (degree[v] == 1)
				{
					q.push(v);
				}
			}
		}
 
        if (last)
        {
            roots_one.push_back(u);
        }
	}
 
    if (!roots_one.empty() && sz(roots_one) != sz(graph[chosen_vertice]))
        return !printf("-1\n");
 
    if (!roots_two.empty() && sz(roots_two) != sz(graph[chosen_vertice]))
        return !printf("-1\n");
 
    centroids.resize(sz(graph[chosen_vertice]));
    if (!roots_one.empty())
    {
        for (int i = 0; i < sz(centroids); i++)
        {
            centroids[i].push_back(roots_one[i]);
        }
    }
    if (!roots_two.empty())
    {
        for (int i = 0; i < sz(centroids); i++)
        {
            centroids[i].push_back(roots_two[i].first);
            centroids[i].push_back(roots_two[i].second);
        }
    }
 
    int target1 = canonical(centroids[0][0]), target2 = canonical(centroids[0].back());
    bool poss = true;
    for (int i = 1; i < sz(graph[chosen_vertice]); i++)
    {
        if (canonical(centroids[i][0]) != target1 && canonical(centroids[i].back()) != target1)
        {
            poss = false;
            break;
        }
    }
    
    if (poss)
        return !printf("%d\n", sz(graph[chosen_vertice]));
 
    poss = true;
 
    for (int i = 1; i < sz(graph[chosen_vertice]); i++)
    {
        if (canonical(centroids[i][0]) != target2 && canonical(centroids[i].back()) != target2)
        {
            poss = false;
            break;
        }
    }
 
    if (poss)
        return !printf("%d\n", sz(graph[chosen_vertice]));
 
    printf("-1\n");
}