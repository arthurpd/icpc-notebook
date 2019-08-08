// https://www.spoj.com/problems/SUBMERGE/
#include "../bridges_art_points.cpp"

#define MAXN 112345

vector<int> graph[MAXN];

int main(void)
{
	int n, m, a, b;
	while (scanf("%d %d", &n, &m) && n)
	{
		for (int i = 0; i<= n; i++)
			graph[i].clear();
		for (int i = 0; i < m; i++)
		{
			scanf("%d %d", &a, &b);
			graph[a].push_back(b);
			graph[b].push_back(a);
		}

		apb rdm(1, n, graph);
		printf("%d\n", (int) count(rdm.art.begin(), rdm.art.end(), true));
	}
}
