#include "../euclid/euclid.cpp"
/*
        Modular Inverse:
                Returns an integer x such that (a * x) % m == 1.
                The modular inverse exists if and only if a and m are
                relatively prime.
                Modular inverse is also equal to a^(phi(m) - 1) % m.
                In particular, if m is prime a^(-1) == a^(m-2), which might
   be faster to code.

        Source: modified from https://cp-algorithms.com/algebra/
                                                        module-inverse.html
*/
template <class T>
T mod_inverse(T a, T m) {
  T x, y;
  assert(gcd(a, m, x, y) == 1);  // Or return something, if gcd is
                                 // not 1 the inverse doesn't exist.
  return (x % m + m) % m;
}
