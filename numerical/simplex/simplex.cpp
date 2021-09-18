#include "../../contest/header.hpp"
/*
        Simplex:
                Optimizes a linear program of the form:
                        maximize c*x, s.t. a*x <ops> b, x >= 0.
                Each constraint can use a different operator from {<= >=
   ==}. Not polynomial, but got AC 150 ms with 4000 constraints and 200
   variables.

        Usage:
                Call run_simplex, with the number of constraints and
                variables, a, b, ops and c (as specified above).
                Return value is ok if solution was found, unbounded if
                objective value can be infinitely large
                or infeasible if there is no solution given the
   constraints.

                The value of each variable is returned in vector res.
                Objective function optimal value is also returned.
                Sample usage is commented below.

        Author: Arthur Pratti Dadalto
*/
template <class T>
struct vec : vector<T> {
  vec(int n) : vector<T>(n) {}
  // c = a*x + b*y
  static void linear_comb(const vec &a, T x, const vec &b, T y, vec &c) {
    for (int i = 0; i < sz(a); i++) c[i] = a[i] * x + b[i] * y;
  }
};
template <class T>
struct mat : vector<vec<T>> {
  // Creates a zero-filled matrix of n rows and m columns.
  mat(int n, int m) : vector<vec<T>>(n, vec<T>(m)) {}
  // Erase row O(n^2).
  void erase_row(int i) { this->erase(this->begin() + i); }
  // Erase column O(n^2).
  void erase_col(int j) {
    for (int i = 0; i < sz(*this); i++)
      (*this)[i].erase((*this)[i].begin() + j);
  }
};
namespace simplex {
// Any value within [-EPS, +EPS] will be considered equal to 0.
const double EPS = 1e-6;
enum op { ge, le, eq };
enum optimization_status { ok, unbouded, infeasible };
int get_entering_var(mat<double> &tab) {
  // Get first non-artificial variable with negative objective
  // coeficient. If none, return -1. (could instead return most
  // negative, but that could cycle)
  for (int i = 0; i < sz(tab[0]) - 1; i++)
    if (tab[0][i] < -EPS) return i;
  return -1;
}
int get_exiting_var_row(mat<double> &tab, int entering_var) {
  // Get smallest value of val and first in case of tie. If none,
  // return -1.
  int retv = -1;
  double val = -1.0;
  for (int i = 1; i < sz(tab); i++) {
    // If strictly positive, it bounds the entering var.
    if (tab[i][entering_var] > EPS) {
      // Entering var will be bounded by
      // tab[i][tab.size().second - 1] / tab[i][entering_var].
      // val could be slightly negative if
      //   tab[i][tab.size().second - 1] = -0.
      if (val == -1.0 ||
          tab[i][sz(tab[i]) - 1] / tab[i][entering_var] < val) {
        val = tab[i][sz(tab[i]) - 1] / tab[i][entering_var];
        retv = i;
      }
    }
  }
  return retv;
}
optimization_status solve_tab(mat<double> &tab, vector<int> &basic_var) {
  // artificial_count is the number of variables at the end we
  // should ignore.
  int entering_var;
  while ((entering_var = get_entering_var(tab)) != -1) {
    int exiting_var_row = get_exiting_var_row(tab, entering_var);
    // If no exiting variable bounds the entering variable, the
    // objective is unbounded.
    if (exiting_var_row == -1) return optimization_status::unbouded;
    // Set new basic var coeficient to 1.
    vec<double>::linear_comb(
        tab[exiting_var_row], (1.0 / tab[exiting_var_row][entering_var]),
        tab[exiting_var_row], 0.0, tab[exiting_var_row]);
    // Gaussian elimination of the other rows.
    for (int i = 0; i < sz(tab); i++)
      if (i != exiting_var_row)
        if (abs(tab[i][entering_var]) > EPS)
          vec<double>::linear_comb(tab[i], 1.0, tab[exiting_var_row],
                                   -tab[i][entering_var], tab[i]);
    basic_var[exiting_var_row] = entering_var;
  }
  return optimization_status::ok;
}
// maximize c*x, s.t. a*x <ops> b. x >= 0.
optimization_status run_simplex(int num_constraints, int num_vars,
                                mat<double> a, vec<op> ops, vec<double> b,
                                vec<double> c, vec<double> &res,
                                double &obj_val) {
  for (int i = 0; i < num_constraints; i++)
    if (ops[i] == op::ge) {
      // Beyond this point "ge" constraints won't exist.
      vec<double>::linear_comb(a[i], -1, a[i], 0, a[i]);  // a[i] *= -1;
      b[i] *= -1;
      ops[i] = op::le;
    }
  int num_artificial_variables = 0;
  int num_slack_variables = 0;
  for (int i = 0; i < num_constraints; i++) {
    if (ops[i] == op::le) {
      num_slack_variables++;
    }
    if ((ops[i] == op::le && b[i] < -EPS) || ops[i] == op::eq) {
      // If we have rhs strictly negative in a inequality or an
      // equality constraint, we need an artificial val.
      num_artificial_variables++;
    }
  }
  mat<double> tab(num_constraints + 1, num_vars + num_slack_variables +
                                           num_artificial_variables + 1);
  vector<int> basic_var(num_constraints + 1);
  vector<int> slack_cols, artificial_cols;
  for (int i = num_vars; i < num_vars + num_slack_variables; i++)
    slack_cols.push_back(i);
  for (int i = num_vars + num_slack_variables;
       i < num_vars + num_slack_variables + num_artificial_variables; i++)
    artificial_cols.push_back(i);
  int rhs_col = num_vars + num_slack_variables + num_artificial_variables;
  // First objective will be to have artificial variables equal to 0
  for (int i : artificial_cols) tab[0][i] = 1;
  for (int i = 0, k = 0, l = 0; i < num_constraints; i++) {
    for (int j = 0; j < num_vars; j++) tab[i + 1][j] = a[i][j];
    if (ops[i] == op::le) tab[i + 1][slack_cols[l++]] = 1;
    tab[i + 1][rhs_col] = b[i];
    if ((ops[i] == op::le && b[i] < -EPS) || ops[i] == op::eq) {
      // Basic var will be artificial
      if (b[i] < -EPS)
        vec<double>::linear_comb(tab[i + 1], -1, tab[i + 1], 0,
                                 tab[i + 1]);  // a[i] *= -1;
      tab[i + 1][artificial_cols[k++]] = 1;
      basic_var[i + 1] = artificial_cols[k - 1];
      vec<double>::linear_comb(tab[0], 1.0, tab[i + 1], -1.0, tab[0]);
    } else  // Basic var will be slack var.
    {
      basic_var[i + 1] = slack_cols[l - 1];
    }
  }
  assert(solve_tab(tab, basic_var) == optimization_status::ok);
  // Best solution could not bring artificial variables to 0
  // (objective max Z = sum(-xa)).
  if (tab[0][sz(tab[0]) - 1] < -EPS)
    return optimization_status::infeasible;
  // If we have an artificial variable on the base with xb = 0, we
  // need to remove it.
  for (int i = 1; i < sz(basic_var); i++)
    if (basic_var[i] >= num_vars + num_slack_variables) {
      // Find non-artificial replacement.
      for (int j = 0; j < sz(tab[i]) - 1 - num_artificial_variables; j++) {
        // If non-zero value in row, we can replace.
        if (j != basic_var[i] && abs(tab[i][j]) > EPS) {
          // Remove from the other rows.
          vec<double>::linear_comb(tab[i], 1.0 / tab[i][j], tab[i], 0,
                                   tab[i]);
          for (int k = 0; k < sz(tab); k++)
            if (k != i) {
              if (abs(tab[k][j]) > EPS)
                vec<double>::linear_comb(tab[k], 1, tab[i], -tab[k][j],
                                         tab[k]);
            }
          // Basic variable replacemente done, so proceed to
          // next basic_var.
          basic_var[i] = j;
          break;
        }
      }
    }
  for (int i = sz(tab) - 1; i > 0; i--)
    if (basic_var[i] >= num_vars + num_slack_variables) {
      // Could not replace basic var, so constraint is redundant
      tab.erase_row(i);
      basic_var.erase(basic_var.begin() + i);
    }
  // Remove artificial variable columns.
  for (int i = sz(artificial_cols) - 1; i >= 0; i--)
    tab.erase_col(artificial_cols[i]);
  for (int i = 0; i < sz(tab[0]); i++) tab[0][i] = 0;
  for (int i = 0; i < num_vars; i++) tab[0][i] = -c[i];
  for (int i = 1; i < sz(tab); i++)
    vec<double>::linear_comb(tab[0], 1, tab[i], -tab[0][basic_var[i]],
                             tab[0]);
  optimization_status status = solve_tab(tab, basic_var);
  res = vec<double>(num_vars);
  for (int i = 1; i < sz(basic_var); i++)
    if (basic_var[i] < num_vars)
      res[basic_var[i]] = tab[i][sz(tab[i]) - 1];
  obj_val = tab[0][sz(tab[0]) - 1];
  return status;
}
}  // namespace simplex
/*
int main(void)
{
        int n, m;
        cin >> n >> m;

        int num_constraints = m, num_vars = n;

        // maximize c*x, s.t. a*x <ops> b. x >= 0.
        mat<double> a(num_constraints, num_vars);
        vec<double> b(num_constraints);
        vec<simplex::op> ops(num_constraints);
        vec<double> c(num_vars);
        vec<double> res(num_vars);

        for (int i = 0; i < n; i++)
                cin >> c[i];

        for (int i = 0; i < m; i++)
        {
                int l, r, x;
                cin >> l >> r >> x;
                for (int j = l - 1; j <= r - 1; j++)
                        a[i][j] = 1;
                b[i] = x;
                ops[i] = simplex::op::le;
        }

        double ans;
        simplex::run_simplex(num_constraints, num_vars, a, ops, b, c, res,
ans);

        cout << ((long long)(ans + 0.5)) << endl;
}
*/
