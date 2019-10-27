// https://www.spoj.com/problems/ELASTIC/

#include<bits/stdc++.h>
#include "../2d.cpp"

using namespace std;

#define point point<double>
#define circle circle<double>
#define segment segment<double>
#define line line<double>

vector<vector<int> > adj;
vector<vector<double> > weight;
bool vis[3123];

priority_queue<pair<double, int> > pq;

void process(int x){
	vis[x] = 1;
	for(int i = 0; i < (int)adj[x].size(); i++){
		int nx = adj[x][i];
		double w = weight[x][i];
		
		if(vis[nx] == 0){
			pq.push({-w, nx});
		}
	}
}

double angle(point a, point o, point b){
	return abs((a - o).angle(b - o));
}

int main(){
	
	int n;
	
	scanf("%d", &n);
	while(1){
		if(n == -1)
			break;
			
		vector<circle> c(n);
		
		for(int i = 0; i < n; i++)
			scanf("%lf %lf %lf", &c[i].center.x, &c[i].center.y, &c[i].r); 
		
		adj.clear();
		adj.resize(n);
		weight.clear();
		weight.resize(n);
		
		for(int i = 0; i < n; i++)
			for(int j = i + 1; j < n; j++){
				pair<point, point> pi, pj;
				c[i].outter_tangents(c[j], pi, pj);
				double val = 0;
				double angi = abs(angle(pi.first, c[i].center, pi.second));
				double angj = abs(angle(pj.first, c[j].center, pj.second));
				
				//printf("%lf %lf\n", angi*360/(2*acos(-1)), angj*360/(2*acos(-1))); 
				
				if(c[i].r < c[j].r){
					val += c[i].r*min(angi, 2*acos(-1) - angi);
					val += c[j].r*max(angj, 2*acos(-1) - angj);
				}
				else{
					val += c[i].r*max(angi, 2*acos(-1) - angi);
					val += c[j].r*min(angj, 2*acos(-1) - angj);
				}
				
				//printf("vala: %lf\n", val);

				val += (pi.first - pj.first).dist() + (pi.second - pj.second).dist();
				
				assert(!isnan(val));
			
				adj[i].push_back(j);
				weight[i].push_back(val);
					
				adj[j].push_back(i);
				weight[j].push_back(val);
			}
			
		memset(vis, 0, sizeof(vis));
		
		process(0);
		
		double res = 0;
		
		while(!pq.empty()){
			int at = pq.top().second;
			double w = -pq.top().first;
			pq.pop();
			
			if(vis[at] == 0){
				vis[at] = 1;
				res += w;
				process(at);
			}
		}
		
		printf("%.3lf\n", res);
		
		scanf("%d", &n);
	}
	return 0;
}
