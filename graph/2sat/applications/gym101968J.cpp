// https://codeforces.com/gym/101968/problem/J
#include "../2sat.cpp"

int main(void)
{
	cin.sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;
	while (T--)
	{
		int n, m, a, b, c;
		cin >> n >> m;
		two_sat st(n);
		for (int i = 0; i < m; i++)
		{
			cin >> a >> b >> c;
			a--, b--;
			st.either(a, b);
			if (c)
				st.at_most_one({a, b});
		}

		cout << (st.solve() ? "YES" : "NO") << endl;
	}
}
