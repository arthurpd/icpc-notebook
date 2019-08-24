#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back

typedef vector<ll> vll;
typedef vector<int> vi;

#define MAXN 100010

//Vetor que guarda a arvore
vector<vi> adj;

int subsize[MAXN], parent[MAXN];
//Inciar chainHead com -1; e chainSize e chainNo com 0.
int chainNo = 0, chainHead[MAXN], chainPos[MAXN], chainInd[MAXN], chainSize[MAXN];
void hld(int cur){
	if(chainHead[chainNo] == -1)
		chainHead[chainNo] = cur;
		
	chainInd[cur] = chainNo;
	chainPos[cur] = chainSize[chainNo];
	chainSize[chainNo]++;
	
	int ind = -1, mai = -1;
	for(int i = 0; i < (int)adj[cur].size(); i++){
		if(adj[cur][i] != parent[cur] && subsize[adj[cur][i]] > mai){
			mai = subsize[adj[cur][i]];
			ind  = i;
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

//usar LCA para garantir que v eh pai de u!!
ll query_up(int u, int v){
	int uchain = chainInd[u], vchain = chainInd[v];
	ll ans = 0LL;
	
	while(1){
		if(uchain == vchain){
			//Query deve ir de chainPos[i] ate chainPos[v]
			ll cur = /*sum(chainPos[u], uchain) - (chainPos[u] == 0? 0LL : sum(chainPos[v] - 1, vchain))*/;
			ans += cur;
			break;
		}
		
		//Query deve ir de chainPos[i] ate o fim da estrutura 
		//ll cur = sum(chainPos[u], uchain);
		ans += cur;
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

int main()
{
	//Salvar arvore em adj
	
	//Inicializa estrutura de dados
	memset(chainHead, -1, sizeof(chainHead));
	
	//Ou 0, se for o no raiz
	dfs0(1);
	hld(1);
	
	//Inicializar estruturas usadas
}
