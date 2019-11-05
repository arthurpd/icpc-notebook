#include "antipodal_pairs.cpp"

/*
	Polygon Diameter O(n):
		Gets the largest distance for a pair of points
		in a convex polygon.
	
	Author: Arthur Pratti Dadalto
*/

// p is a convex hull in ccw order with no duplicate or
// collinear points.
double convex_polygon_diameter(const vector<point<ll>> &p)
{
	vector<pii> anti = antipodal_pairs(p);

	double retv = 0;
	for (pii a : anti)
	{
		if ((p[a.first] - p[a.second]).dist() > retv)
			retv = (p[a.first] - p[a.second]).dist();

		if ((p[(a.first + 1) % sz(p)] - p[a.second]).dist() > retv)
			retv = (p[(a.first + 1) % sz(p)] - p[a.second]).dist();
	}

	return retv;
}
