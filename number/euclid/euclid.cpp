#include "../../contest/header.hpp"

/*
	Extended Euclidean Algorithm:
		Returns the gcd of a and b.
		Also finds numbers x and y for which a * x + b * y = gcd(a, b) (not unique).
		All pairs can be represented in the form (x + k * b / gcd, y - k * a / gcd) for k an arbitrary integer.
		If there are several such x and y, the function returns the pair for which |x| + |y| is minimal.
		If there are several x and y satisfying the minimal criteria, it outputs the pair for which X <= Y.

	Source: modified from https://cp-algorithms.com/algebra/extended-euclid-algorithm.html

	Usage:
		For non-extendend version, c++ has __gcd and __lcm.

	Constraints:
		Produces correct results for negative integers as well.
*/

int gcd(int a, int b, int &x, int &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}

	int x1, y1;
	int d = gcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - y1 * (a / b);
	return d;
}
