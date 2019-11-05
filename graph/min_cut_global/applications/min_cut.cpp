#include "../min_cut.cpp"

int main(void)
{
	int T, n, m, a, b, c;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d %d", &n, &m);
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

		printf("%d\n", mincut(n, graph).first);
	}
}
