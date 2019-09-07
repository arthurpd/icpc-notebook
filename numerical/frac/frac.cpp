#include "../../contest/header.hpp"

/*
	Fraction representation:
		All operations run in O(gcd) = O(log).
	
	Usage:
		Don't modify internal values, use constructor.
		Some nice things about the constructor: frac() = 0/1, frac(5) = 5/1.

		Be careful that the numerator and denominator might overflow if lcm is too big.
		In those cases, you can always do frac<big_int>, but that will be painful to code.

	Author: Arthur Pratti Dadalto
*/

template <class T>
struct frac
{
	T a, b; // b can't be negative, very important.

	explicit frac(T a = 0, T b = 1) : a(a), b(b) { simpl(); }

	void simpl()
	{
		T g = __gcd(abs(a), abs(b)) * sign(b); // Make b positive.
		a /= g;
		b /= g;
	}

	bool operator<(const frac &rhs) const
	{
		return a * rhs.b < rhs.a * b;
	}

	bool operator>(const frac &rhs) const
	{
		return rhs < *this;
	}

	bool operator==(const frac &rhs) const // TODO: untested.
	{
		return !(*this < rhs) && !(rhs < *this);
	}

	frac operator*(const frac &rhs) const
	{
		return frac(a * rhs.a, b * rhs.b);
	}

	frac operator+(const frac &rhs) const
	{
		T m = (b * rhs.b) / __gcd(b, rhs.b);
		return frac(a * (m / b) + rhs.a * (m / rhs.b), m);
	}

	frac operator-(void) const
	{
		return frac(-a, b);
	}

	frac operator-(const frac &rhs) const
	{
		return (*this) + (-rhs);
	}

	frac operator/(const frac &rhs) const
	{
		return (*this) * frac(rhs.b, rhs.a);
	}

	friend ostream &operator<<(ostream &os, const frac &f)
	{
		return os << f.a << "/" << f.b;
	}
};

