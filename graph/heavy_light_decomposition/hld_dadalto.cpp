#include "../../contest/header.hpp"

/*
	Heavy Light Decomposition:
		Splits a tree in a set of vertex disjoint heavy paths such
		that each path from a node to the root passes at most log(n)
		different heavy paths.
		This allows data structures to be implement with queries and
		updates on tree paths in log(n) * data_structure_time.
	
	Usage:
		Create the struct passing a tree root (a), the number of
		vertices (n) and the graph. Tested with 1 <= a <= n, but
		should work with 0 <= a <= n.

		The data structure DS class should implement single element
		updates or range updates as needed and range queries
		according to the form defined in update, update_path and
		query_path.
		DS should also have a constructor specifying the size
		and should support operations in range [0, size - 1].
		IMPORTANT: DS should handle empty queries [x + 1, x].
		IMPORTANT: function applied in DS should be commutative
		and associative. (If not commutative, check out application
		for GSS7)

		VALUES_IN_VERTICES indicates if the tree values are in vertices
		or in edges. In case of edges, update(v, value)
		should be called for the downward vertex of each edge.

		See application for more information.
 
	Source: adapted from codeforces blog (https://codeforces.com/blog/
										  entry/22072).
*/

template <class DS, bool VALUES_IN_VERTICES> // DS for data structure.
											 // Values in vertices,
											 // true or false.
struct heavy_light
{
	vector<int> p, heavy, h; // parent, heavy child of vertex,
							 // height of vertex.

	vector<int> num;		 // number of vertex (in an order where
							 // paths are contiguos intervals).

	vector<int> root;		 // root of heavy path of a given vertex.
	DS ds;

	template <class G>
	heavy_light(int a, int n, const G &graph) : p(n + 1), heavy(n + 1, -1), h(n + 1), num(n + 1), root(n + 1), ds(n + 1)
	{
		p[a] = a;
		h[a] = 0;
		dfs(graph, a);
		for (int i = 0, id = 0; i <= n; ++i)
			if (heavy[p[i]] != i) // parent of the root is itself,
								  // so this works.
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
};
