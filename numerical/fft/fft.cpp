#include "../../contest/header.hpp"

/*
	Modular Inverse:
		FFT allows multiplication of two polynomials in O(n log n).
		This can also be used to multiply two long numbers faster.
		Other applications: 
		- All possible sums of two arrays.
		- Dot product of vector a with every cyclic shift of vector b.
		- Attaching two boolean stripes without two 1s next to each other.
		- String matching.
	
	Usage:
		long double is a lot slower. 3s with ld and 0.7 with double for 10^6 size vectors.

	Source: https://cp-algorithms.com/algebra/fft.html
*/

using cd = complex<long double>;
const ld PI = acos(-1.0L);

void fft(vector<cd> &a, bool invert)
{
	int n = a.size();

	for (int i = 1, j = 0; i < n; i++)
	{
		int bit = n >> 1;
		for (; j & bit; bit >>= 1)
			j ^= bit;
		j ^= bit;

		if (i < j)
			swap(a[i], a[j]);
	}

	for (int len = 2; len <= n; len <<= 1)
	{
		ld ang = 2 * PI / len * (invert ? -1 : 1);
		cd wlen(cos(ang), sin(ang));
		for (int i = 0; i < n; i += len)
		{
			cd w(1);
			for (int j = 0; j < len / 2; j++)
			{
				cd u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}

	if (invert)
	{
		for (cd &x : a)
			x /= n;
	}
}

// Input a[0] + a[1]x + a[2]x^2 ...
// Returns polynomial of size equal to the smallest power of two at least
// as large as a.size() + b.size(). This can have some extra zeros.
// Use long double if using long long.
template <class T>
vector<T> multiply(vector<T> const &a, vector<T> const &b)
{
	vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1;
	while (n < a.size() + b.size())
		n <<= 1;
	fa.resize(n);
	fb.resize(n);

	fft(fa, false);
	fft(fb, false);
	for (int i = 0; i < n; i++)
		fa[i] *= fb[i];
	fft(fa, true);

	vector<T> result(n);
	for (int i = 0; i < n; i++)
		result[i] = round(fa[i].real()); // Remember to remove rounding if working with floats.
	return result;
}
