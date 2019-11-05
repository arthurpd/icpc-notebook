// http://www.spoj.com/problems/FASTFLOW/

#include "../dinic.cpp"

int main(void)
{
    int a, b, c, n, m;
    cin >> n >> m;

    dinic::init(n, 1, n);
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        dinic::put_edge_undirected(a, b, c);
    }

    cout << dinic::max_flow() << endl;
}
