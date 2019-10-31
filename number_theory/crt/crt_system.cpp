#include "../../contest/header.hpp"
#include "../euclid/euclid.cpp"
/*
    [DESCRIPTION]
     Returns a integer a number x, such that:
        x = a[0] (mod m[0])
        x = a[1] (mod m[1])
        ...
        x = a[n - 1] (mod m[n - 1])

    The m[] set does not need to be only of coprimes, because it uses the generalized version of
    CRT.

    [USAGE]
     Just pass the arrays as shown above in the description and their size.
     It's 0-indexed, but its trivial to change it to 1-indexed.

    [RESULT]
     The function returns x % LCM(m[0], m[1], ..., m[n - 1]) if a answer exists. Otherwise
     it returns -1.
    
    [COMPLEXITY]
     O( n * log(LCM(m)) )

    [CONSTRAINTS]
        LCM(m[0], m[1], ..., m[n - 1]) should fit in a long long variable.
        The values of a[] can be arbitrary, because they are normalized inside the function

    source: https://codeforces.com/blog/entry/61290

*/

ll crt(ll a[], ll m[], int n)
{
    for(int i = 0; i < n; i++) 
        a[i] = (a[i] % m[i] + m[i]) % m[i];
    ll ans = a[0];
    ll lcm = m[0];
    for(int i = 1; i < n; i++)
    {
        ll x1, y;
        ll d = gcd<ll>(lcm, m[i], x1, y);
        if((a[i] - ans) % d != 0)
            return -1;
        ll new_lcm = lcm * m[i] / d;
        ans = ((ans + x1 * (a[i] - ans) / d % (m[i] / d) * lcm) % new_lcm + new_lcm) % new_lcm;
        lcm = new_lcm;
    }
    return ans;
}