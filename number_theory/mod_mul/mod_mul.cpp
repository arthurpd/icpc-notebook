#include "../../contest/header.hpp"

/*
    Description: 
		Calculate a * b mod c (or a^b mod c) for 0 ≤ a, b < c < 2^63.
    Time: 
		mod_mul: O (1)
		mod_pow: (log b)
	Source: https://github.com/kth-competitive-programming/
*/

ull mod_mul(ull a, ull b, ull M)
{
	ll ret = a * b - M * ull(ld(a) * ld(b) / ld(M));
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull mod_pow(ull b, ull e, ull mod)
{
	ull ans = 1;
	for (; e; b = mod_mul(b, b, mod), e /= 2)
		if (e & 1)
			ans = mod_mul(ans, b, mod);
	return ans;
}