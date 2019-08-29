/*
 * https://codeforces.com/gym/102299/problem/G 
 */

#include <bits/stdc++.h>
using namespace std;
 
#define MAXN 112345
#define inf 0x3f3f3f3f
 
#define ll long long
#define pb push_back
 
typedef vector<ll> vll;
typedef vector<int> vi;
 
#define MAX 100010
#define MAXLOG 19
 
vector<vi> adj;
 
int subsize[MAXN], parent[MAXN];
int chainNo = 0, chainHead[MAXN], chainPos[MAXN], chainInd[MAXN], chainSize[MAXN];
set<pair<int, int> > sets[MAXN];
int p[MAXN];
int h[MAXN];
 
bool hasBoss[MAXN];
 
void hld(int cur){
	if(chainHead[chainNo] == -1)
		chainHead[chainNo] = cur;
	
	chainInd[cur] = chainNo;
	chainPos[cur] = chainSize[chainNo];
	chainSize[chainNo]++;
	
	int ind  = -1, mai = -1;
	for(int i = 0; i < (int)adj[cur].size(); i++){
		if(adj[cur][i] != parent[cur] && subsize[adj[cur][i]] > mai){
			mai = subsize[adj[cur][i]];
			ind = i;
		}
	}
	
	if(ind >= 0)
		hld(adj[cur][ind]);
		
	for(int i = 0; i < (int)adj[cur].size(); i++)
		if(adj[cur][i] != parent[cur] && i != ind){
			chainNo++;
			hld(adj[cur][i]);
		}
}
 
int dfs0(int pos, int prev = -1){
	int res = 1;
	if(prev != -1){
		h[pos] = h[prev] + 1;
	}
	for(int i = 0; i < (int)adj[pos].size(); i++){
		int nx = adj[pos][i];
		if(nx != prev){
			res += dfs0(nx, pos);
			parent[nx] = pos;
		}
	}
	return subsize[pos] = res;
}
 
int query_up(int u){
	int uchain = chainInd[u];
	
	if(sets[uchain].empty() || (*(sets[uchain].begin())).first > chainPos[u]){
		u = chainHead[uchain];
		u = parent[u];
		if(u == -1)
			return -1;
		return query_up(u);
	}
	
	set<pair<int, int> > :: iterator it = sets[uchain].upper_bound({chainPos[u], 9999999});
	
	it--;
	
	return (*it).second;
}
 
void update(int u){
	int uchain = chainInd[u];
	sets[uchain].insert({chainPos[u], u});
}
 
struct query{
	char type;
	
	int par;
	
	query(){}
	
	query(char t, int p){
		type = t;
		par = p;
	}
};
 
vector<query> queries;
 
int up[MAXN][MAXLOG];
int upmin[MAXN][MAXLOG];
 
int main(void)
{
	memset(chainHead, -1, sizeof(chainHead));
	memset(parent, -1, sizeof(parent));
	
	int n, m;
	
	scanf("%d %d", &n, &m);
	
	adj.resize(n);
	
	for(int i = 0; i < n; i++)
		scanf("%d", &p[i]);
	
	for(int i = 0; i < m; i++){
		char c;
		scanf(" %c", &c);
		
		if(c == '+'){
			int a, b;
			scanf("%d %d", &a, &b);
			a--;
			b--;
			adj[a].pb(b);
			adj[b].pb(a);
			hasBoss[b] = 1;
			queries.pb(query('+', b));
		}
		
		else{
			int a;
			scanf("%d", &a);
			a--;
			queries.pb(query('?', a));
		}
	}
	
	int fBoss = -1;
	for(int i = 0; i < n; i++){
		if(hasBoss[i] == 0){
			if(fBoss == -1)
				fBoss = i;
			else{
				adj[i].pb(fBoss);
				adj[fBoss].pb(i);
				queries.pb(query('+', i));
			}
		}
	}
	
	dfs0(fBoss);
	hld(fBoss);
	
	for (int i = 0; i < n; i++)
	{
		up[i][0] = parent[i];
		upmin[i][0] = p[i];
	}
 
	up[fBoss][0] = fBoss;
	
	for (int j = 1; j < MAXLOG; j++)
		for (int i = 0; i < n; i++)
		{
			up[i][j] = up[up[i][j-1]][j-1];
			upmin[i][j] = min(upmin[i][j-1], upmin[up[i][j-1]][j-1]);
		}
	
	
	vector<int> res;
	for(int i = queries.size() - 1; i >= 0; i--){
		if(queries[i].type == '+'){
			update(queries[i].par);
		}
		
		else{
			int pos = queries[i].par;
			int zeroParent = query_up(pos);
			if (zeroParent == -1)
				zeroParent = fBoss;
 
			int height = h[zeroParent];
			
			int ans = p[zeroParent];
			int cur = pos;
			for (int j = MAXLOG - 1; j >= 0; j--)
			{
				if (h[up[cur][j]] >= height)
				{
					ans = min(ans, upmin[cur][j]);
					cur = up[cur][j];
				}
			}
			res.push_back(ans);
		}
	}
	
	for (int i = (int) res.size() - 1; i >= 0; i--)
		printf("%d\n", res[i]);
}
