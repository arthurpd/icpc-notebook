#include <bits/stdc++.h>
 
using namespace std;
#define pb push_back
#define db(x) cerr << #x << " = " << x << endl;
#define INF 0x3f3f3f3f3f3f3f3f
#define fi first
#define se second
#define vi vector<int>
#define vll vector<ll>
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vii vector<pii>
#define ll long long
#define ull unsigned long long
typedef long double ld;
 
#define sz(x) x.size()
 
char aux[1123];
 
#define MAXN 30
#define MAXM 112345
 
struct Edge {
	int u, v, id;
};
 
struct Vertice {
	vi outs;  // edges indexes
	int in_degree = 0; // not used with undirected graphs
};
 
int n, m;
Edge edges[MAXM];
Vertice vertices[MAXN];
vi::iterator its[MAXN];
bool used_edge[MAXM];
 
void init()
{
	for (int i = 0; i < n; i++)
	{
		its[i] = vertices[i].outs.begin();
	}
}
 
// Directed version
int find_src()
{
	int src = 0;
	for (int i = 0; i < n; i++)
	{
		if ((int)sz(vertices[i].outs) > vertices[i].in_degree)
		{
			src = i;
			break;
		}
		if (vertices[i].in_degree)
			src = i;
	}
 
	return src;
}
 
// Directed version
bool check_condition()
{
	int c = 0;
	for (int i = 0; i < n; ++i)
	    c += abs(vertices[i].in_degree - (int)sz(vertices[i].outs));
	return c <= 2;
}
 
vi euler_tour(int n_edges, int src = -1) {
	
    if (!check_condition())
		return {};
 
    if (src == -1)
    {
        src = find_src();
    }
    
	vi ret_vertices;
	//vi ret_edges;
	vii s = {{src, -1}};
	while(!s.empty()) 
    {
		int x = s.back().fi;
		int e = s.back().se;
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
	return ret_vertices;
	*/
}
 
void reset()
{
    for (int i = 0; i < n; i++)
    {
        vertices[i].outs.clear();
        vertices[i].in_degree = 0;
    }
    for (int i = 0; i < m; i++)
    {
        used_edge[i] = false;
    }
    
}
 
int main()
{
    int t;
    scanf("%d", &t);
    n = 26;
    while (t--)
    {
        scanf("%d", &m);
        for (int i = 0; i < m; i++)
        {
            scanf("%s", aux);
            string str = aux;
            int u = str[0] - 'a';
            int v = str.back() - 'a';
            edges[i] = {u, v, i};
            vertices[u].outs.pb(i);
            vertices[v].in_degree++;
        }
 
        init();
        if (euler_tour(m).empty())
        {
            printf("The door cannot be opened.\n");
        }
        else
        {
            printf("Ordering is possible.\n");
        }
        
        reset();
    }
    
} 