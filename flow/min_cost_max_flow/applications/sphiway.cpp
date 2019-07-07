// https://www.spoj.com/problems/SPHIWAY/

#include "../min_cost_max_flow.cpp"
#include <bits/stdc++.h>
using namespace std;

int main(void)
{
	int n, m, s, t, a, b, c;
	scanf("%d %d %d %d", &n, &m, &s, &t);

	mcmf::init(n, 0, t);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &a, &b, &c);
		mcmf::put_edge(a, b, 1, c);
		mcmf::put_edge(b, a, 1, c);
	}

	mcmf::put_edge(0, s, 2, 0);

	pll ans = mcmf::mincost_maxflow();
	if (ans.first == 2)
		printf("%lld\n", ans.second);
	else
		printf("-1\n");
}
