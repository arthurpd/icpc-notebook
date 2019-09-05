// https://www.urionlinejudge.com.br/judge/pt/problems/view/2199

#include "../biconnected_components.cpp"

#define MAXN 51234
vector<int> graph[MAXN];

int main(void)
{
	int m, n, a, b, T = 0;
	while(scanf("%d", &m) && m != 0)
	{
		n = 0;
		for (int i = 0; i <= m + 1; i++)
			graph[i].clear();
		
		for (int i = 0; i < m; i++)
		{
			scanf("%d %d", &a, &b);
			graph[a].push_back(b);
			graph[b].push_back(a);
			n = max(a, n);
			n = max(b, n);
		}

		vector<vector<int>> bcc;
		apb sol(1, n, graph, [&](vector<pii> v){
			set<int> s;
			for (int i = 0; i < sz(v); i++)
			{
				s.insert(v[i].first);
				s.insert(v[i].second);
			}

			bcc.push_back(vector<int>(s.begin(), s.end()));
		});

		printf("Case %d: ", ++T);
		if (bcc.size() == 1)
			printf("2 %lld\n", n*1ll*(n-1)/2);
		else
		{
			int ans1 = 0;
			long long ans2 = 1;
			for (int i = 0; i < sz(bcc); i++)
			{
				int cnt = 0;
				for (int v : bcc[i])
					if (sol.art[v])
						cnt++;
				if (cnt == 1)
				{
					ans1++;
					ans2 *= (sz(bcc[i]) - 1);
				}
			}

			printf("%d %lld\n", ans1, ans2);
		}
	}
}
