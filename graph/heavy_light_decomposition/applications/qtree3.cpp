// https://www.spoj.com/problems/QTREE3/
#include "../hld_dadalto.cpp"

struct data_s
{
	set<pii> s;

	data_s(int n) {}

	int get(int a, int b)
	{
		auto it = s.lower_bound(pii(a, -1));
		if (it != s.end() && it->first <= b)
		{
			return it->second;
		}
		else
			return -1;
	}

	void update(int a, int x)
	{
		if (x > 0)
			s.insert(pii(a, x));
		else
			s.erase(pii(a, -x));
	}
};

struct edge
{
	int a, b, c;
};

int main(void)
{
	int n, q, a, b;
	scanf("%d %d", &n, &q);
	vector<vector<int>> graph(n + 1);
	vector<int> v(n + 1, -1);
	for (int i = 0; i < n - 1; i++)
	{
		scanf("%d %d", &a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	heavy_light<data_s, true> hld(1, n, graph);

	for (int i = 0; i < q; i++)
	{
		int x, y;
		scanf("%d %d", &x, &y);
		if (x == 1)
			printf("%d\n", hld.query_path(1, y, -1, [](int a, int b) { return (b == -1) ? a : b; }));
		else
		{
			v[y] *= -1;
			hld.update(y, v[y] * y);
		}
	}
}
