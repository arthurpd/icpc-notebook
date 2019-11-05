// https://codeforces.com/contest/723/problem/E
#include "../eulertour.cpp"

int vis[MAXM];

int dfs(int u)
{
    int res = 0;
    for (int e : euler::vertices[u].outs)
    {
        if (!vis[e])
        {
            vis[e] = 1;
            int v = u == euler::edges[e].u ? euler::edges[e].v : euler::edges[e].u;
            res += dfs(v) + 1;
        }
    }
    return res;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &euler::n, &euler::m);
        for (int i = 0; i < euler::m; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            --u, --v;
            euler::edges[i].u = u;
            euler::edges[i].v = v;
            euler::edges[i].id = i;

            euler::vertices[u].outs.push_back(i);
            euler::vertices[v].outs.push_back(i);
        }

        vi odds;
        int evens = 0;
        for (int i = 0; i < euler::n; i++)
        {
            if (sz(euler::vertices[i].outs) & 1)
                odds.push_back(i);
            else
                ++evens;
        }

        set<pii> created_edges;
        for (int i = 0; i < sz(odds); i += 2)
        {
            int u = odds[i];
            int v = odds[i + 1];
            euler::edges[i + euler::m].u = u;
            euler::edges[i + euler::m].v = v;
            euler::edges[i + euler::m].id = i + euler::m;
            euler::vertices[u].outs.push_back(i + euler::m);
            euler::vertices[v].outs.push_back(i + euler::m);

            created_edges.insert({min(u, v), max(u, v)});
        }

        euler::init();
        printf("%d\n", evens);
        for (int i = 0; i < euler::n; i++)
        {
            if (!euler::vertices[i].outs.empty() && 
                !euler::used_edge[euler::vertices[i].outs.back()])
            {
                int n_edges = dfs(i);
                auto tour = euler::euler_tour(n_edges, i);
                for (int j = 0; j < sz(tour) - 1; ++j)
                {
                    int u = tour[j];
                    int v = tour[j + 1];
                    auto it = created_edges.find({min(u, v), max(u, v)});
                    if (it == created_edges.end())
                    {
                        printf("%d %d\n", u + 1, v + 1);
                    }
                    else
                        created_edges.erase(it);
                }
            }
        }
        
        for (int i = 0; i < euler::n; i++)
        {
            euler::vertices[i].outs.clear();
        }

        for (int i = 0; i < euler::m + sz(odds); i++)
        {
            euler::used_edge[i] = 0;
            vis[i] = 0;
        }
    }
    
}