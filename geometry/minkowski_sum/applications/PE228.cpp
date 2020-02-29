// Problem: https://projecteuler.net/problem=228
// Solution: Simply generate the polygons described and find the mikowski sum

#include "../convex_mikowski_sum.cpp"

typedef long double ld;
typedef point<ld> P;

//gera poligonos descritos no problema
vector<P> pol(int n){
    vector<P> ans;
    ld PI = acosl(-1);

    for(int i = 1; i <= n; i++)
        ans.push_back(P(cosl((2*i - 1)/(ld)n*PI), sinl((2*i - 1)/(ld)n*PI))*((ld)100));

    return ans;
}

int main(){
    int ini = 1864, end = 1909;

    vector<P> ans = pol(ini);

    for(int i = ini + 1; i <= end; i++)
        ans = convex_minkowski_sum(ans, pol(i));

    cout << sz(ans) << endl;
}