// https://www.spoj.com/problems/GSS8/
#include "../../../contest/header.hpp"

typedef uint32_t ui;

ui pot[200001][11];
ui comb[11][11];

namespace treap
{
struct node
{
	node *l = 0, *r = 0;
	ui val; // Any value associated with node.
	ui tab[11];

	int p;	 // Node heap priority.
	int c = 1; // Node subtree size.
	node(ui val) : val(val), p(rand()) {
		for (int i = 0; i <= 10; i++)
			tab[i] = val;
	}

	void recalc();
};

int cnt(node *n) { return n ? n->c : 0; }

void node::recalc() // To augment with extra data you should mostly add stuff to this function.
{
	c = cnt(l) + cnt(r) + 1;

	ui y = cnt(l) + 1;
	for (int k = 0; k <= 10; k++)
		tab[k] = val * pot[y][k];

	if (l)
		for (int k = 0; k <= 10; k++)
			tab[k] += l->tab[k];

	if (r)
		for (int k = 0; k <= 10; k++)
			for (int i = 0; i <= k; i++)
				tab[k] += r->tab[i] * pot[y][k - i] * comb[k][k - i];
}

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

// Split treap rooted at n in two treaps containing [0, k) and [k, ...)
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
// Also used to insert one node (e.g. root = ins(root, new node(10), 3))
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

// Do a query in range [l, r].
node *query(node *t, int l, int r, int k)
{
	node *a, *b, *c;
	tie(a, b) = split(t, l);
	tie(b, c) = split(b, r - l + 1);

	printf("%u\n", b->tab[k]);

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

int main(void)
{
	for (int i = 0; i <= 10; i++)
		for (ui j = 0; j <= 200000; j++)
		{
			if (i == 0)
				pot[j][i] = 1;
			else
				pot[j][i] = pot[j][i-1] * j;		
		}

	for (int i = 0; i <= 10; i++)
		for (int j = 0; j <= i; j++)
		{
			if (j == 0 || j == i)
				comb[i][j] = 1;
			else
			{
				comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
			}			
		}

	treap::node *root = nullptr;

	int n, q, x, y;
	ui v;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%u", &v);
		root = treap::ins(root, new treap::node(v), i);
	}

	char tp;
	scanf("%d", &q);
	for (int i = 0; i < q; i++)
	{
		scanf(" %c", &tp);
		if (tp == 'I')
		{
			scanf("%d %u", &x, &v);
			root = treap::ins(root, new treap::node(v), x);
		}
		else if (tp == 'D')
		{
			scanf("%d", &x);
			root = treap::rem(root, x);
		}
		else if (tp == 'R')
		{
			scanf("%d %u", &x, &v);
			root = treap::rem(root, x);
			root = treap::ins(root, new treap::node(v), x);
		}
		else
		{
			int k;
			scanf("%d %d %d", &x, &y, &k);
			root = treap::query(root, x, y, k);
		}
	}
}
