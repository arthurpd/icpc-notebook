#include "../mod_inverse/mod_inverse.cpp"

/*
	Modular Arithmetic:
		Struct wrapper on to of modular arithmetics.

	Source: modified from https://github.com/
	kth-competitive-programming/kactl/blob/master/content/
	number-theory/ModularArithmetic.h
*/

template <ll mod>
struct mod_num
{
	ll x;
	explicit mod_num(ll x = 0) : x(x % mod) {}
	mod_num operator+(mod_num b) { return mod_num(x + b.x); }
	mod_num operator-(mod_num b) { return mod_num(x - b.x + mod); }
	mod_num operator*(mod_num b) { return mod_num(x * b.x); }
	mod_num operator/(mod_num b) { return mod_num(x * mod_inverse(b.x, mod)); }
	mod_num operator^(ll e)
	{
		mod_num ans(1);
		mod_num b = *this;
		for (; e; b = b * b, e /= 2)
			if (e & 1)
				ans = ans * b;
		return ans;
	}

	void operator+=(mod_num b) { x = (x + b.x) % mod; }
};

template <ll mod>
ostream &operator<<(ostream &os, mod_num<mod> x)
{
	return os << x.x;
}
