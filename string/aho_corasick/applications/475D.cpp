// https://codeforces.com/problemset/problem/963/D

#include "../aho_corasick.cpp"

#define MAXN 112345

int k[MAXN];

int main()
{
	cin.sync_with_stdio(0);
	cin.tie(0);

	string text;
	cin >> text;

	int n;
	cin >> n;
	vector<string> pats(n);
	for (int i = 0; i < n; i++)
		cin >> k[i] >> pats[i];
	
	aho_corasick aho(pats);
	auto tmp = aho.find_all(text);

	vector<vector<int>> m(n);
	for (int i = 0; i < sz(tmp); i++)
		for (auto x : tmp[i])
			m[x].push_back(i);
	
	for (int i = 0; i < n; i++)
	{
		int r = 0;
		int ans = inf;
		for (int j = 0; j + k[i] <= sz(m[i]); j++)
		{
			while (r < sz(m[i]) && r - j + 1 < k[i])
				r++;
			if (r - j + 1 == k[i])
				ans = min(ans, m[i][r] - m[i][j] + sz(pats[i]));
		}

		cout << (ans == inf ? -1 : ans) << "\n";
	}
}
