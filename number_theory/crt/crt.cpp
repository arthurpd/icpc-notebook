#include "../../contest/header.hpp"
#include "../euclid/euclid.cpp"

/*
    [DESCRIPTION]
     Returns a number x, such that: 
        x ≡ a (mod m)
        x ≡ b (mod n)
    
    [USAGE]
        if n, m are coprimes: use chinese()
        else: use chinese_common()  // its possible to use when n, m are coprimes either
            
*/

template<class Z> Z chinese(Z a, Z m, Z b, Z n) {
    Z x, y; gcd<Z>(m, n, x, y);
    Z ret = a * (y + m) % m * n + b * (x + n) % n * m;
    if (ret >= m * n) ret -= m * n;
    return ret;
}

template<class Z> Z chinese_common(Z a, Z m, Z b, Z n) {
    Z d = gcd<Z>(m, n);
    if (((b -= a) %= n) < 0) b += n;
    if (b % d) return -1; // No solution
    return d * chinese(Z(0), m/d, b/d, n/d) + a;
}
