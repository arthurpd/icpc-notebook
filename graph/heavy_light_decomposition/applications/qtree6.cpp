// https://www.spoj.com/problems/QTREE6/
#include "../hld_dadalto.cpp"

int cur_color = 0;

struct data_s
{
	set<pii> s[2];

	data_s(int n) {}

	int get(int a, int b)
	{
		auto it = s[cur_color ^ 1].upper_bound(pii(b, inf));
		if (it != s[cur_color ^ 1].begin() && (--it)->first >= a)
		{
			it = s[cur_color].lower_bound(pii(it->first, -1));
			if (it != s[cur_color].end() && it->first <= b)
				return -it->second;
			else
				return 0;
		}
		else
		{
			it = s[cur_color].lower_bound(pii(a, -1));
			if (it != s[cur_color].end() && it->first <= b)
				return it->second;
			else
				assert(false); // Assuming interval is not empty.
		}
	}

	void update(int a, int x)
	{
		if (x > 0)
		{
			s[0].insert(pii(a, x));
			s[1].erase(pii(a, x));
		}
		else
		{
			s[0].erase(pii(a, -x));
			s[1].insert(pii(a, -x));
		}
	}
};

#define left(i) ((i) << 1)
#define right(i) (((i) << 1) + 1)

struct segtree
{
	vector<int> val;
	int n;

	segtree(int n) : val(4 * (n + 1), 0), n(n) {}

	// Sum x in all elements in range [a, b].
	void update(int id, int l, int r, int a, int b, int x)
	{
		if (a == l && b == r)
		{
			val[id] += x;
		}
		else
		{
			int mid = (l + r) / 2;
			if (b <= mid)
				update(left(id), l, mid, a, b, x);
			else if (a > mid)
				update(right(id), mid + 1, r, a, b, x);
			else
			{
				update(left(id), l, mid, a, mid, x);
				update(right(id), mid + 1, r, mid + 1, b, x);
			}
		}
	}

	int get(int id, int l, int r, int a)
	{
		if (l == r)
			return val[id];
		else
		{
			int mid = (l + r) / 2;
			if (a <= mid)
				return get(left(id), l, mid, a) + val[id];
			else if (a > mid)
				return get(right(id), mid + 1, r, a) + val[id];
		}
	}

	int get(int a, int b)
	{
		assert(a == b);
		return get(1, 0, n - 1, a);
	}

	void update(int a, int b, int x)
	{
		update(1, 0, n - 1, a, b, x);
	}
};

int main(void)
{
	int n, q, a, b;
	scanf("%d", &n);
	vector<vector<int>> graph(n + 1);
	vector<int> v(n + 1, 1);
	for (int i = 0; i < n - 1; i++)
	{
		scanf("%d %d", &a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	heavy_light<data_s, true> hld(1, n, graph);
	for (int i = 1; i <= n; i++)
		hld.update(i, i);

	heavy_light<segtree, true> ws_hld(1, n, graph);
	heavy_light<segtree, true> bs_hld(1, n, graph);

	for (int i = 1; i <= n; i++)
		bs_hld.update_path(1, i, 1);
	for (int i = 1; i <= n; i++)
		ws_hld.update_path(i, i, 1);
		
	scanf("%d", &q);
	for (int i = 0; i < q; i++)
	{
		int x, y;
		scanf("%d %d", &x, &y);
		if (x == 1)
		{
			if (y == 1)
			{
				v[y] *= -1;
				hld.update(y, v[y] * y);
				continue;
			}

			cur_color = (v[y] > 0 ? 0 : 1);
			int first_diff = hld.p[abs(hld.query_path(1, y, y, [](int a, int b) {
				if (a > 0)
				{
					if (b == 0)
						return -a;
					return b;
				}
				return a;
			}))];

			int v1 = ws_hld.query<int>(y);
			int v2 = bs_hld.query<int>(y);

			if (v[y] == -1)
				ws_hld.update_path(hld.p[y], first_diff, -v1);
			else
				bs_hld.update_path(hld.p[y], first_diff, -v2);

			v[y] *= -1;
			hld.update(y, v[y] * y);
			cur_color = (v[y] > 0 ? 0 : 1);
			first_diff = hld.p[abs(hld.query_path(1, y, y, [](int a, int b) {
				if (a > 0)
				{
					if (b == 0)
						return -a;
					return b;
				}
				return a;
			}))];

			if (v[y] == 1)
				bs_hld.update_path(hld.p[y], first_diff, v2);
			else
				ws_hld.update_path(hld.p[y], first_diff, v1);
		}
		else
		{
			cur_color = (v[y] > 0 ? 0 : 1);
			int last_equal = abs(hld.query_path(1, y, y, [](int a, int b) {
				if (a > 0)
				{
					if (b == 0)
						return -a;
					return b;
				}
				return a;
			}));

			// debug(last_equal);
			if (v[y] == -1)
				printf("%d\n", ws_hld.query<int>(last_equal));
			else
				printf("%d\n", bs_hld.query<int>(last_equal));
		}
	}
}
