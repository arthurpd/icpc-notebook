#include "antipodal_pairs.cpp"

/*
	Polygon Width O(n):
		Gets the smallest width for a "tunnel" by which you can
		slide the convex polygon.
	
	Author: Arthur Pratti Dadalto
*/

// p is a convex hull in ccw order with no duplicate or collinear points.
double convex_polygon_width(const vector<point<ll>> &p)
{
	vector<pii> anti = antipodal_pairs(p);

	double retv = 1e18;
	for (int i = 0; i < sz(anti); i++)
	{
		line<ll> l(p[anti[i].first], p[(anti[i].first + 1) % sz(p)]);
		if (l.dist(p[anti[i].second]) < retv)
			retv = l.dist(p[anti[i].second]);
	}

	return retv;
}
