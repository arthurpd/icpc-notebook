// https://www.spoj.com/problems/POLYMUL/

#include "../fft.cpp"

int main(void)
{
	int T, n;
	cin >> T;
	while(T--)
	{
		scanf("%d", &n);
		vector<ll> a(n + 1), b(n + 1);
		for (int i = 0; i < n + 1; i++)
			scanf("%lld", &a[i]);
		for (int i = 0; i < n + 1; i++)
			scanf("%lld", &b[i]);
		vector<ll> c = multiply(a, b);

		for (int i = 0; i < 2*n + 1; i++)
			printf("%lld%c", c[i], (i + 1 < 2*n + 1) ? ' ' : '\n');
	}
}
