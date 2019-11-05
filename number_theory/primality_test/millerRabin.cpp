/*
    Description: 
        Deterministic Miller-Rabin primality test. 
        Guaranteed to work for numbers up to 2^64 (for larger 
        numbers, extend A randomly).

    Time: 
        7 * O(log b)

     Source: https://github.com/kth-competitive-programming/
*/

#include "../../contest/header.hpp"
#include "../mod_mul/mod_mul.cpp"

bool isPrime(ull n)
{
    if (n < 2 || n % 6 % 4 != 1)
        return n - 2 < 2;
    ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
        s = __builtin_ctzll(n - 1), d = n >> s;
    for (auto &a : A)
    { // ^ count trailing zeroes
        ull p = mod_pow(a, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--)
            p = mod_mul(p, p, n);
        if (p != n - 1 && i != s)
            return 0;
    }
    return 1;
}
