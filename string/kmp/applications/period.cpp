// https://www.spoj.com/problems/PERIOD/

#include "../kmp.cpp"

int main(void)
{
	int t, n;
	scanf("%d", &t);
	for (int k = 1; k <= t; k++)
	{
		scanf("%d", &n);
		string s;
		cin >> s;

		vector<int> pi = prefix_function(s);

		printf("Test case #%d\n", k);
		for (int i = 1; i <= n; i++)
			if (pi[i] % (i - pi[i]) == 0 && i / (i - pi[i]) != 1)
				printf("%d %d\n", i, i / (i - pi[i]));
		printf("\n");
	}
}
