// https://codeforces.com/gym/101492/problem/G

#include "../biconnected_components.cpp"

#define MAXN 51234
vector<int> graph[MAXN];

int main(void)
{
	int n, m, a, b;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	int ans = 0;
	auto rdm = apb(1, n, graph, [&](vector<pii> v){
		set<int> s;
		for (int i = 0; i < sz(v); i++)
		{
			s.insert(v[i].first);
			s.insert(v[i].second);
		}

		ans = max(ans, sz(s));
	});

	cout << ans << endl;
}

