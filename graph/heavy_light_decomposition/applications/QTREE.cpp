/*
 * Problema de encontrar aresta com menor valor em arvore (incluindo updates)
 * https://www.spoj.com/problems/QTREE/
 * */

#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back

typedef vector<ll> vll;
typedef vector<int> vi;


#define MAXN 100010
#define INF 2000000000
#define MAXLOG 20

//Vetores LCA
int h[MAXN];
int par[MAXN][MAXLOG];

//Vetor que guarda valores das segs
class segtree{
public:
	vector<int> tree;
	int spam;
	
	segtree(vector<int> &a){
		tree.resize(4*a.size() + 5);
		spam = a.size() - 1;
		this->build(1, 0, spam, a);
	}
	
	void build(int node, int left, int right, vector<int> &a){
		if(left == right){
			tree[node] = a[left];
			return;
		}
		
		int mid = (left + right)/2;
		
		build(2*node, left, mid, a);
		build(2*node + 1, mid + 1, right, a);
		
		tree[node] = max(tree[2*node], tree[2*node + 1]);
	}
	
	void update(int pos, int val, int node = 1, int left = -1, int right = -1){
		if(left == -1){
			left = 0;
			right = spam;
		}
		
		if(left == right){
			tree[node] = val;
			return;
		}
		
		int mid = (left + right)/2;
		
		if(pos <= mid)
			update(pos, val, 2*node, left, mid);
		
		else
			update(pos, val, 2*node + 1, mid + 1, right);
		
		tree[node] = max(tree[2*node], tree[2*node + 1]);
	}
	
	int query(int posL, int posR, int node = 1, int left = -1, int right = -1){
		
		if(left == -1){
			left = 0;
			right = spam;
		}
		
		if(posL > right || posR < left)
			return -INF;
		
		if(posL <= left && posR >= right)
			return tree[node];
		
		int mid = (left + right)/2;
		
		return max(query(posL, posR, 2*node, left, mid), query(posL, posR, 2*node + 1, mid + 1, right));
	}
	
};

vector<segtree> segs;

//Vetor que guarda a arvore
vector<vi> adj;

int subsize[MAXN], parent[MAXN], chainPos[MAXN], chainInd[MAXN];
//Começar com zero
int chainNo = 0, chainSize[MAXN];
//Começar com -1
int chainHead[MAXN];

void hld(int cur){
	//Seta variaveis do segmento 
	if(chainHead[chainNo] == -1)
		chainHead[chainNo] = cur;
		
	chainInd[cur] = chainNo;
	chainPos[cur] = chainSize[chainNo];
	chainSize[chainNo]++;
	
	//Encontra maior subarvore
	int ind = -1, mai = -1;
	for(int i = 0; i < (int)adj[cur].size(); i++){
		if(adj[cur][i] != parent[cur] && subsize[adj[cur][i]] > mai){
			mai = subsize[adj[cur][i]];
			ind  = i;
		}
	}
	
	//Continua segmento atual
	if(ind >= 0)
		hld(adj[cur][ind]);
	
	//Gera novos segmentos
	for(int i = 0; i < (int)adj[cur].size(); i++)
		if(adj[cur][i] != parent[cur] && i != ind){
			chainNo++;
			hld(adj[cur][i]);
		}
}

//garantir que v eh pai de u!! (Por ex com LCA)
int query_up(int u, int v){
	int uchain = chainInd[u], vchain = chainInd[v];
	int ans = -INF;
	while(1){
		//Query termina no segmento atual
		if(uchain == vchain){
			ans = max(ans, segs[uchain].query(chainPos[v], chainPos[u]));
			break;
		}
		
		ans = max(ans, segs[uchain].query(0, chainPos[u]));
		
		//Query sobe para proximo segmento
		u = chainHead[uchain];
		u = parent[u];
		uchain = chainInd[u];
	}
	
	return ans;
}

int dfs0(int pos, int prev = -1){
	int res  = 1;
	for(int i = 0; i < (int)adj[pos].size(); i++){
		int nx  = adj[pos][i];
		if(nx != prev){
			res += dfs0(nx, pos);
			parent[nx] = pos;
		}
	}
	return subsize[pos] = res;
}

void dfs(int v,int p = -1){
	par[v][0] = p;
	if(p + 1)
		h[v] = h[p] + 1;
	for(int i = 1;i < MAXLOG;i ++)
		if(par[v][i-1] + 1)
			par[v][i] = par[par[v][i-1]][i-1];
	for(auto u : adj[v])	if(p - u)
		dfs(u,v);
}

int LCA(int v,int u){
	if(h[v] < h[u])
		swap(v,u);
	for(int i = MAXLOG - 1;i >= 0;i --)
		if(par[v][i] + 1 and h[par[v][i]] >= h[u])
			v = par[v][i];

	if(v == u)
		return v;
	for(int i = MAXLOG - 1;i >= 0;i --)
		if(par[v][i] - par[u][i])
			v = par[v][i], u = par[u][i];
	return par[v][0];
}

int main()
{
	int t;
	
	scanf("%d", &t);
	
	while(t--){
		int n;
		scanf("%d", &n);
		adj.clear();
		adj.resize(n);
		
		vector<pair<int, int> > in(n);
		vector<int> w(n), ed(n); 
		
		for(int i = 0; i < n - 1; i++){
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			a--;
			b--;
			adj[a].pb(b);
			adj[b].pb(a);
			in[i] = {a, b};
			w[i] = c;
		}
		
		//Inicializa estrutura de dados
		memset(chainHead, -1, sizeof(chainHead));
		memset(par, -1, sizeof(par));
			
		dfs(0);
		dfs0(0);
		hld(0);
	
		for(int i = 0; i < n - 1; i++){
			if(parent[in[i].first] == in[i].second)
				ed[i] = in[i].first;
			else
				ed[i] = in[i].second;
		}
		
		vector<vector<int> > hldSegs(chainNo + 1);
		
		for(int i = 0; i <= chainNo; i++){
			hldSegs[i].resize(chainSize[i]);
		}
		
		for(int i = 0; i < n - 1; i++){
			int j = ed[i];
			hldSegs[chainInd[j]][chainPos[j]] = w[i];
		}
		
		segs.clear();
		for(int i = 0; i <= chainNo; i++){
			segs.push_back(segtree(hldSegs[i]));
		}
		
		char s[10];
		
		do{
			scanf(" %s", s);

			if(strcmp(s, "QUERY") == 0){
				int a, b;
				scanf("%d %d", &a, &b);
				a--;b--;
				int u = LCA(a, b);
				int val = segs[chainInd[u]].query(chainPos[u], chainPos[u]);
				segs[chainInd[u]].update(chainPos[u], -INF);
				printf("%d\n", max(query_up(a, u), query_up(b, u)));	
				
				segs[chainInd[u]].update(chainPos[u], val);			
			}
			
			else if(strcmp(s, "CHANGE") == 0){
				int i, ti;
				scanf("%d %d", &i, &ti);
				i--;
				int vrt = ed[i];
				
				segs[chainInd[vrt]].update(chainPos[vrt], ti);
			}
			else
				break;
		}while(1);
	
	}
	
	//Inicializar estruturas usadas
}
