// https://codeforces.com/gym/101554/problem/H

#include "../2d.cpp"

#define point point<ll>

struct segment_id : public segment<ll>
{
	int id;

	bool operator<(const segment_id &rhs) const
	{
		if (pi.x <= rhs.pi.x && rhs.pi.x <= pf.x)
			return pi.cross(pf, rhs.pi) > 0;
		else if (pi.x <= rhs.pf.x && rhs.pf.x <= pf.x)
			return pi.cross(pf, rhs.pf) > 0;
		else
			return rhs.pi.cross(rhs.pf, pi) < 0;
	}
};

struct event
{
	ll x, y;
	int id, tp;

	bool operator<(const event &rhs) const
	{
		return make_tuple(x, tp, -y) < make_tuple(rhs.x, rhs.tp, -rhs.y);
	}
};

int main(void)
{
 	cin.sync_with_stdio(0);
 	cin.tie(0);

	int n;
	cin >> n;
	vector<segment_id> s(n);
	for (int i = 0; i < n; i++)
	{
		cin >> s[i].pi.x >> s[i].pi.y >> s[i].pf.x >> s[i].pf.y;
		s[i].id = i;
		if (s[i].pf < s[i].pi)
			swap(s[i].pi, s[i].pf);
	}

	ll x_ball;
	int ball_first_seg;
	cin >> x_ball;

	vector<int> prox_seg(n);
	vector<event> e;
	e.push_back({x_ball, 10000000ll, -1, 1});

	for (int i = 0; i < n; i++)
	{
		e.push_back({s[i].pi.x, s[i].pi.y, i, 0});
		e.push_back({s[i].pf.x, s[i].pf.y, i, 2});
	}

	sort(e.begin(), e.end());
	set<segment_id> cur;
	for (int i = 0; i < sz(e); i++)
	{
		if (e[i].tp == 0)
		{
			if (s[e[i].id].pi.y < s[e[i].id].pf.y)
			{
				auto it = cur.lower_bound(s[e[i].id]);
				if (it != cur.begin())
					prox_seg[e[i].id] = (--it)->id;
				else
					prox_seg[e[i].id] = -1;
			}

			cur.insert(s[e[i].id]);
		}
		else if (e[i].tp == 2)
		{
			cur.erase(s[e[i].id]);

			if (s[e[i].id].pf.y < s[e[i].id].pi.y)
			{
				auto it = cur.lower_bound(s[e[i].id]);
				if (it != cur.begin())
					prox_seg[e[i].id] = (--it)->id;
				else
					prox_seg[e[i].id] = -1;
			}
		}
		else
		{
			auto it = cur.rbegin();
			if (it != cur.rend())
				ball_first_seg = it->id;
			else
				ball_first_seg = -1;
		}
	}

	// debug(ball_first_seg);
	// debug(prox_seg);

	ll ans = x_ball;
	for (int i = ball_first_seg; i != -1; i = prox_seg[i])
	{
		ans = (s[i].pi.y < s[i].pf.y ? s[i].pi.x : s[i].pf.x);
	}

	cout << ans << endl;
}
