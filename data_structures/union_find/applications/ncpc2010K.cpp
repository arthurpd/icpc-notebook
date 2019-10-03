// https://codeforces.com/gym/101556
#include "../union_find.cpp"
#include "../../../geometry/2d/2d.cpp"

#define point point<double>

ostream &operator<<(ostream &os, point p)
{
	return os << "(" << p.x << ", " << p.y << ")";
}

int main(void)
{
	int n, m, a, b;
	scanf("%d %d", &n, &m);
	vector<point> p(n);
	vector<vector<pii>> graph(n);
	for (int i = 0; i < n; i++)
		scanf("%lf %lf", &p[i].x, &p[i].y);

	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &a, &b);
		graph[a].push_back({b, i});
		graph[b].push_back({a, i});
	}

	union_find dsu(m);
	vector<double> diff(n);
	double ans = 0;
	for (int i = 0; i < n; i++)
	{
		if (graph[i].size() == 2)
		{
			ans += acos(-1) - abs((p[graph[i][0].first] - p[i]).angle(p[graph[i][1].first] - p[i]));
			diff[i] = 0;
			dsu.join(graph[i][0].second, graph[i][1].second);
		}
		else
		{
			vector<pair<double, int>> vals;
			for (int j = 1; j < 4; j++)
			{
				int k, l;
				if (3 + j == 6)
					k = 1, l = 2;
				else if (4 + j == 6)
					k = 1, l = 3;
				else
					k = 2, l = 3;

				double d1 = acos(-1) - abs((p[graph[i][0].first] - p[i]).angle(p[graph[i][j].first] - p[i]));
				double d2 = acos(-1) - abs((p[graph[i][k].first] - p[i]).angle(p[graph[i][l].first] - p[i]));

				vals.push_back({d1 + d2, j});
			}

			sort(vals.begin(), vals.end());
			diff[i] = vals[1].first - vals[0].first;
			ans += vals[0].first;

			for (int j = vals[0].second; j < 4; j = 4)
			{
				int k, l;
				if (3 + j == 6)
					k = 1, l = 2;
				else if (4 + j == 6)
					k = 1, l = 3;
				else
					k = 2, l = 3;

				dsu.join(graph[i][0].second, graph[i][j].second);
				dsu.join(graph[i][k].second, graph[i][l].second);
			}
		}
	}

	vector<pair<double, int>> pi;
	for (int i = 0; i < n; i++)
		pi.push_back({diff[i], i});
	sort(pi.begin(), pi.end());

	for (int i = 0; i < n; i++)
	{
		a = pi[i].second;
		for (int j = 0; j < sz(graph[a]); j++)
			for (int k = j + 1; k < sz(graph[a]); k++)
			{
				if (dsu.find(graph[a][j].second) != dsu.find(graph[a][k].second))
				{
					ans += diff[a];
					dsu.join(graph[a][j].second, graph[a][k].second);
				}
			}
	}

	printf("%.20lf\n", ans);
}
