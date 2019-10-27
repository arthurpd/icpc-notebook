#include "../../contest/header.hpp"

/*
	Closest Pair of points O(n * log n):
		Finds the closest pair of points from a set of given points.

	Usage:
		Call closest_pair with the array of points and the number.
		The function will modify the array.
		Then, get the squared distance from ans and the indexes
		of both points from idx.

	Author: Arthur Pratti Dadalto
*/

#define MAXN 112345

struct point
{
	ll x, y;
	int id;
};

namespace closest_pair
{
point tmp[MAXN];

ll ans = infll;
int idx[2];

void update(point i, point j)
{
	ll dist = (i.x - j.x) * (i.x - j.x) + (i.y - j.y) * (i.y - j.y);
	if (dist < ans)
	{
		ans = dist;
		idx[0] = min(i.id, j.id);
		idx[1] = max(i.id, j.id);
	}
}

bool compx(point a, point b) { return a.x < b.x; }

bool compy(point a, point b) { return a.y < b.y; }

void solve(point p[], int l, int r)
{
	if (r - l <= 3)
	{
		for (int i = l; i <= r; i++)
			for (int j = i + 1; j <= r; j++)
				update(p[i], p[j]);
		sort(p + l, p + r + 1, compy);
		return;
	}

	int mid = (l + r) / 2;
	ll xmid = p[mid].x;

	solve(p, l, mid), solve(p, mid + 1, r);
	merge(p + l, p + mid + 1, p + mid + 1, p + r + 1, tmp, compy);
	copy(tmp, tmp + r - l + 1, p + l);

	int sz = 0;
	for (int i = l; i <= r; i++)
		if ((p[i].x - xmid) * (p[i].x - xmid) < ans)
		{
			for (int j = sz - 1; j >= 0 && (p[i].y - tmp[j].y) * (p[i].y - tmp[j].y) < ans; j--)
				update(p[i], tmp[j]);
			tmp[sz++] = p[i];
		}
}

void closest_pair(point p[], int n)
{
	ans = infll;
	sort(p, p + n, compx);
	solve(p, 0, n - 1);
}
}; // namespace closest_pair

