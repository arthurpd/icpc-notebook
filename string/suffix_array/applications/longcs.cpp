// https://www.spoj.com/problems/LONGCS/

#include "../sa.cpp"

int findsrc(vector<int> &v, int j)
{
	for (int i = 0; i < v.size(); i++)
		if (j < v[i])
			return i;
		else
		{
			j -= v[i];
		}
	
	assert(false);
}

int main(void)
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int n;
		scanf("%d", &n);
		string s, tmp;
		vector<int> v;
		for (int i = 0; i < n; i++)	
		{
			cin >> tmp;
			v.push_back(tmp.size() + 1);
			s += tmp;
			s += i + 1;
		}

		int ans = 0;
		auto sa = suffix_array(s);
		int j = 0;
		vector<int> cnt(n, 0);
		multiset<int> rdm;
		for (int i = 1; i <= s.size(); i++)
		{
			while (j + 1 <= s.size() && count(cnt.begin(), cnt.end(), 0) != 0)
			{
				j++;

				cnt[findsrc(v, sa.sa[j])]++;
				rdm.insert(sa.lcp[j]);
			}

			rdm.erase(rdm.find(sa.lcp[i]));

			if (count(cnt.begin(), cnt.end(), 0) == 0)
				ans = max(ans, *rdm.begin());

			cnt[findsrc(v, sa.sa[i])]--;
		}

		cout << ans << endl;
	}
}

