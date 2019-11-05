#include "../../contest/header.hpp"

/*
	Mo's Algorithm:
		Solve Q interval queries on a sequence of N values offline
		in O(N * sqrt(Q) * max(insertion time, removal time)).
	
	Usage:
		Queries are defined by closed intervals 
			[l, r] (1 <= l <= r <= n).
		add(i) must add i-th element to your data structure 
			(1 <= i <= n).
		remove(i) must remove the i-th element (1 <= i <= n).
		output(id) should answer query with given id using current 
		state.

	Author: Arthur Pratti Dadalto
*/

struct query {
	int l, r, id;
};

template<class F>
void mos(int n, vector<query> q, const F &add, const F &remove, const F &output)
{
	int bsize = 1 + n / sqrt(sz(q));
	sort(q.begin(), q.end(), [&](const query &lhs, const query &rhs) {
        if (lhs.l / bsize != rhs.l / bsize) 
            return lhs.l < rhs.l;
        if ((lhs.l / bsize) & 1)
            return (lhs.r > rhs.r);     
        return (lhs.r < rhs.r);    
	});

	int l = 1, r = 0; // int l = 0, r = -1; (if indices starts at 0)
	for (int i = 0; i < sz(q); i++)
	{
		while (l > q[i].l)
			add(--l);
		while (r < q[i].r)
			add(++r);
		while (l < q[i].l)
			remove(l++);
		while (r > q[i].r)
			remove(r--);

		output(q[i].id);
	}
}
