#include "../../contest/header.hpp"

/*
	Sieve of Eratosthenes:
		Finds all primes in interval [2, MAXP] in O(MAXP) time.
		Also finds lp[i] for every i in [2, MAXP], such that lp[i] is 
		the minimum prime factor of i.
		Particularly useful for factorization.

	Source: modified from https://cp-algorithms.com/algebra/
							prime-sieve-linear.html

	Usage:
		Set MAXP and call init.
		Sieve for 10^7 should run in about 0.2 s.
*/

namespace sieve
{
const int MAXP = 10000000; // Will find primes in interval [2, MAXP].
int lp[MAXP + 1]; // lp[i] is the minimum prime factor of i.
vector<int> p; // Ordered list of primes up to MAXP.

void init()
{
	for (int i = 2; i <= MAXP; i++)
	{
		if (lp[i] == 0)
			p.push_back(lp[i] = i);

		for (int j = 0; j < (int)p.size() && p[j] <= lp[i] && i * p[j] <= MAXP; j++)
			lp[i * p[j]] = p[j];
	}
}
} // namespace sieve
