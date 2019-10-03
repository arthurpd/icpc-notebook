#include "../../contest/header.hpp"

struct union_find
{
	vector<int> p, size;
	union_find(int n) : p(n), size(n, 1)
	{
		iota(p.begin(), p.end(), 0);
	}

	int find(int a)
	{
		return (p[a] == a) ? a : (p[a] = find(p[a]));
	}

	void join(int a, int b)
	{
		a = find(a);
		b = find(b);
		if (a == b)
			return;
		if (size[a] < size[b])
			swap(a, b);
		p[b] = a;
		size[a] += size[b];
	}
};

