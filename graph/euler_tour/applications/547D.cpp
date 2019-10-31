//https://codeforces.com/contest/547/problem/D
#include "../../../contest/header.hpp"

namespace euler
{

#define MAXM 212345
#define MAXN 212345

struct edge
{
    int u, v, id;
};

struct vertice
{
    set<int> outs;           // edges indexes
    int in_degree = 0; // not used with undirected graphs
};

int n, m;
edge edges[MAXM];
vertice vertices[2 * MAXN];
set<int>::iterator its[2 * MAXN];
bool used_edge[MAXM];

void init()
{
    for (int i = 0; i < n; i++)
    {
        its[i] = vertices[i].outs.begin();
    }
}

vi euler_tour(int src)
{
    vi ret_edges;
    vector<pii> s = {{src, -1}};
    while (!s.empty())
    {
        int x = s.back().first;
        int e = s.back().second;
        auto &it = its[x], end = vertices[x].outs.end();

        while (it != end && used_edge[*it])
            ++it;

        if (it == end)
        {
            ret_edges.push_back(e);
            s.pop_back();
        }
        else
        {
            auto edge = edges[*it];
            int v = edge.u == x ? edge.v : edge.u;
            s.push_back({v, *it});
            used_edge[*it] = true;
        }
    }

	reverse(all(ret_edges));
	return ret_edges;
	
}

} // namespace euler


int main()
{
    scanf("%d", &euler::m);
    euler::n = 2 * MAXM;
    for (int i = 0; i < euler::m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        y += MAXM;
        euler::edges[i] = {x, y, i};
        euler::vertices[x].outs.insert(i);
        euler::vertices[y].outs.insert(i);
    }

    queue<int> odds;
    for (int i = 0; i < 2 * MAXM; i++)
    {
        if (!euler::vertices[i].outs.empty())
            odds.push(i);
    }
    
    stack<pii> removed_edges;

    while (!odds.empty())
    {
        int u = odds.front();
        odds.pop();
        if ((int)euler::vertices[u].outs.size() & 1)
        {
            int e = *euler::vertices[u].outs.begin();
            removed_edges.push({e, u});
            int x = euler::edges[e].u;
            int y = euler::edges[e].v;
            euler::vertices[x].outs.erase(e);
            euler::vertices[y].outs.erase(e);

            if ((int)euler::vertices[y].outs.size() & 1)
            {
                odds.push(y);
            }

            if ((int)euler::vertices[x].outs.size() & 1)
            {
                odds.push(x);
            }
        }
    }

    vector<char> color(euler::m);
    vi balance(2 * MAXM);
    euler::init();

    for (int i = 0; i < 2 * MAXM; i++)
    {
        if (!euler::vertices[i].outs.empty() && !euler::used_edge[*euler::vertices[i].outs.begin()])
        {
            auto res = euler::euler_tour(i);
            char c = 'r';
            for (int j : res)
            {
                if (j == -1) continue;
                color[j] = c;
                if (c == 'r')
                {
                    balance[euler::edges[j].u]++;
                    balance[euler::edges[j].v]++;
                    c = 'b';
                }
                else
                {
                    balance[euler::edges[j].u]--;
                    balance[euler::edges[j].v]--;
                    c = 'r';
                }
            }
        }
    }

    while(!removed_edges.empty())
    {
        int e, u, v;
        tie(e, u) = removed_edges.top();
        v = euler::edges[e].u == u ? euler::edges[e].v:euler::edges[e].u;
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