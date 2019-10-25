// https://codeforces.com/gym/101128/my

#include "../convex_hull.cpp"

int main(void)
{
	int n, q;
	scanf("%d", &n);
	vector<point> p(n);
	for (int i = 0; i < n; i++)
		scanf("%lld %lld", &p[i].x, &p[i].y);

	vector<point> upper, lower;
	convex_hull(p, upper, lower);

	scanf("%d", &q);
	int ans = 0;
	while (q--)
	{
		point o;
		scanf("%lld %lld", &o.x, &o.y);
		if (point_in_ch(o, upper, lower))
			ans++;
	}

	printf("%d\n", ans);
}
