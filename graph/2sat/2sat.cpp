
#include "../../contest/header.hpp"
/*
        2-SAT O(N + E):
                Calculates a valid assignment to boolean variables a, b,
   c,... to a 2-SAT problem, so that an expression of the type (a || b)
                && (!a || c) && (d || !b) && ...
                becomes true, or reports that it is unsatisfiable.

        Constraints:
                Variables are labeled form 0 to n-1.

        Usage:
                Negated variables are represented by bit-inversions (~x).

        Usage sample:
                two_sat ts(number of boolean variables);
                ts.either(0, ~3); // Var 0 is true or var 3 is false
                ts.set_true(2); // Var 2 is true
                ts.set_true(~0); // Var 0 is false
                ts.at_most_one({0,~1,2}); // <= 1 of vars 0, ~1 and 2 are
   true ts.solve(); // Returns true iff it is solvable ts.values[0..N-1]
   holds the assigned values to the vars

        Source: https://github.com/kth-competitive-programming/kactl/blob/
                        master/content/graph/2sat.h
*/
struct two_sat {
  int n;
  vector<vector<int>> graph;
  vector<int> values;  // 0 = false, 1 = true
  two_sat(int n = 0) : n(n), graph(2 * n) {}
  // a || b.
  void either(int a, int b) {
    a = max(2 * a, -1 - 2 * a);
    b = max(2 * b, -1 - 2 * b);
    graph[a].push_back(b ^ 1);
    graph[b].push_back(a ^ 1);
  }
  // x == true.
  void set_true(int x) { either(x, x); }  // (optional)
  int add_var()                           // (optional)
  {
    graph.emplace_back();
    graph.emplace_back();
    return n++;
  }
  // Zero or one of variables in the list must be true.
  // This will create auxiliary variables.
  void at_most_one(const vector<int> &li)  // (optional)
  {
    if (sz(li) <= 1) return;
    int cur = ~li[0];
    for (int i = 2; i < sz(li); i++) {
      int next = add_var();
      either(cur, ~li[i]);
      either(cur, next);
      either(~li[i], next);
      cur = ~next;
    }
    either(cur, ~li[1]);
  }
  vector<int> val, comp, z;
  int time = 0;
  int dfs(int i) {
    int low = (val[i] = ++time), x;
    z.push_back(i);
    for (int e : graph[i])
      if (!comp[e]) low = min(low, val[e] ? val[e] : dfs(e));
    if (low == val[i]) {
      do {
        x = z.back();
        z.pop_back();
        comp[x] = low;
        if (values[x >> 1] == -1) values[x >> 1] = x & 1;
      } while (x != i);
    }
    return val[i] = low;
  }
  // Returns true if solution exists and values[0..n-1] holds the
  // assigned values to the vars.
  bool solve() {
    values.assign(n, -1);
    val.assign(2 * n, 0);
    comp = val;
    for (int i = 0; i < 2 * n; i++)
      if (!comp[i]) dfs(i);
    for (int i = 0; i < n; i++)
      if (comp[2 * i] == comp[2 * i + 1]) return false;
    return true;
  }
};
