// https://www.spoj.com/problems/PCPC12F/

#include "../../../numerical/linalg/mat.cpp"

#define mat mat<double>
#define vec vec<double>

#define MAXN 112

int prox[MAXN];

int main(void)
{
	int n, m, s, l, h, t;
	while (scanf("%d %d %d %d", &n, &m, &s, &l) != EOF)
	{
		memset(prox, -1, sizeof(prox));
		for (int i = 0; i < s + l; i++)
		{
			scanf("%d %d", &h, &t);
			prox[h] = t;
		}

		int nstates = n * m + 1;
		mat Q(nstates - 1, nstates - 1); // State nstates - 1 is final state.

		for (int i = 0; i < nstates - 1; i++)
		{
			for (int roll = 1; roll <= 6; roll++)
			{
				if (i + roll >= nstates)
					Q[i][i] += 1.0 / 6;
				else
				{
					int j = i + roll;
					while (j != nstates - 1 && prox[j] != -1)
						j = prox[j];

					if (j != nstates - 1)
						Q[i][j] += 1.0 / 6;
				}
			}
		}

		mat id(nstates - 1, nstates - 1);
		for (int i = 0; i < nstates - 1; i++)
			id[i][i] = 1;

		mat N = (id - Q).inverse();

		double ans = 0;
		for (int i = 0; i < nstates - 1; i++)
			ans += N[0][i];

		printf("%.3lf\n", ans);
	}
}
