 /*
  Description: Pollard-rho randomized factorization algorithm. Returns prime
  factors of a number, in arbitrary order (e.g. 2299 -> {11, 19, 11}).
  Time: O(n^1/4) gcd calls, less for numbers with small factors.
   
  Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/number-theory/Factor.h
 */
typedef unsigned long long ull;
typedef long double ld;
 
ull mod_mul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(ld(a) * ld(b) / ld(M));
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull mod_pow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = mod_mul(b, b, mod), e /= 2)
		if (e & 1) ans = mod_mul(ans, b, mod);
	return ans;
}
 
bool isPrime(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return n - 2 < 2;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n >> s;
	for(auto &a : A) {   // ^ count trailing zeroes
		ull p = mod_pow(a, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = mod_mul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}
 
ull pollard(ull n) {
	auto f = [n](ull x) { return (mod_mul(x, x, n) + 1) % n; };
	if (!(n & 1)) return 2;
	for (ull i = 2;; i++) {
		ull x = i, y = f(x), p;
		while ((p = __gcd(n + y - x, n)) == 1)
			x = f(x), y = f(f(y));
		if (p != n) return p;
	}
}

vector<ull> factorize(ull n) {
	if (n == 1) return {};
	if (isPrime(n)) return {n};
	ull x = pollard(n);
	auto l = factorize(x), r = factorize(n / x);
	l.insert(l.end(), all(r));
	return l;
}
