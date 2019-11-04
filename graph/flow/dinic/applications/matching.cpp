// http://www.spoj.com/problems/MATCHING/

#include "../dinic.cpp"

int main(void)
{
    int a, b, l, r, m;
    scanf("%d %d %d", &l, &r, &m);

    dinic::init(l + r + 2, l + r, l + r + 1);

    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &a, &b);
        a--, b--;
        dinic::put_edge(a, b + l, 1);
    }

    for (int i = 0; i < l; i++)
        dinic::put_edge(l + r, i, 1);
    for (int i = l; i < l + r; i++)
        dinic::put_edge(i, l + r + 1, 1);

    cout << dinic::max_flow() << endl;
}
