#include "../../contest/header.hpp"

/*
	Treap:
		A short self-balancing tree. It acts as a sequential container
		with log-time splits/joins, and is easy to augment with
		additional data.
	
	Time: O(log N) per operation.

	Constraints:
		Acts as a vector of size N, with positions in range [0, N-1].

	Source: https://github.com/kth-competitive-programming/kactl/blob/
			master/content/data-structures/Treap.h

	Usage:
		To insert elements, create one node treaps. 
		(e.g. treap::ins(root, new treap::node(x), i))
		To augment with extra data you should mostly add stuff to the
		recalc function. (e.g. to make it work like a seg tree)
		See applications for more usage examples.
*/

namespace treap
{
struct node
{
	node *l = 0, *r = 0;
	int val;   // Any value associated with node.
	int p;	 // Node heap priority.
	int c = 1; // Node subtree size.
	node(int val) : val(val), p(rand()) {}
	void recalc();
};

int cnt(node *n) { return n ? n->c : 0; }
void node::recalc() { c = cnt(l) + cnt(r) + 1; }

// Apply function f on each tree node in order.
template <class F>
void each(node *n, F f)
{
	if (n)
	{
		each(n->l, f);
		f(n->val);
		each(n->r, f);
	}
}

// Split treap rooted at n in two treaps containing positions [0, k)
// and [k,...)
pair<node *, node *> split(node *n, int k)
{
	if (!n)
		return {NULL, NULL};
	if (cnt(n->l) >= k) // "n->val >= k" for lower_bound(k)
	{
		auto pa = split(n->l, k);
		n->l = pa.second;
		n->recalc();
		return {pa.first, n};
	}
	else
	{
		auto pa = split(n->r, k - cnt(n->l) - 1); // and just "k"
		n->r = pa.first;
		n->recalc();
		return {n, pa.second};
	}
}

// Merge treaps l and r keeping order (l first).
node *merge(node *l, node *r)
{
	if (!l)
		return r;
	if (!r)
		return l;
	if (l->p > r->p)
	{
		l->r = merge(l->r, r);
		l->recalc();
		return l;
	}
	else
	{
		r->l = merge(l, r->l);
		r->recalc();
		return r;
	}
}

// Insert treap rooted at n into position pos of treap rooted at t.
node *ins(node *t, node *n, int pos)
{
	auto pa = split(t, pos);
	return merge(merge(pa.first, n), pa.second);
}

// Remove node at position pos from treap rooted at t.
node *rem(node *t, int pos)
{
	node *a, *b, *c;
	tie(a, b) = split(t, pos);
	tie(b, c) = split(b, 1);

	delete b;
	return merge(a, c);
}

// Example application: do a query in range [l, r].
node *query(node *t, int l, int r)
{
	node *a, *b, *c;
	tie(a, b) = split(t, l);
	tie(b, c) = split(b, r - l + 1);

	// printf("%lld\n", b->tab);

	return merge(merge(a, b), c);
}

// Example application: move the range [l, r) to index k.
void move(node *&t, int l, int r, int k)
{
	node *a, *b, *c;
	tie(a, b) = split(t, l);
	tie(b, c) = split(b, r - l);
	if (k <= l)
		t = merge(ins(a, b, k), c);
	else
		t = merge(a, ins(c, b, k - r));
}
} // namespace treap
