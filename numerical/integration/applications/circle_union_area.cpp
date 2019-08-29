// https://www.spoj.com/problems/VCIRCLES/

#include "../../../geometry/2d/2d.cpp"
#include "../simpson.cpp"

#define point point<double>
#define circle circle<double>
#define MAXN 1123

circle c[MAXN];

int main(void)
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lf %lf %lf", &c[i].center.x, &c[i].center.y, &c[i].r);

	set<double> inx;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			pair<point, point> intersections;
			if (!(c[i].center == c[j].center) && c[i].intersect(c[j], intersections) > 0)
			{
				inx.insert(intersections.first.x);
				inx.insert(intersections.second.x);
			}
		}

		inx.insert(c[i].center.x + c[i].r);
		inx.insert(c[i].center.x - c[i].r);
	}

	vector<double> good_x(inx.begin(), inx.end());

	double ans = 0;
	int total = 500000;
	double range_x = good_x.back() - good_x[0]; 
	vector<pair<double, pair<int,int>>> v;
	for (int i = 0; i + 1 < good_x.size(); i++)
	{
		v.clear();
		for (int j = 0; j < n; j++)
		{
			double d = abs((good_x[i] + good_x[i+1])/2 - c[j].center.x);
			if (d + EPS < c[j].r)
			{
				double h = sqrt(c[j].r * c[j].r - d * d);
				v.push_back({c[j].center.y - h, {j, 1}});
				v.push_back({c[j].center.y + h, {j, -1}});
			}
		}
		sort(v.begin(), v.end());

		ans += simpsons([&](double x) {

			double prev = -1e9;
			double retv = 0;
			int open = 0;
			for (int j = 0; j < v.size(); j++)
			{
				double d = abs(x - c[v[j].second.first].center.x);
				double h = sqrt(c[v[j].second.first].r * c[v[j].second.first].r - d * d);
				double tmp = c[v[j].second.first].center.y - v[j].second.second * h;

				retv += (tmp - prev) * (open ? 1 : 0);
				open += v[j].second.second;
				assert(tmp + EPS >= prev);
				prev = tmp;
			}

			return retv;
		},
						2*max(1, int(((good_x[i+1] - good_x[i]) / range_x) * total)) , good_x[i], good_x[i+1]);
	}

	printf("%.5lf\n", ans);
}
