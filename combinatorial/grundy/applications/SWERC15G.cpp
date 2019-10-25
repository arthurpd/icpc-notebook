/*Problem G from https://codeforces.com/gym/101128*/

#include <bits/stdc++.h>
using namespace std;
 
int p, k;
 
vector<int> v;
 
int mex(vector<int> a){
	for(int i = 0; i < a.size(); i++){
		while(a[i] < a.size() && a[a[i]] != a[i])
			swap(a[a[i]], a[i]);
	}
	for(int i = 0; i < a.size(); i++)
		if(a[i] != i)
			return i;
	
	return a.size();
}
 
int grundy(){
	vector<int> g(v.size());
 
	for(int i = v.size() - 1; i >= 0; i--){
		vector<int> rea;
		for(int j = 0; j <= min(k, (int)v.size() - 1 - i); j++){
			if(i + j < v.size() && i + j + v[i + j] <= v.size()){
				if(i + j + v[i + j] == v.size())
					rea.push_back(0);
				else
					rea.push_back(g[i + j + v[i + j]]);
			}
		}
 
		g[i] = mex(rea);
	}
 
	return g[0];
}
 
int main(void)
{
	
	scanf("%d %d", &p, &k);
	int res = 0;
	for(int i = 0; i < p; i++){
		int n;
		scanf("%d", &n);
		v.clear();
		for(int j = 0; j < n; j++){
			int x;
			scanf("%d", &x);
			v.push_back(x);
		}
		reverse(v.begin(), v.end());
		res ^= grundy();
	}
 
	if(res == 0)
		printf("Bob will win.\n");
	else
		printf("Alice can win.\n");
}
