#include "../../contest/header.hpp"

/*
	Merge Sort Tree:
		Build segment tree where each node stores a sorted version
		of the underlying range.
		O(n log n) to build, O(log^2 n) each query (in this case).
		This example uses kth number in interval queries.

	Usage:
		In this example, instead of building the merge sort tree with
		the given vector (e.g. {1, 5, 2, 6, 3, 7, 4}), we sort a
		vector of indices by their value in the vector
		(e.g. {0, 2, 4, 6, 1, 3, 5} for the vector above).

		This way, each node in the tree is responsible for a range of
		sorted elements in the vector and we can ask it how many of
		those have indices in the range [a, b].
*/

#define left(i) ((i) << 1)
#define right(i) (((i) << 1) + 1)

struct merge_sort_tree
{
	vector<int> v; // original vector.
	vector<vector<int>> val;
	vector<int> indices; // indices sorted by value in v.

	merge_sort_tree(vector<int> v) : v(v), val(4 * (sz(v) + 1))
	{
		for (int i = 0; i < sz(v); i++)
			indices.push_back(i);
		sort(all(indices), [&v](int i, int j) { return v[i] < v[j]; });

		build(1, 0, sz(v) - 1);
	}

	void build(int id, int l, int r)
	{
		if (l == r)
			val[id].push_back(indices[l]);
		else
		{
			int mid = (l + r) / 2;
			build(left(id), l, mid), build(right(id), mid + 1, r);
			val[id] = vector<int>(r - l + 1);
			merge(all(val[left(id)]), all(val[right(id)]), val[id].begin());
		}
	}

	// How many elements in this node have indices in the range [a, b]
	int count_interval(int id, int a, int b)
	{
		return (int)(upper_bound(all(val[id]), b) - lower_bound(all(val[id]), a));
	}

	int get(int id, int l, int r, int a, int b, int x)
	{
		if (l == r)
			return v[val[id].back()];
		int mid = (l + r) / 2;
		int lcount = count_interval(left(id), a, b);
		if (lcount >= x)
			return get(left(id), l, mid, a, b, x);
		else
			return get(right(id), mid + 1, r, a, b, x - lcount);
	}

	int kth(int a, int b, int k)
	{
		return get(1, 0, sz(v) - 1, a, b, k);
	}
};
