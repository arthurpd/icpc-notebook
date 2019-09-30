// https://codeforces.com/gym/100962
#include "../mos_tree_edge_query.cpp"

#define MAXN 112345
#define MAXQ 112345

vector<int> graph[MAXN];
vector<int> cost[MAXN];

int x[MAXN];
int ans[MAXQ];
int freq[MAXN];
int val[MAXN];

#define SQN 300

void add(int a)
{
	if (++freq[x[a]] == 1)
	{
		val[x[a] / SQN]++;
	}
}

void remove(int a)
{
	if (--freq[x[a]] == 0)
		val[x[a] / SQN]--;
}

void output(int k)
{
	for (int i = 0; ; i++)
		if (val[i] != SQN)
		{
			for (int j = i * SQN; ; j++)
				if (freq[j] == 0)
				{
					ans[k] = j;
					return;
				}
		}
}

void dfs(int a, int p)
{
	for (int i = 0; i < sz(graph[a]); i++)
		if (graph[a][i] != p)
		{
			dfs(graph[a][i], a);
			x[graph[a][i]] = cost[a][i];
		}
}

int main(void)
{
	int n, m, a, b, c;
	scanf("%d %d", &n, &m);

	unordered_set<int> s;
	vector<tuple<int,int,int>> e(n-1);
	for (int i = 0; i < n - 1; i++)	
	{
		scanf("%d %d %d", &a, &b, &c);
		e[i] = {a, b, c};
		s.insert(c);
	}

	int first;
	for (first = 0; s.find(first) != s.end(); first++)
	{
	}

	for (int i = 0; i < n - 1; i++)	
	{
		tie(a, b, c) = e[i];
		graph[a].push_back(b);
		cost[a].push_back(min(first + 1, c));
		graph[b].push_back(a);
		cost[b].push_back(min(first + 1, c));
	}

	int root = (rand() % n) + 1;

	dfs(root, root);

	vector<pii> q(m);
	for (int i = 0; i < m; i++)
		scanf("%d %d", &q[i].first, &q[i].second);

	mos_tree(root, n, q, graph, add, remove, output);

	for (int i = 0; i < sz(q); i++)
		printf("%d\n", ans[i]);
}
