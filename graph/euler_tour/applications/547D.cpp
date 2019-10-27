//https://codeforces.com/contest/547/problem/D
#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define db(x) //cerr << #x << " = " << x << endl;
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

#define MAXM 212345

struct Edge {
	int u, v, id;
};

struct Vertice {
	set<int> outs;  // edges indexes
};

int n, m;
Edge edges[MAXM];
Vertice vertices[2 * MAXM];
set<int>::iterator its[2 * MAXM];
bool used_edge[MAXM];

void init()
{
	for (int i = 0; i < n; i++)
	{
		its[i] = vertices[i].outs.begin();
	}
}

// Undirected version
int find_src()
{
	int src = 0;
	for (int i = 0; i < n; i++)
	{
		if (sz(vertices[i].outs) & 1)
		{
			src = i;
			break;
		}
		if (sz(vertices[i].outs))
			src = i;
	}
	
	return src;
}

// Undirected version
bool check_condition()
{
	int c = 0;
    for (int i = 0; i < n; ++i)
	    c += (sz(vertices[i].outs) & 1);
	return (c == 2 || c == 0);
}

vi euler_tour(int n_edges, int src = -1) {
	
    if (!check_condition())
		return {};

    if (src == -1)
    {
        src = find_src();
    }
    
	vi ret_edges;
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
			ret_edges.push_back(e);
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
	// Check if is cycle ret_vertices.front() == ret_vertices.back()

	reverse(all(ret_edges));
	return ret_edges;
}

int main()
{
    scanf("%d", &m);
    n = 2 * MAXM;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        y += MAXM;
        edges[i] = {x, y, i};
        vertices[x].outs.insert(i);
        vertices[y].outs.insert(i);
    }

    queue<int> odds;
    for (int i = 0; i < 2 * MAXM; i++)
    {
        if (!vertices[i].outs.empty())
            odds.push(i);
    }
    
    stack<pii> removed_edges;

    while (!odds.empty())
    {
        int u = odds.front();
        odds.pop();
        if ((int)vertices[u].outs.size() & 1)
        {
            int e = *vertices[u].outs.begin();
            removed_edges.push({e, u});
            int x = edges[e].u;
            int y = edges[e].v;
            vertices[x].outs.erase(e);
            vertices[y].outs.erase(e);

            if ((int)vertices[y].outs.size() & 1)
            {
                odds.push(y);
            }

            if ((int)vertices[x].outs.size() & 1)
            {
                odds.push(x);
            }
        }
    }

    vector<char> color(m);
    vi balance(2 * MAXM);
    init();

    for (int i = 0; i < 2 * MAXM; i++)
    {
        if (!vertices[i].outs.empty() && !used_edge[*vertices[i].outs.begin()])
        {
            auto res = euler_tour(i);
            char c = 'r';
            for (int j : res)
            {
                db(j);
                if (j == -1) continue;
                color[j] = c;
                if (c == 'r')
                {
                    balance[edges[j].u]++;
                    balance[edges[j].v]++;
                    c = 'b';
                }
                else
                {
                    balance[edges[j].u]--;
                    balance[edges[j].v]--;
                    c = 'r';
                }
            }
        }
    }

    while(!removed_edges.empty())
    {
        int e, u, v;
        tie(e, u) = removed_edges.top();
        v = edges[e].u == u ? edges[e].v:edges[e].u;
        removed_edges.pop();

        if (balance[v] > 0)
        {
            color[e] = 'b';
            balance[u]--;
            balance[v]--;
        }
        else
        {
            color[e] = 'r';
            balance[u]++;
            balance[v]++;
        }
    }

    for(char c : color)
        printf("%c", c);
    printf("\n");

}