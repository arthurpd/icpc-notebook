// http://www.spoj.com/problems/MATCHING/

#include "../hopcroft_karp.cpp"
#include <bits/stdc++.h>
using namespace std;

int main(void)
{
	int a, b, c, m, l, r;
	scanf("%d %d %d", &l, &r, &m);
	hopcroft::init(l, r);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &a, &b);
		hopcroft::graph[a].push_back(b + l);
	}

	cout << hopcroft::hopcroft() << endl;
}
