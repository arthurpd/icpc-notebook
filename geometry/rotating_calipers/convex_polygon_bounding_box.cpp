#include "../graham_scan(convex_hull)/graham_scan.cpp"

/*
	Bounding Box O(n):
		Finds the smallest perimeter for a rotated rectangle
		that covers the entire given convex polygon.
	
	Author: Arthur Pratti Dadalto
*/

// p is a convex hull in ccw order with no duplicate or collinear points.
// Might not work as expected for two points.
double min_bounding_box_perimeter(const vector<point<ll>> &p)
{
	int j = 1, n = sz(p);
	int k = 1, l = 1;

	double ans = 1e18;
	for (int i = 0; i < n; i++)
	{
		// While j + 1 is farther from segment {i, i+1} than j.
		while (p[i].cross(p[(i + 1) % n], p[(j + 1) % n]) > p[i].cross(p[(i + 1) % n], p[j]))
			j = (j + 1) % n;

		if (i == 0)
			l = j;

		while ((p[(i + 1) % n] - p[i]).dot(p[(k + 1) % n] - p[k]) > 0)
			k = (k + 1) % n;

		while ((p[(i + 1) % n] - p[i]).dot(p[(l + 1) % n] - p[l]) < 0)
			l = (l + 1) % n;

		line<ll> ln(p[i], p[(i + 1) % n]);
		ans = min(ans, 2 * ln.dist(p[j]) +
						   2 * (p[(i + 1) % n] - p[i]).proj(p[k] - p[i]).dist() +
						   2 * (p[(i + 1) % n] - p[i]).proj(p[l] - p[i]).dist());
	}

	return ans;
}
