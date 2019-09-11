// https://br.spoj.com/problems/GROWIN10/
#include "../aho_corasick.cpp"

int main()
{
	cin.sync_with_stdio(0);
	cin.tie(0);

	int n;

	while (cin >> n && n)
	{
		vector<string> s(n);

		for (int i = 0; i < n; i++)
			cin >> s[i];

		sort(s.begin(), s.end(), [](const string &lhs, const string &rhs) { return lhs.size() < rhs.size(); });

		aho_corasick aho(s);

		vector<int> tab(n, 0);
		int ans = 0;
		for (int i = 0; i < n; i++)
		{
			tab[i] = 1;

			auto v = aho.find(s[i]);
			for (int j = 0; j + 1 < sz(s[i]); j++)
				if (v[j] >= 0)
					tab[i] = max(tab[v[j]] + 1, tab[i]);

			v = aho.find_all_at_pos(s[i], sz(s[i]) - 1);
			for (int j = 1; j < sz(v); j++)
				tab[i] = max(tab[v[j]] + 1, tab[i]);
			
			ans = max(ans, tab[i]);
		}

		cout << ans << endl;
	}
}
