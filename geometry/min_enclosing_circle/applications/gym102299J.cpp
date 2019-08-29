// https://codeforces.com/gym/102299

#include "../randomized.cpp"
// #include "../ternary_search.cpp"

int main(void)
{
	int n;
	scanf("%d", &n);
	vector<point> p(n);
	for (int i = 0; i < n; i++)
		scanf("%lf %lf", &p[i].x, &p[i].y);

	if (n == 0)
		printf("0 0 0\n");
	else
	{
		circle ans = min_enclosing_circle(p/*, -1e4, 1e4, 1e-7*/);
		printf(" %.15lf %.15lf %.15lf\n", ans.center.x, ans.center.y, ans.r * ans.r / 2);
	}
}
