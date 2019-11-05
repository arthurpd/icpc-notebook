// https://www.spoj.com/problems/BRKSTRNG/

#include "../../contest/header.hpp"

/*
	Knuth Optimization for DP:
		Optimizes dp of the form (or similar) 
			dp[i][j] = 
				min_{i <= k <= j}(dp[i][k-1] + dp[k+1][j] + c(i, j)).
		The classical case is building a optimal binary tree, where k 
		determines the root.
		
		Let opt[i][j] be the value of k which minimizes the function. 
		(in case of tie, choose the smallest)
		To apply this optimization, you need 
			opt[i][j - 1] <= opt[i][j] <= opt[i+1][j].
		That means the when you remove an element form the left 
		(i + 1), you won't choose a breaking point more to the left 
		than before.
		Also, when you remove an element from the right (j - 1), you 
		won't choose a breking point more to the right than before.
		This is usually intuitive by the problem details.
		
		Time goes from O(n^3) to O(n^2).

		To apply try to write the dp in the format above and verify if 
		the property holds.
		Be careful with edge cases for opt.

	Author: Arthur Pratti Dadalto
*/

#define MAXN 1123

int b[MAXN];
ll tab[MAXN][MAXN];
int opt[MAXN][MAXN];
int l, n;

int c(int i, int j)
{
	return b[j + 1] - b[i - 1];
}

int main(void)
{
	while (scanf("%d %d", &l, &n) != EOF)
	{
		for (int i = 1; i <= n; i++)
			scanf("%d", &b[i]);
		b[n + 1] = l;
		b[0] = 0;

		for (int i = 1; i <= n + 1; i++)
			tab[i][i - 1] = 0, opt[i][i - 1] = i;

		for (int i = n; i > 0; i--)
			for (int j = i; j <= n; j++)
			{
				tab[i][j] = infll;
				for (int k = max(i, opt[i][j - 1]); k <= j && k <= opt[i + 1][j]; k++)
					if (tab[i][k - 1] + tab[k + 1][j] + c(i, j) < tab[i][j])
					{
						tab[i][j] = tab[i][k - 1] + tab[k + 1][j] + c(i, j);
						opt[i][j] = k;
					}
			}

		printf("%lld\n", tab[1][n]);
	}
}
