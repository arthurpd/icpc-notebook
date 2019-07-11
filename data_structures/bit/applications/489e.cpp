// https://codeforces.com/contest/992/problem/E
#include "../bit.cpp"

int main(void)
{
	int n, q;
	cin >> n >> q;
	vector<int> a(n + 1);
	bit<long long> bit(n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		bit.update(i, a[i]);
	}

	int p, x;
	for (int i = 0; i < q; i++)
	{
		scanf("%d %d", &p, &x);
		bit.update(p, x - a[p]);
		a[p] = x;

		long long sum = 0;
		while (true)
		{
			p = bit.lower_bound(sum);
			if (p > n)
				break;

			if (bit.query(p) == 2 * bit.query(p - 1))
				break;
			
			sum = 2 * bit.query(p);
		}

		printf("%d\n", p > n ? -1 : p);
	}
}
