#include "../../contest/header.hpp"

/*
	Segment tree with dynamic memory allocation and arbitrary interval.
		Every operation is O(log(r-l))
		Uses O(min(r-l, n*log(r-l)) memory, where n is the number of insertions. 

	Constraints:
		Segment tree range [l, r] must be such that 0 <= l <= r.

	Author: Arthur Pratti Dadalto
*/

template<class T>
struct node
{
	T val;
	node *left, *right;

	T get(int l, int r, int a, int b)
	{
		if (l == a && r == b)
			return val;
		int mid = (l + 0ll + r) / 2;
		if (b <= mid)
			return left ? left->get(l, mid, a, b) : 0;
		else if (a > mid)
			return right ? right->get(mid + 1, r, a, b) : 0;
		else
			return (left ? left->get(l, mid, a, mid) : 0) + (right ? right->get(mid + 1, r, mid + 1, b) : 0);		
	}

	void update(int l, int r, int a, T x)
	{
		if (l == r)
			val = x;
		else
		{
			int mid = (l + 0ll + r) / 2;
			if (a <= mid)
				(left ? left : (left = new node()))->update(l, mid, a, x);
			else
				(right ? right : (right = new node()))->update(mid + 1, r, a, x);
			
			val = (left ? left->val : 0) + (right ? right->val : 0);
		}
	}
};

