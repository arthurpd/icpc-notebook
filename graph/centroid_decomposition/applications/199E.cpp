// https://codeforces.com/contest/342/problem/E

#include "../centroid.cpp"
#include "../../lca/lca.cpp"

/*
	BIT: element update, range sum query and sum lower_bound in O(log(N)).
	Represents an array of elements in range [1, N].
*/

template <class T>
struct bit
{
	int n, LOGN;
	vector<T> val;
	bit(int _n = 0) : n(_n), LOGN(log2(n + 1)), val(_n + 1, 0) {}

	// val[pos] += x
	void update(int pos, T x)
	{
		for (int i = pos; i <= n; i += -i & i)
			val[i] += x;
	}

	// sum of range [1, pos]
	T query(int pos)
	{
		T retv = 0;
		for (int i = pos; i > 0; i -= -i & i)
			retv += val[i];
		return retv;
	}

	// min pos such that sum of [1, pos] >= sum, or n + 1 if none exists.
	int lower_bound(T x)
	{
		T sum = 0;
		int pos = 0;

		for (int i = LOGN; i >= 0; i--)
			if (pos + (1 << i) <= n && sum + val[pos + (1 << i)] < x)
				sum += val[pos += (1 << i)];

		return pos + 1; // pos will have position of largest value less than x.
	}
};

int par[MAXN];
bit<int> ans[MAXN]; // Using BIT as a multiset for reasons.

void dfs(int a, int p, int c, int l, int &mh)
{
	mh = max(mh, l);
	par[a] = c;

	for (int i = 0; i < sz(graph[a]); i++)
		if (graph[a][i] != p && !block[graph[a][i]])
			dfs(graph[a][i], a, c, l + 1, mh);
}

void process(int a, int sz)
{
	int mh = 1;
	for (int i = 0; i < sz(graph[a]); i++)
		if (!block[graph[a][i]])
			dfs(graph[a][i], a, a, 1, mh);

	ans[a] = bit<int>(mh + 1);
}

int cnt_ans[MAXN];
bool color[MAXN];

void toggle(int a, lca_preprocess &lca)
{
	color[a] = !color[a];
	for (int v = a; v != 0; v = par[v])
		if (color[a])
		{	
			cnt_ans[v]++;
			ans[v].update(lca.dist(a, v) + 1, 1);
		}
		else
		{	
			cnt_ans[v]--;
			ans[v].update(lca.dist(a, v) + 1, -1);
		}
}

int get_ans(int a, lca_preprocess &lca)
{
	int retv = inf;
	for (int v = a; v != 0; v = par[v])
		if (cnt_ans[v])
			retv = min(retv, ans[v].lower_bound(1) - 1 + lca.dist(a, v));

	return retv;
}

int main(void)
{
	int n, m, a, b;
	scanf("%d %d", &n, &m);
	for (int i = 0; i + 1 < n; i++)
	{
		scanf("%d %d", &a, &b);
		put_edge(a, b);
	}

	decomp(1, n);

	lca_preprocess lca(1, n, graph);

	toggle(1, lca);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &a, &b);
		if (a == 1)
			toggle(b, lca);
		else
		{
			int x = get_ans(b, lca);
			printf("%d\n", (x == inf ? -1 : x));
		}
	}
}
