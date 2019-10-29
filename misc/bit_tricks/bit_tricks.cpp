
// Returns one plus the index of the least significant 1-bit of x, or if x is zero, returns zero.
__builtin_ffs(x)

// Returns the number of leading 0-bits in x, starting at the most significant bit position. If x is 0, the result is undefined.
__builtin_clz(x)

// Returns the number of trailing 0-bits in x, starting at the least significant bit position. If x is 0, the result is undefined.
__builtin_ctz(x)

// Returns the number of 1-bits in x.
__builtin_popcount(x)

// For long long versions append ll (e.g. __builtin_popcountll)

// Least significant bit in x.
x & -x

// Iterate on non-empty submasks of a bitmask.
for (int submask = mask; submask > 0; submask = (mask & (submask - 1)))

// Iterate on non-zero bits of a bitset.
for (int j = btset._Find_next(0); j < MAXV; j = btset._Find_next(j))
