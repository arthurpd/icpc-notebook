// https://www.spoj.com/problems/QTREE/
#include "../hld_dadalto.cpp"
#include "../../../data_structures/segment_tree/seg.cpp"

struct edge
{
	int a, b, c;
};

int main(void)
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		int n;
		scanf("%d", &n);
		vector<vector<int>> graph(n + 1);
		vector<edge> e(n - 1);
		for (int i = 0; i < n - 1; i++)
		{
			scanf("%d %d %d", &e[i].a, &e[i].b, &e[i].c);
			graph[e[i].a].push_back(e[i].b);
			graph[e[i].b].push_back(e[i].a);
		}

		heavy_light<segtree, false> hld(1, n, graph);
		for (int i = 0; i < n - 1; i++)
		{
			if (hld.h[e[i].a] > hld.h[e[i].b])
				hld.update(e[i].a, e[i].c);
			else
				hld.update(e[i].b, e[i].c);
		}

		char s[10];
		while (scanf("%s", s) && s[0] != 'D')
		{
			int x, y;
			scanf("%d %d", &x, &y);
			if (s[0] == 'Q')
				printf("%d\n", hld.query_path(x, y, 0, [](int a, int b) { return max(a, b); }));
			else
			{
				int i = x - 1;
				e[i].c = y;

				if (hld.h[e[i].a] > hld.h[e[i].b])
					hld.update(e[i].a, e[i].c);
				else
					hld.update(e[i].b, e[i].c);
			}
		}
	}
}
