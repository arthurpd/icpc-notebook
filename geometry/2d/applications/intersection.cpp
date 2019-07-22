// https://open.kattis.com/problems/segmentintersection
#include "../2d.cpp"

#define point point<double>
#define segment segment<double>

int main(void)
{
	segment s1, s2;
	int n;
	scanf("%d", &n);
	while(n--)
	{
		scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &s1.pi.x, &s1.pi.y, &s1.pf.x, &s1.pf.y, &s2.pi.x, &s2.pi.y, &s2.pf.x, &s2.pf.y);
		auto v = s1.intersect(s2);
		if (v.size() == 0)
			printf("none\n");
		else if (v.size() == 1)
			printf("%.2lf %.2lf\n", (abs(v[0].x) < 0.005) ? 0.0 : v[0].x, (abs(v[0].y) < 0.005) ? 0.0 : v[0].y);
		else
		{
			printf("%.2lf %.2lf %.2lf %.2lf\n",  (abs(v[0].x) < 0.005) ? 0.0 : v[0].x, (abs(v[0].y) < 0.005) ? 0.0 : v[0].y, (abs(v[1].x) < 0.005) ? 0.0 : v[1].x, (abs(v[1].y) < 0.005) ? 0.0 : v[1].y);
		}
	}
}

