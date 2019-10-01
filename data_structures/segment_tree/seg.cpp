#include "../../contest/header.hpp"

/*
	Segment Tree:
		Point update and range query in O(log(n))
		Given as an example using maximum.

	Usage:
		Only valid if all numbers are >= 0.
*/

#define left(i) ((i) << 1)
#define right(i) (((i) << 1) + 1)

struct segtree
{
	vector<int> val;
	int n;

	segtree(int n) : val(4 * (n + 1), 0), n(n) {}

	void update(int id, int l, int r, int a, int x)
	{
		if (l == r)
			val[id] = x;
		else
		{
			int mid = (l + r) / 2;
			if (a <= mid)
				update(left(id), l, mid, a, x);
			else
				update(right(id), mid + 1, r, a, x);

			val[id] = max(val[left(id)], val[right(id)]);
		}
	}

	int get(int id, int l, int r, int a, int b)
	{
		if (l == a && r == b)
			return val[id];
		else
		{
			int mid = (l + r) / 2;
			if (b <= mid)
				return get(left(id), l, mid, a, b);
			else if (a > mid)
				return get(right(id), mid + 1, r, a, b);
			else
				return max(get(left(id), l, mid, a, mid), get(right(id), mid + 1, r, mid + 1, b));
		}
	}

	int get(int a, int b)
	{
		if (a > b)
			return 0;
		return get(1, 0, n - 1, a, b);
	}

	void update(int a, int x)
	{
		update(1, 0, n - 1, a, x);
	}
};
