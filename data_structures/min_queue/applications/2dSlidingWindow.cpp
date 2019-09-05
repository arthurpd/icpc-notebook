#include <bits/stdc++.h>
 
using namespace std;
#define pb push_back
#define db(x) //cerr << #x << " = " << x << endl;
#define INF 0x3f3f3f3
#define fi first
#define se second
#define ll long long
#define vi vector<int>
#define vll vector<ll>
#define all(x) x.begin(), x.end()

#define MAXN 3123 
 
ll G[MAXN*MAXN];
ll g0;
ll X, Y, Z;
ll grid[MAXN][MAXN];
ll grid_min[MAXN][MAXN];
ll N, M, A, B;

struct min_queue
{
	queue<ll> q;
	deque<ll> s;
	
	int size()
	{
		return (int)q.size();
	}
	
	void push(ll val)
	{
		while (!s.empty() && s.back() > val)
			s.pop_back();
		s.push_back(val);
		
		q.push(val);
	}
	
	void pop()
	{
		ll u = q.front();
		q.pop();
		
		if (!s.empty() && s.front() == u)
			s.pop_front();
	}
	
	ll get_min()
	{
		return s.front();
	}
	
};

void calc_G()
{
	G[0] = g0;
	for (int i = 1; i < MAXN*MAXN; i++)
	{
		G[i] = (G[i - 1] * X + Y) % Z;
	}
}

int main()
{
	scanf("%lld%lld%lld%lld", &N, &M, &A, &B);
	scanf("%lld%lld%lld%lld", &g0, &X, &Y, &Z);
	calc_G();
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			grid[i][j] = G[(i - 1) * M + j - 1];
		}
	}
	
	// pre-calc min_grid
	for (int i = 1; i <= N; i++)
	{
		min_queue mq;
		for (int j = 1; j <= M; j++)
		{
			mq.push(grid[i][j]);
			if (mq.size() > B)
			{
				mq.pop();
			}
			ll m = mq.get_min();
			grid_min[i][j - B + 1] = m;
		}
	}
	
	// 1D sliding window in each column as an independent array
	ll res = 0;
	for (int j = 1; j + B - 1 <= M; j++)
	{
		min_queue mq;
		for (int i = 1; i <= N; i++)
		{
			mq.push(grid_min[i][j]);
			if (mq.size() > A)
				mq.pop();
			if (mq.size() == A)
				res += mq.get_min();
		}
	}
	
	printf("%lld\n", res);
}
