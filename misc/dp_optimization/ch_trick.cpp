// https://codeforces.com/contest/319/problem/C

#include "../../data_structures/line_container/line_container.cpp"

/*
	Convex Hull Trick for DP:
		Transforms dp of the form (or similar) dp[i] = min_{j < i}(dp[j] + b[j] * a[i]).
		Time goes from O(n^2) to O(n log n), if using online line container, or O(n) if
		lines are inserted in order of slope and queried in order of x.

		To apply try to find a way to write the factor inside minimization as a linear function
		of a value related to i. Everything else related to j will become constant.
*/

#define MAXN 112345

int a[MAXN];
int b[MAXN];

ll tab[MAXN];

int main(void)
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	for (int i = 0; i < n; i++)
		scanf("%d", &b[i]);

	tab[0] = 0;
	line_container l;
	l.add(-b[0], -tab[0]);

	for (int i = 1; i < n; i++)
	{
		tab[i] = -l.query(a[i]);
		l.add(-b[i], -tab[i]);
	}

	// Original DP O(n^2).
	// for (int i = 1; i < n; i++)
	// {
	// 	tab[i] = inf;
	// 	for (int j = 0; j < i; j++)
	// 		tab[i] = min(tab[i], tab[j] + a[i] * b[j]);
	// }

	cout << tab[n - 1] << endl;
}
