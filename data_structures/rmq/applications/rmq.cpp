// https://www.spoj.com/problems/RMQSQ/

#include "../rmq.cpp"

int main(void)
{
	int n;
	scanf("%d", &n);
	vector<int> a(n);
	for (int i = 0; i < n; a[i] = -a[i], i++)
		scanf("%d", &a[i]);

	int q;
	scanf("%d", &q);

	rmq<int> rm(a);
	for (int i = 0; i < q; i++)
	{
		int x, y;
		scanf("%d %d", &x, &y);
		printf("%d\n", -rm.query(x, y));
	}
}
