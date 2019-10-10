#include "../transitive_closure.cpp"

#define MAXN 312
#define MAXK 1123

bitset<MAXN> graph[MAXN];
vector<pii> doc[MAXK];
vector<int> l[MAXN][MAXN];
int doc_done[MAXK];
int n = 0;

int main()
{
	cin.sync_with_stdio(0);
	cin.tie(0);

	map<string, int> rdm;
	int a, b;
	string s1, s2;

	cin >> s1 >> s2;
	rdm[s1] = ++n;
	rdm[s2] = ++n;
	tie(a, b) = {rdm[s1], rdm[s2]};

	graph[a][b] = 1;

	int k = 0, m;
	cin >> k;
	for (int i = 0; i < k; i++)
	{
		cin >> m;
		while (m--)
		{
			cin >> s1 >> s2;
			if (rdm[s1] == 0)
				rdm[s1] = ++n;

			if (rdm[s2] == 0)
				rdm[s2] = ++n;
			tie(a, b) = {rdm[s1], rdm[s2]};

			doc[i].push_back({a, b});
			l[a][b].push_back(i);
		}
	}

	transitive_closure<MAXN> t(graph);

	bool ans = true;
	while (ans)
	{
		int cur = -1;
		for (int i = 1; cur == -1 && i <= n; i++)
			for (int j = 1; cur == -1 && j <= n; j++)
				if (t.closure[i][j] && !l[i][j].empty())
				{
					int tmp = l[i][j].back();
					l[i][j].pop_back();
					if (!doc_done[tmp])
						cur = tmp;
					else
						j--;					
				}
		
		if (cur == -1)
			break;
		
		doc_done[cur] = true;
		for (int i = 0; i < doc[cur].size(); i++)
			graph[doc[cur][i].first][doc[cur][i].second] = 1;

		t = transitive_closure<MAXN>(graph);

		for (int i = 1; i <= n; i++)
			if (t.closure[i][i])
				ans = false;
	}

	cout << (ans ? "Yes" : "No") << endl;
}
