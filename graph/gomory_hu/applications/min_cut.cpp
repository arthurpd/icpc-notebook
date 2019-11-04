// https://www.urionlinejudge.com.br/judge/pt/problems/view/2082
#include "../gomory_hu.cpp"

int main(void)
{
	int T, n, m, a, b, c;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d %d", &n, &m);
		gomory_hu gh;

		vector<vector<int>> graph(n);
		for (int i = 0; i < n; i++)
			graph[i] = vector<int>(n, 0);

		for (int i = 0; i < m; i++)
		{
			scanf("%d %d %d", &a, &b, &c);
			a--;
			b--;
			graph[a][b] = c;
			graph[b][a] = c;
		}

		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				if (graph[i][j] > 0)
					gh.add_edge(i, j, graph[i][j]);

		ll ans = inf;
		auto edges = gh.solve(n);
		for (int i = 1; i < n; i++)
			ans = min(ans, edges[i].first);

		printf("%lld\n", ans);
	}
}
