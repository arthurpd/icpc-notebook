#include "../2d/2d.cpp"
#include "../../misc/ternary_search/ternary_search_continuous.cpp"

/*
	Minimum Enclosing Circle:
		Given a list of points, returns a circle of minimum radius such that all given
		points are within the circle.
		Runs in O(n * log^2((top - bot) / eps)) (in practice 2.5s at best for 10^5 points).

	Constraints:
		Non-empty list of points.
	
	Usage:
		The coordinates of the circle's center must be in the range [bot, top].
		eps specifies the precision of the result, but set it to a higher value
		than necessary since the error in x affects the y value.

	Author: Arthur Pratti Dadalto
*/

#define point point<double>
#define circle circle<double>

circle min_enclosing_circle(const vector<point> &p, double bot = -1e9, double top = 1e9, double eps = 1e-9)
{
	circle retv;

	auto f1 = [&](double x) {
		auto f2 = [&](double y)
		{
			double r = 0;
			for (int i = 0; i < sz(p); i++)
				r = max(r, (p[i].x - x)*(p[i].x - x) + (p[i].y - y)*(p[i].y - y));
			return r;
		};
		retv.center.y = ternary_search(f2, bot, top, eps);
		return f2(retv.center.y);
	};

	retv.center.x = ternary_search(f1, bot, top, eps);
	retv.r = sqrt(f1(retv.center.x));

	return retv;
}
