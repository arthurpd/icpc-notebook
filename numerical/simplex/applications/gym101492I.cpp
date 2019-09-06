// https://codeforces.com/gym/101492/problem/I

#include "../simplex.cpp"

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
	simplex::run_simplex(num_constraints, num_vars, a, ops, b, c, res, ans);

	cout << ((long long)(ans + 0.5)) << endl;
}
