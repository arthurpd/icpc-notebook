/*
	Ternary Search:
		Finds x such that f(x) is minimum in range [bot, top] in 
		O(lg((top - bot) / eps)). 
		Value is correct within the specified precision eps.

	Constraints:
		f(x) is strictly decreasing for some interval [bot, x1], 
		constant in an interval [x1, x2]
		and strictly increasing in a interval [x2, top]. x1 <= x2 are 
		arbitrary values where [x1, x2] is a plateau of optimal 
		solutions.

	Usage:
		Call the function passing a lambda expression or function f.
		If there are multiple possible solutions, assume that an 
		arbitrary one in the plateau is returned.
	
	Author: Arthur Pratti Dadalto
*/

template <typename F>
double ternary_search(const F &f, double bot = -1e9, double top = 1e9, double eps = 1e-9)
{
	while (top - bot > eps)
	{
		double x1 = (0.55*bot + 0.45*top); // (2*bot + top) / 3 is 
		 								  // more stable, but slower.
		double x2 = (0.45*bot + 0.55*top);
		if (f(x1) > f(x2))
			bot = x1;
		else
			top = x2;
	}

	return (bot + top) / 2;
}
