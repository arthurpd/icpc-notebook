#include "../../contest/header.hpp"
#include "../euclid/euclid.cpp"

/*
    [DESCRIPTION]
     Returns a number x % lcm(m,n), such that: 
        x ≡ a (mod m)
        x ≡ b (mod n)
     
     returns -1 if there is no solution

    [COMPLEXITY]
     log(n)

    [CONSTRAINTS]
        LCM(m, n) should fit in a long long variable.
*/

ll crt(ll a, ll m, ll b, ll n)
{
    if (n > m)
        swap(a, b), swap(m, n);
    ll x, y, g = gcd<ll>(m, n, x, y);
    if ((a - b) % g != 0)
        return -1;
    x = (b - a) % n * x % n / g * m + a;
    return x < 0 ? x + m * n / g : x;
}
