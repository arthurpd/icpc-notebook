/*
	Solution for convex hull problem (minimum polygon covering a set of points) based on ordering ponts by angle.
	* Finds the subset of points in the convex hull in O(Nlog(N)).
	* This version works if you either want intermediary points in segments or not (see comments delimited by //)
	* This version works when all points are collinear
	* This version works for repeated points if you add a label to struct, and use this label in overloaded +, - and =.
	
	Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/contest/template.cpp
*/

#include<bits/stdc++.h>

typedef long long ll;

using namespace std;

template<typename T>
struct point
{
	typedef point<T> P;
	T x, y;

	explicit point(T x = 0, T y = 0) : x(x), y(y) {}
	//Double version: bool operator<(P p) const { return  fabs(x - p.x) < EPS ? y < p.y : x < p.x; }
	bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
	//Double version: bool operator==(P p) const { return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS; }
	bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
	P operator+(P p) const { return P(x + p.x, y + p.y); }
	T dist2() const { return x*x + y*y; }
	P operator-(P p) const { return P(x - p.x, y - p.y); }
	T dot(P p) const { return x * p.x + y * p.y; }
	T cross(P p) const { return x * p.y - y * p.x; }
	T cross(P a, P b) const { return (a - *this).cross(b - *this); }
	long double dist() const { return sqrt((long double)dist2()); } 					 
};

/*Compara primeiro por angulo em relacao a origem e depois por distancia para a origem*/
template<typename T>
bool cmp(point<T> a, point<T> b){
	if(a.cross(b) != 0)
		return a.cross(b) > 0;
	return a.dist2() < b.dist2();
}

template<typename T>
vector<point<T> > CH(vector<point<T> > points){
	/*Encontra pivo (ponto extremos que com ctz faz parte do CH)*/
	point<T> pivot = points[0];
	for(auto p : points)
		pivot = min(pivot, p); 
	
	/*Desloca conjunto para pivo ficar na origem e ordena potos pelo angulo e distancia do pivo*/
	for(int i = 0; i < (int) points.size(); i++)
		points[i] = points[i] - pivot;
		
	sort(points.begin(), points.end(), cmp<ll>);
	
	for(int i = 0; i < (int) points.size(); i++)
		points[i] = points[i] + pivot;

	/*Ponto extra para fechar o poligono*/
	points.push_back(points[0]);
	
	vector<point<T> > ch;
	
	for(auto p : points){
		/*Enquanto o proximo ponto gera uma curva para a direita, retira ultimo ponto atual*/
		/*Segunda comparação serve para caso especial de pontos colineares quando se quer eliminar os intermediarios*/
		//Trocar terceira comparacao pra <= para discartar pontos do meio de arestas no ch
		//Double: trocar terceira comparação por < EPS (descarta pontos em arestas) ou < -EPS (mantem pinto em aresta
		while(ch.size() > 1 && !(p == ch[ch.size() - 2]) && ch[ch.size() - 2].cross(ch[ch.size() - 1] , p) < 0)
			ch.pop_back();
		ch.push_back(p);
	}
	
	/*Elimina ponto extra*/
	ch.pop_back();
		
	return ch;
}

int main(){
	int n;
	scanf("%d", &n);
	vector<point<ll> > p(n);
	
	/*Le poligono*/
	for(int i = 0; i < n; i++)
		scanf("%lld %lld", &p[i].x, &p[i].y);
	
	/*Encontra CH*/
	vector<point<ll> > ch = CH(p);
	
	/*Imorime resultado*/
	printf("%d\n", (int)ch.size());
	for(int i = 0; i < (int)ch.size(); i++)
		printf("%d% %d\n", ch[i].x, ch[i].y);
	
}
