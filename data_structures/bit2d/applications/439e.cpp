// https://codeforces.com/problemset/problem/869/E
#include "../bit2d.cpp"

#define NHASH 3
#define MAXN 3123
int tab[MAXN][MAXN][NHASH];

int main(void)
{
	int n, m, q;
	scanf("%d %d %d", &n, &m, &q);
	srand(42);

	vector<bit2d<long long>> bit;
	for (int i = 0; i < NHASH; i++)
		bit.emplace_back(n, m);

	for (int i = 0; i < q; i++)
	{
		int tp, r1, r2, c1, c2;
		scanf("%d %d %d %d %d", &tp, &r1, &c1, &r2, &c2);
		if (tp == 1)
		{
			for (int j = 0; j < NHASH; j++)
			{
				assert(bit[j].query_rect(r1, c1, r2 + 1, c2 + 1) == 0);
				tab[r1][c1][j] = rand();
				bit[j].update(r1, c1, tab[r1][c1][j]);
				bit[j].update(r1, c2 + 1, -tab[r1][c1][j]);
				bit[j].update(r2 + 1, c1, -tab[r1][c1][j]);
				bit[j].update(r2 + 1, c2 + 1, tab[r1][c1][j]);
				assert(bit[j].query_rect(r1, c1, r2 + 1, c2 + 1) == 0);
			}
		}
		else if (tp == 2)
		{
			for (int j = 0; j < NHASH; j++)
			{
				assert(bit[j].query_rect(r1, c1, r2 + 1, c2 + 1) == 0);
				bit[j].update(r1, c1, -tab[r1][c1][j]);
				bit[j].update(r1, c2 + 1, tab[r1][c1][j]);
				bit[j].update(r2 + 1, c1, tab[r1][c1][j]);
				bit[j].update(r2 + 1, c2 + 1, -tab[r1][c1][j]);				
				assert(bit[j].query_rect(r1, c1, r2 + 1, c2 + 1) == 0);
			}
		}
		else
		{
			bool ok = true;
			for (int j = 0; j < NHASH; j++)
				ok = ok && (bit[j].query(r1, c1) == bit[j].query(r2, c2));

			printf("%s\n", ok ? "Yes" : "No");
		}		
	}
}
