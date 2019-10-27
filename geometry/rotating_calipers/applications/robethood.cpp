// https://open.kattis.com/problems/roberthood
// IMPORTANT: need to change convex hull code to pass (no collinear points).

#include "../convex_polygon_diameter.cpp"

int main(void)
{
	int n;
	cin >> n;
	vector<point<ll>> p(n);
	for (int i = 0; i < n; i++)
		cin >> p[i].x >> p[i].y;
	
	auto ch = CH(p);

	double ans = convex_polygon_diameter(ch);;

	printf("%.20lf\n", ans);
}
