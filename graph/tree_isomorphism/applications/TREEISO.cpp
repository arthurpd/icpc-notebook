// https://www.spoj.com/submit/TREEISO/id=24729943

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
#define sz(x) (int)(x.size())
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vii vector<pii>
#define ll long long
#define ull unsigned long long
typedef long double ld;

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
            children_labels.pb(canonical(v, u, graph));
    }

    sort(all(children_labels));
    if (map_labels.count(children_labels) == 0)
        map_labels[children_labels] = label++;
    return map_labels[children_labels];
}

int main()
{
    int t;
    scanf("%d", &t);

    while (t--)
    {
        int n;
        scanf("%d", &n);
        
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
            graph_a[u].pb(v);
            graph_a[v].pb(u);
        }
        for (int i = 0; i < n - 1; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            graph_b[u].pb(v);
            graph_b[v].pb(u);
        }

        pii roots_a = get_roots(graph_a);
        pii cano_a = {canonical(roots_a.fi, 0, graph_a), canonical(roots_a.se, 0, graph_a)};

        pii roots_b = get_roots(graph_b);
        pii cano_b = {canonical(roots_b.fi, 0, graph_b), canonical(roots_b.se, 0, graph_b)};
        
        if (cano_a.fi == cano_b.fi || 
            cano_a.fi == cano_b.se ||
            cano_a.se == cano_b.fi ||
            cano_a.se == cano_b.se)
            printf("YES\n");
        else
            printf("NO\n");
    }
    
}