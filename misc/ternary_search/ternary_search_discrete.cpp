#include "../../contest/header.hpp"
/*
        Ternary Search:
                Finds the smallest x in range [bot, top] such that f(x) is
                maximum in O(lg(top - bot)).

        Constraints:
                f(x) is strictly increasing for some interval [bot, x1],
                constant in an interval [x1, x2] and strictly decreasing in
   a interval [x2, top]. x1 <= x2 are arbitrary values where [x1, x2] is a
   plateau of optimal solutions.

        Usage:
                Call the function passing a lambda expression or function
   f.

        Source: modified from https://github.com/
        kth-competitive-programming/kactl/blob/master/content/
        various/TernarySearch.h
*/
template <typename F>
int ternary_search(const F &f, int bot, int top) {
  while (top - bot >= 5) {
    int mid = (bot + top) / 2;
    if (f(mid) < f(mid + 1))
      bot = mid;
    else
      top = mid + 1;
  }
  for (int i = bot + 1; i <= top; i++)
    if (f(i) > f(bot)) bot = i;
  return bot;
}
