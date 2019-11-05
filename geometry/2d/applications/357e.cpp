// https://codeforces.com/problemset/problem/681/E
#include "../2d.cpp"

#define point point<double>
#define segment segment<double>
#define circle circle<double>
#define MAXN 112345

#define M_PI 3.14159265358979323846

circle c[MAXN];

int main(void)
{
	point p0;
	double v, t;
	int n;
	cin >> p0.x >> p0.y >> v >> t >> n;
	for (int i = 0; i < n; i++)
	{
		scanf("%lf %lf %lf", &c[i].center.x, &c[i].center.y, &c[i].r);
		c[i].center = c[i].center - p0;
		if (c[i].center.dist() < c[i].r + EPS)
		{
			printf("1\n");
			return 0;
		}
	}

	p0 = p0 - p0;
	circle safe = {p0, v * t};
	vector<pair<double, double>> arcs;
	for (int i = 0; i < n; i++)
	{
		if (c[i].center.dist() < c[i].r + safe.r - EPS)
		{
			pair<point, point> sf;
			sf = c[i].tangents(p0);
			if (sf.first.dist() > safe.r + EPS)
			{
				if (c[i].intersect(safe, sf) <= 0)
				{
					debug(safe.center, safe.r);
					debug(sf);
					debug(c[i].center, c[i].r);
					assert(false);
				}
			}

			pair<double, double> tmp = {sf.first.angle(), sf.second.angle()};

			if (tmp.first > tmp.second)
				swap(tmp.first, tmp.second);

			if (tmp.second - tmp.first < M_PI)
				arcs.push_back(tmp);
			else
			{
				arcs.push_back({-M_PI, tmp.first});
				arcs.push_back({tmp.second, M_PI});
			}
		}
	}

	double ans = 0;
	sort(arcs.begin(), arcs.end());
	for (int i = 0; i < arcs.size(); i++)
	{
		double l = arcs[i].first;
		double r = arcs[i].second;
		while (i + 1 < arcs.size() && arcs[i + 1].first <= r)
			r = max(r, arcs[++i].second);

		ans += r - l;
	}

	printf("%.15lf\n", ans / (2 * M_PI));
}
