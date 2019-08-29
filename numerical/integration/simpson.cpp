/*
	Numerical Integration:
		Given a function f and an interval [a, b] estimates integral of f(x) dx from a to b.
		Error is in theory inversely proportional to n^4.

	Usage:
		n, the number of intervals must be even.
	
	Author: Arthur Pratti Dadalto
*/

template <class F>
double simpsons(const F &f, int n /* even */, double a, double b)
{
	double retv = f(a) + f(b);
	double h = (b - a) / n;
	for (int i = 1; i < n; i += 2)
		retv += 4 * f(a + i * h);
	for (int i = 2; i < n; i += 2)
		retv += 2 * f(a + i * h);

	retv *= h / 3;
	return retv;
}

// Sample usage:
// int main(void)
// {
// 	printf("%.20lf\n", simpsons([](double x) { return pow(sin(M_PI * x / 2.0), 3.2);}, 2000, 0, 2));
// }
