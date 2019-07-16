#include "../../contest/header.hpp"

/*
	BIT: element update, range sum query in O(log(n) * log(m)). This can also be generalized for 3d.
	Represents a matrix of elements in range [1 ... n][1 ... m].
*/

template <class T>
struct bit2d
{
	int n, m;
	vector<vector<T>> val;
	bit2d(int _n, int _m) : n(_n), m(_m), val(_n + 1, vector<T>(_m + 1, 0)) {}

	// val[i][j] += x
	void update(int r, int c, T x)
	{
		for (int i = r; i <= n; i += -i & i)
			for (int j = c; j <= m; j += -j & j)
				val[i][j] += x;
	}

	// sum of positions (1 ... r, 1 ... c)
	T query(int r, int c)
	{
		T retv = 0;
		for (int i = r; i > 0; i -= -i & i)
			for (int j = c; j > 0; j -= -j & j)
				retv += val[i][j];
		return retv;
	}

	// sum of positions (ri ... rf, ci ... cf). (1 <= ri <= rf <= n) and (1 <= ci <= cf <= m). TODO: test me.
	T query_rect(int ri, int ci, int rf, int cf)
	{
		return query(rf, cf) - query(rf, ci - 1) - query(ri - 1, cf) + query(ri - 1, ci - 1);
	}
};
