#include "../graham_scan(convex_hull)/graham_scan.cpp"

/*
	Antipodal pairs O(n):
		Uses rotating calipers techinique to find all antipodal pairs.
		Returned list will be such the the entire polygon lies between
		the line defined by (p[retv[i].first], 
						     p[(retv[i].first + 1) % n])
		and a parallel line passing by p[retv[i].second].
	
	Author: Arthur Pratti Dadalto
*/

// p is a convex hull in ccw order with no duplicate or collinear
// points. Might not work as expected for two points.
vector<pii> antipodal_pairs(const vector<point<ll>> &p)
{
	int j = 1, n = sz(p);
	vector<pii> retv;
	for (int i = 0; i < n; i++)
	{
		// While j + 1 is farther from segment {i, i+1} than j.
		while (p[i].cross(p[(i + 1) % n], p[(j + 1) % n]) > p[i].cross(p[(i + 1) % n], p[j]))
			j = (j + 1) % n;

		retv.push_back({i, j});

		// If j + 1 is at the same distance as j, both pairs are
		// antipodal.
		if (p[i].cross(p[(i + 1) % n], p[(j + 1) % n]) == p[i].cross(p[(i + 1) % n], p[j]))
			retv.push_back({i, (j + 1) % n});
	}

	return retv;
}
