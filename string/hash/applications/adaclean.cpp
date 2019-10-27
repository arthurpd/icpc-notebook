// https://www.spoj.com/problems/ADACLEAN/
#include "../hash.cpp"

int main()
{
	cin.sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--)
	{
		int n, k;
		string s;
		cin >> n >> k;
		cin >> s;

		hash_interval hash1(s, 137, 1000000007);
		hash_interval hash2(s, 137, 1000000009);
		set<pair<ll, ll>> rdm;
		for (int i = 0; i + k - 1 < n; i++)
			rdm.insert({hash1.get(i, i + k - 1), hash2.get(i, i + k - 1)});
		cout << rdm.size()<<endl;
	}
}
