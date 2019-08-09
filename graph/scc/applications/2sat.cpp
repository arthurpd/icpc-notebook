// http://br.spoj.com/problems/CARDAPIO/

#include "../scc.cpp"

// x || y must be true
// Make graph ~x -> y, ~y -> x
// There is a solution if x and ~x are no in the same scc.

vector<int> graph[4123];
 
char s1[51], s2[51];
int a[1123], b[1123];
int neg[4123];

int
main(void)
{
	int n, t = 1;
	while(scanf("%d", &n) != EOF)
	{
		map<string,int> hash;
		for(int i = 0; i < 4123; i++)
			graph[i].clear();
		
		memset(neg, 0, sizeof(neg));
		int id = 1;
		
		for(int i = 0; i < n; i++)
		{
			scanf(" %s %s", s1, s2);
			if(hash[s1] == 0)
				hash[s1] = id++;
			if(hash[s2] == 0)
				hash[s2] = id++;
			a[i] = hash[s1], b[i] = hash[s2];
		}
		string no = "!";
		map<string,int> hash2 = hash;
		for(map<string,int>::iterator it = hash.begin(); it != hash.end(); it++)
			if((it->first)[0] != '!')
				neg[neg[it->second] = hash2[no + it->first]] = it->second;
		
		for(int i = 0; i < n; i++)
		{
			if(neg[a[i]] != 0)
				graph[neg[a[i]]].push_back(b[i]);
			if(neg[b[i]] != 0)
				graph[neg[b[i]]].push_back(a[i]);
		}
		
        scc_decomp rdm(id - 1, graph);
        debug(rdm.scc);

		bool ans = true;
		for(int i = 1; i < id; i++)
//			printf("%d\n", scc[i]);
			if(rdm.scc[neg[i]] == rdm.scc[i])
				 ans = false;
		
		printf("Instancia %d\n%s\n\n", t++, ans ? "sim" : "nao");
		
	}
}
