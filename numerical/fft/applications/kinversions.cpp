// https://open.kattis.com/problems/kinversions

#include "../fft.cpp"

int main(void)
{
	string s;
	cin >> s;
	int n = s.size();
	vector<int> a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++)
		if (s[i] == 'A')
			a[i] = 1;
		else
		{
			b[n-i-1] = 1;
		}
		
	vector<int> c = multiply(a, b);
	for (int i = n; i < 2*n - 1; i++)
		printf("%d\n", c[i]);
}
