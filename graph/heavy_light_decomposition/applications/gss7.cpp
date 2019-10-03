// https://www.spoj.com/problems/GSS7/
#include "../../../contest/header.hpp"

template <class DS, bool VALUES_IN_VERTICES> // DS for data structure. Values in vertices, true or false.
struct heavy_light
{
	vector<int> p, heavy, h; // parent, heavy child of vertex, height of vertex.
	vector<int> num;		 // number of vertex (in an order where paths are contiguos intervals).
	vector<int> root;		 // root of heavy path of a given vertex.
	DS ds;

	template <class G>
	heavy_light(int a, int n, const G &graph) : p(n + 1), heavy(n + 1, -1), h(n + 1), num(n + 1), root(n + 1), ds(n + 1)
	{
		p[a] = a;
		h[a] = 0;
		dfs(graph, a);
		for (int i = 0, id = 0; i <= n; ++i)
			if (heavy[p[i]] != i) // parent of the root is itself, so this works.
				for (int j = i; j != -1; j = heavy[j])
				{
					root[j] = i;
					num[j] = id++;
				}
	}

	template <class G>
	int dfs(const G &graph, int a)
	{
		int size = 1, max_subtree = 0;
		for (int u : graph[a])
			if (u != p[a])
			{
				p[u] = a;
				h[u] = h[a] + 1;
				int subtree = dfs(graph, u);
				if (subtree > max_subtree)
					heavy[a] = u, max_subtree = subtree;
				size += subtree;
			}
		return size;
	}

	template <class BO> // BO for binary_operation
	void process_path(int u, int v, BO op)
	{
		for (; root[u] != root[v]; v = p[root[v]])
		{
			if (h[root[u]] > h[root[v]])
				swap(u, v);
			op(num[root[v]], num[v]);
		}
		if (h[u] > h[v])
			swap(u, v);
		op(num[u] + (VALUES_IN_VERTICES ? 0 : 1), num[v]);
	}

	template <class T>
	void update(int v, const T &value)
	{
		ds.update(num[v], value);
	}

	template <class T>
	T query(int v)
	{
		return ds.get(num[v], num[v]);
	}

	template <class T>
	void update_path(int u, int v, const T &value)
	{
		process_path(u, v, [this, &value](int l, int r) { ds.update(l, r, value); });
	}

	template <class T, class F>
	T query_path(int u, int v, T res /* initial value */, F join /* join value with query result */)
	{
		process_path(u, v, [this, &res, &join](int l, int r) { res = join(res, ds.get(l, r)); });
		return res;
	}

	int lca(int u, int v)
	{
		for (; root[u] != root[v]; v = p[root[v]])
		{
			if (h[root[u]] > h[root[v]])
				swap(u, v);
		}

		if (h[u] > h[v])
			swap(u, v);

		return u;
	}

	// Given that u is on the path from v to the root and u != v,
	// returns the child of u which is on the path u->v.
	int prev(int u, int v)
	{
		int retv = v;
		for (; root[u] != root[v]; v = p[root[v]])
		{
			retv = root[v];
		}

		if (u == v)
			return retv;

		return heavy[u];
	}
};

#define left(i) ((i) << 1)
#define right(i) (((i) << 1) + 1)

struct csum
{
	int pref, gen, suf, tot;
};

csum join(csum l, csum r)
{
	return {max(l.pref, l.tot + r.pref), max(max(l.gen, r.gen), l.suf + r.pref), max(r.suf, r.tot + l.suf), l.tot + r.tot};
}

struct segtree
{
	vector<csum> val;
	vector<int> delta;
	int n;

	segtree(int n) : val(4 * (n + 1), {0, 0, 0, 0}), delta(4 * (n + 1), -inf), n(n)
	{
	}

	void prop(int id, int l, int r)
	{
		if (delta[id] != -inf)
		{
			if (l != r)
			{
				delta[left(id)] = delta[id];
				delta[right(id)] = delta[id];
			}

			val[id].suf = val[id].pref = val[id].gen = max(0, (r - l + 1) * delta[id]);
			val[id].tot = (r - l + 1) * delta[id];
			delta[id] = -inf;
		}
	}

	void update(int id, int l, int r, int a, int b, int x)
	{
		if (a == l && b == r)
		{
			delta[id] = x;
			prop(id, l, r);
		}
		else
		{
			prop(id, l, r);
			int mid = (l + r) / 2;
			if (b <= mid)
			{
				update(left(id), l, mid, a, b, x);
				prop(right(id), mid + 1, r);
			}
			else if (a > mid)
			{
				update(right(id), mid + 1, r, a, b, x);
				prop(left(id), l, mid);
			}
			else
			{
				update(left(id), l, mid, a, mid, x);
				update(right(id), mid + 1, r, mid + 1, b, x);
			}

			val[id] = join(val[left(id)], val[right(id)]);
		}
	}

	// Get the minimum value in range [a, b].
	csum get(int id, int l, int r, int a, int b)
	{
		prop(id, l, r);
		if (a == l && b == r)
			return val[id];
		else
		{
			int mid = (l + r) / 2;
			if (b <= mid)
				return get(left(id), l, mid, a, b);
			else if (a > mid)
				return get(right(id), mid + 1, r, a, b);
			else
				return join(get(left(id), l, mid, a, mid), get(right(id), mid + 1, r, mid + 1, b));
		}
	}

	void update(int a, int b, int x)
	{
		return update(1, 0, n - 1, a, b, x);
	}

	csum get(int a, int b)
	{
		return get(1, 0, n - 1, a, b);
	}
};

int main(void)
{
	int n, q, a, b, c;
	scanf("%d", &n);
	vector<vector<int>> graph(n + 1);
	vector<int> v(n + 1, -1);
	for (int i = 1; i <= n; i++)
		scanf("%d", &v[i]);

	for (int i = 0; i < n - 1; i++)
	{
		scanf("%d %d", &a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	heavy_light<segtree, true> hld(1, n, graph);
	for (int i = 1; i <= n; i++)
		hld.update_path(i, i, v[i]);

	scanf("%d", &q);
	for (int i = 0; i < q; i++)
	{
		int tp;
		scanf("%d", &tp);
		if (tp == 2)
		{
			scanf("%d %d %d", &a, &b, &c);
			hld.update_path(a, b, c);
		}
		else
		{
			scanf("%d %d", &a, &b);
			if (hld.h[a] > hld.h[b])
				swap(a, b);

			if (a == b)
			{
				printf("%d\n", hld.query_path(a, b, (csum) {0,0,0,0}, [](csum prev, csum cur) { return join(cur, prev); }).gen);
			}
			else
			{
				csum l = {0,0,0,0};
				csum r = {0,0,0,0};
				int lca = hld.lca(a, b);
				int prev = hld.prev(lca, b);
				l = hld.query_path(a, lca, l, [](csum prev, csum cur) { return join(cur, prev); });
				r = hld.query_path(prev, b, r, [](csum prev, csum cur) { return join(cur, prev); });

				swap(l.pref, l.suf);
				printf("%d\n", join(l, r).gen);
			}
		}
	}
}
