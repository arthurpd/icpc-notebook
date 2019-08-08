// https://www.spoj.com/problems/SUBMERGE/
#include "../bridges_art_points.cpp"

#define MAXN 1123

vector<int> graph[MAXN];

int main(void)
{
	int n, m, a, b, T;
    scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
        scanf("%d %d", &n, &m);
		for (int i = 0; i<= n; i++)
			graph[i].clear();
		for (int i = 0; i < m; i++)
		{
			scanf("%d %d", &a, &b);
			graph[a].push_back(b);
			graph[b].push_back(a);
		}

		apb rdm(1, n, graph);
        for (int i = 0; i < rdm.bridges.size(); i++)
			rdm.bridges[i] = {min(rdm.bridges[i].first, graph[rdm.bridges[i].first][rdm.bridges[i].second]), max(rdm.bridges[i].first, graph[rdm.bridges[i].first][rdm.bridges[i].second])};

		sort(rdm.bridges.begin(), rdm.bridges.end());
		
		printf("Caso #%d\n", t);
		if (rdm.bridges.size())
		{
			printf("%d\n", (int) rdm.bridges.size());
			for (int i = 0; i < rdm.bridges.size(); i++)
				printf("%d %d\n", rdm.bridges[i].first, rdm.bridges[i].second);
		}
		else
			printf("Sin bloqueos\n");
	}
}
