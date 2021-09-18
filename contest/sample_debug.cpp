#include "header.hpp"
int main(void) {
  int a = 11, b = 12, c = 13;
  vector<vector<int>> v = {{a, b}, {c}, {0, 1}};
  set<int> s = {a, b};
  map<double, int> m;
  m[2.5] = 2;
  m[-3.1] = 3;
  map<string, int> tab;
  tab["abc"] = (int)'a' + 'b' + 'c';
  tab["abz"] = (int)'a' + 'b' + 'z';
  int array[3] = {1, 2, 5};
  debug(a, b, c);
  debug(v);
  debug(s, m);
  debug(tab);
  debug(array);  // This one does not work.
}
