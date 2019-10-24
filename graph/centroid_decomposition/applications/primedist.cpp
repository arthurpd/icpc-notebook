// https://www.codechef.com/problems/PRIMEDST

#include "../../../numerical/fft/fft.cpp"
#include "../../../number_theory/sieve/sieve.cpp"
#include "../centroid.cpp"

ll ans[MAXN];

void dfs(int a, int p, int l, vector<ll> &nh)
{
	while (sz(nh) <= l)
		nh.push_back(0);

	nh[l]++;
	for (int i = 0; i < sz(graph[a]); i++)
		if (graph[a][i] != p && !block[graph[a][i]])
			dfs(graph[a][i], a, l + 1, nh);
}

void process(int a, int sz)
{
	vector<ll> tot(1);
	tot[0] = 1;

	for (int i = 0; i < sz(graph[a]); i++)
		if (!block[graph[a][i]])
		{
			vector<ll> nh;
			dfs(graph[a][i], a, 1, nh);

			for (int j = 0; j < sz(nh); j++)
			{
				while (sz(tot) <= j)
					tot.push_back(0);

				tot[j] += nh[j];
			}

			auto intra_paths = multiply(nh, nh);
			for (int j = 0; j < sz(intra_paths); j++)
				if (intra_paths[j] != 0)
					ans[j] -= intra_paths[j];
		}

	auto total_paths = multiply(tot, tot);
	total_paths[0]--;
	for (int j = 0; j < sz(total_paths); j++)
		if (total_paths[j] != 0)
			ans[j] += total_paths[j];
}

int main(void)
{
	sieve::init();
	cin.sync_with_stdio(0);
	cin.tie(0);

	int n, a, b;
	cin >> n;
	for (int i = 0; i + 1 < n; i++)
	{
		cin >> a >> b;
		put_edge(a, b);
	}

	decomp(1, n);

	ll total = 0;
	for (int i = 0; i < n; i++)
		if (i > 1 && sieve::lp[i] == i)
			total += ans[i] / 2;

	if (n == 1)
	{
		cout << total << endl;
	}
	else
	{
		printf("%.20lf\n", total / (n * 1ll * (n - 1) / 2.0));
	}
}
