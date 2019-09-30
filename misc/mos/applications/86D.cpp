// https://codeforces.com/contest/86/problem/D

#include "../mos.cpp"

#define MAXN 212345

int a[MAXN];
ll ans[MAXN];
ll val = 0;
int freq[1123456];

ll calc(int x)
{
	return freq[x] * 1ll * freq[x] * 1ll * x;
}

void add(int i)
{
	val += (long long)(2 * freq[a[i]] + 1) * a[i];
	freq[a[i]]++;
}

void remove(int i)
{
	val -= (long long)(2 * freq[a[i]] - 1) * a[i];
	freq[a[i]]--;
}

void output(int i)
{
	ans[i] = val;
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);
	vector<query> q(m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &q[i].l, &q[i].r);
		q[i].id = i;
	}

	mos(n, q, add, remove, output);
	for (int i = 0; i < m; i++)
		printf("%lld\n", ans[i]);
}
