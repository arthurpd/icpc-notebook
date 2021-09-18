
#include "../../contest/header.hpp"
/*
        Suffix array:
                Build suffix array and LCP array in O((n + lim) log n)
   using O(n + lim) memory, where lim is the alphabet size.

                sa[i] is the starting index of the suffix which is i-th in
   the sorted suffix array. The returned vector is of size s.size()+1, and
   sa[0] == s.size(). The '\0' char at the end is considered part of the
   string, so sa[0] = "\0", the prefix starting at index s.size().

                The lcp array contains longest common prefixes for
                neighbouring strings in the suffix array:
                        lcp[i] = lcp(sa[i], sa[i-1]), lcp[0] = 0.

        Example:
                Computing the LCP and the SA of "GATAGACA"
                        i	sa[i]	lcp[i]	suffix
                        0	8		0		""
                        1	7		0		"A"
                        2	5		1		"ACA"
                        3	3		1		"AGACA"
                        4	1		1		"ATAGACA"
                        5	6		0		"CA"
                        6	4		0		"GACA"
                        7	0		2		"GATAGACA"
                        8	2		0		"TAGACA"

        Usage:
                Important: the input string must not contain any zero
   values. Must use C++11 or above. You can use this for strings of
   integers, just change the alphabet size.

        Source: https://github.com/kth-competitive-programming/kactl/blob/
        master/content/strings/SuffixTree.h
*/
struct suffix_array {
  vector<int> sa, lcp;
  suffix_array(const string &s,
               int lim = 256)  // or basic_string<int> for integer strings.
  {
    int n = sz(s) + 1, k = 0, a, b;
    vector<int> x(s.begin(), s.end() + 1), y(n), ws(max(n, lim)), rank(n);
    sa = lcp = y;
    iota(sa.begin(), sa.end(), 0);
    for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
      p = j;
      iota(y.begin(), y.end(), n - j);
      for (int i = 0; i < n; i++)
        if (sa[i] >= j) y[p++] = sa[i] - j;
      fill(ws.begin(), ws.end(), 0);
      for (int i = 0; i < n; i++) ws[x[i]]++;
      for (int i = 1; i < lim; i++) ws[i] += ws[i - 1];
      for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
      swap(x, y);
      p = 1;
      x[sa[0]] = 0;
      for (int i = 1; i < n; i++) {
        a = sa[i - 1];
        b = sa[i];
        x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
      }
    }
    for (int i = 1; i < n; i++) rank[sa[i]] = i;
    for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
      for (k &&k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++)
        ;
  }
};
