// https://codeforces.com/gym/102007/attachments Problem I.

#include "../dinic.cpp"

#define MAXN 212345

int p[MAXN];
vector<int> graph[MAXN];
vector<int> cost[MAXN];

int sh[12];
int sh_cap[12];
long long dist[12][MAXN];

typedef pair<long long, int> pli;

void dijkstra(int n, int a, long long d[])
{
    memset(d, 0x3f, sizeof(long long) * (n + 1));

    priority_queue<pli> q;
    q.push(pli(0, a));
    d[a] = 0;
    while (!q.empty())
    {
        a = q.top().second;
        long long tmp = q.top().first;
        q.pop();
        if (-tmp != d[a])
            continue;

        for (int i = 0; i < (int)graph[a].size(); i++)
        {
            if (d[graph[a][i]] > d[a] + cost[a][i])
            {
                d[graph[a][i]] = d[a] + cost[a][i];
                q.push(pli(-d[graph[a][i]], graph[a][i]));
            }
        }
    }
}

long long foo(int n, int s, long long mid)
{
    dinic::init(n + s + 1, 0, n + s + 1);

    for (int i = 1; i <= n; i++)
        dinic::put_edge(0, i, p[i]);

    for (int i = 1; i <= n; i++)
        for (int j = 0; j < s; j++)
            if (dist[j][i] <= mid)
                dinic::put_edge(i, n + j + 1, inf);

    for (int i = 0; i < s; i++)
        dinic::put_edge(n + i + 1, n + s + 1, sh_cap[i]);

    return dinic::max_flow();
}

int main(void)
{
    int n, m, s, u, v, w;
    cin >> n >> m >> s;
    long long total_pop = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
        total_pop += p[i];
    }

    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        graph[u].push_back(v);
        cost[u].push_back(w);
        graph[v].push_back(u);
        cost[v].push_back(w);
    }

    for (int i = 0; i < s; i++)
    {
        scanf("%d %d", &sh[i], &sh_cap[i]);
        dijkstra(n, sh[i], dist[i]);
    }

    long long bot = 0, top = 1e16;
    while (bot < top)
    {
        long long mid = (bot + top) / 2;

        if (foo(n, s, mid) == total_pop)
        {
            top = mid;
        }
        else
        {
            bot = mid + 1;
        }
    }

    cout << bot << endl;
}
