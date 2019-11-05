// https://codeforces.com/gym/101158/

#include "../../misc/ternary_search/ternary_search_continuous.cpp"
#include "../2d/2d.cpp"

#define point point<double>
#define line line<double>
#define circle circle<double>
#define segment segment<double>

// Returns the intersection area between a convex polygon and a
// circle.
// Only works if circle center is inside the polygon and
// the points in p are given in counter-clockwise order.
// Has some precision issues, so EPS value is very relevant.
double circle_convex_polygon_intersection(const vector<point> &p, circle c)
{
	double retv = 0;
	int n = sz(p);
	for (int i = 0; i < n; i++)
	{
		line l(p[i], p[(i + 1) % n]);
		segment s(p[i], p[(i + 1) % n]);
		pair<point,point> res;
		
		vector<point> bd; // Boundary points (either in segment or
						  // segment-circle intersection).
		bd.push_back(p[i]);
		bd.push_back(p[(i + 1) % n]);

		if (c.intersect(l, res) == 2)
		{
			if (s.dist(res.first) < EPS)
				bd.push_back(res.first);
			if (s.dist(res.second) < EPS)
				bd.push_back(res.second);
		}

		sort(bd.begin() + 1, bd.end(), [&bd] (point lhs, point rhs) { return (lhs-bd[0]).dist2() < (rhs-bd[0]).dist2(); });
		
		if (bd.size() == 2)
		{
			if ((bd[0] - c.center).dist() < c.r + EPS && (bd[1] - c.center).dist() < c.r + EPS) // Segment completely inside.
				retv += c.center.cross(bd[0], bd[1]) / 2;
			else // Segment completely outside.
				retv += c.r * c.r * (bd[0] - c.center).angle(bd[1] - c.center) / 2;
		}
		else if (bd.size() == 3) // One point inside circle and one
							     // outside.
		{
			if ((bd[0] - c.center).dist() < c.r + EPS) 
			{
				// Point 0 is inside.
				retv += c.center.cross(bd[0], bd[1]) / 2;
				retv += c.r * c.r * (bd[1] - c.center).angle(bd[2] - c.center) / 2;
			}
			else 
			{
				// Point 2 is inside
				retv += c.center.cross(bd[1], bd[2]) / 2;
				retv += c.r * c.r * (bd[0] - c.center).angle(bd[1] - c.center) / 2;
			}
		}
		else
		{
			retv += c.r * c.r * (bd[0] - c.center).angle(bd[1] - c.center) / 2;
			retv += c.center.cross(bd[1], bd[2]) / 2;
			retv += c.r * c.r * (bd[2] - c.center).angle(bd[3] - c.center) / 2;
		}
	}

	return retv;
}

// This finds the maximum intersection between convex polygon and 
// any circle of a given radius.
// Has some precision issues, review before using.
double max_circle_intersection(const vector<point> &p, double r)
{
	circle retv;
	retv.r = r;

	auto f1 = [&](double x) {
		auto f2 = [&](double y) {
			return -circle_convex_polygon_intersection(p, {point(x, y), r});
		};

		double bot = 1e18;
		double top = -1e18;
		for (int i = 0; i < sz(p); i++)
		{
			segment s1(p[i], p[(i + 1) % sz(p)]);
			segment s2(point(x, -1e3), point(x, 1e3));

			auto inter = s2.intersect(s1);
			if (inter.size() > 0)
			{
				for (point a : inter)
				{
					bot = min(bot, a.y);
					top = max(top, a.y);
				}
			}
		}

		retv.center.y = ternary_search(f2, bot, top, EPS);
		return f2(retv.center.y);
	};

	double botx = 1e18;
	double topx = -1e18;
	for (int i = 0; i < sz(p); i++)
	{
		botx = min(botx, p[i].x);
		topx = max(topx, p[i].x);
	}

	retv.center.x = ternary_search(f1, botx, topx, EPS);

	return -f1(retv.center.x);
}

int main(void)
{
	int n;
	double r;
	cin >> n >> r;
	vector<point> p(n);
	for (int i = 0; i < n; i++)
		cin >> p[i].x >> p[i].y;

	printf("%.20lf\n", max_circle_intersection(p, r));
}
