//https://www.spoj.com/problems/ADASTRNG/

#include "../sa.cpp"

long long ans[30];

int main(void)
{
	string s;
	cin >> s;
	auto sa = suffix_array(s);
	for (int i = 1; i <= s.size(); i++)
		ans[s[sa.sa[i]] - 'a'] += s.size() - sa.sa[i] - sa.lcp[i];

	for (int i = 0; i < 26; i++)
		printf("%lld%c", ans[i], i + 1 == 26 ? '\n' : ' ');
}
