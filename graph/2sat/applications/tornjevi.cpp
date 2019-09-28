// https://www.spoj.com/problems/TORNJEVI/
#include "../2sat.cpp"

#define MAXN 112

char grid[MAXN][MAXN];
int num[MAXN][MAXN];

enum dirs { down, up, right, left };
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int ans[2][2] = {{4,3}, {1,2}};

int go(int i, int j, int dir)
{
	do
	{
		i += dx[dir];
		j += dy[dir];
	} while (grid[i][j] != '#' && grid[i][j] != 'T');
	
	return (grid[i][j] == 'T') ? num[i][j] : -1;
}

int var(int x, int dir)
{
	int tmp = 2*x+dir/2;
	return (dir&1) ? (~tmp) : tmp;
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);
	memset(grid, '#', sizeof(grid));

	int tw = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf(" %c", &grid[i][j]);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (grid[i][j] == 'T')
				num[i][j] = tw++;

	two_sat st(2*tw);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (grid[i][j] == 'T')
				for (int k = 0; k < 4; k++)
				{
					int y = go(i, j, k);
					if (y != -1)
						st.set_true(~var(num[i][j], k));
				}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (grid[i][j] == 'n')
			{
				int l = go(i, j, dirs::left);
				int r = go(i, j, dirs::right);
				int d = go(i, j, dirs::down);
				int u = go(i, j, dirs::up);

				if ((l == -1 && r == -1) || (l != -1 && r != -1))
				{
					if (u != -1)
						st.set_true(var(u, down));
					else
						st.set_true(var(d, up));
				}
				else if ((d == -1 && u == -1) || (d != -1 && u != -1))
				{
					if (l != -1)
						st.set_true(var(l, dirs::right));
					else
						st.set_true(var(r, dirs::left));
				}
				else
				{
					if (l != -1)
					{
						if (u != -1)
							st.either(var(l, dirs::right), var(u, down));
						else
							st.either(var(l, dirs::right), var(d, up));
					}
					else
					{
						if (u != -1)
							st.either(var(r, dirs::left), var(u, down));
						else
							st.either(var(r, dirs::left), var(d, up));
					}
				}
			}

	st.solve();
	for (int i = 1; i <= n; i++, printf("\n"))
		for (int j = 1; j <= m; j++)
			if (grid[i][j] == 'T')
			{
				printf("%d", ans[st.values[var(num[i][j], dirs::down)]][st.values[var(num[i][j], dirs::right)]]);
			}
			else
			{
				printf("%c", grid[i][j]);
			}
}
