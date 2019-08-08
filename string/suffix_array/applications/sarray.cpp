// https://www.spoj.com/problems/SARRAY/

#include "../sa.cpp"

int main(void)
{
	string s;
	cin >> s;
	auto sa = suffix_array(s);
	for (int i = 1; i <= s.size(); i++)
		printf("%d\n", sa.sa[i]);
}
