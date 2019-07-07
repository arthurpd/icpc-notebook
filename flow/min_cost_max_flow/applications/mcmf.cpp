// https://open.kattis.com/problems/mincostmaxflow

#include "../min_cost_max_flow.cpp"
#include <bits/stdc++.h>
using namespace std;

int main(void)
{
	int n, m, s, t, a, b, c, w;
	scanf("%d %d %d %d", &n, &m, &s, &t);

	mcmf::init(n, s, t);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d %d", &a, &b, &c, &w);
		mcmf::put_edge(a, b, c, w);
	}

	pll ans = mcmf::mincost_maxflow();
	cout << ans.first << " " << ans.second << endl;
}
