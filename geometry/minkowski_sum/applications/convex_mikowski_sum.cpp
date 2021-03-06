/*
    
*/

#include "../../contest/header.hpp"

template <class T>
vector<point<T>> convex_minkowski_sum(vector<point<T>> a, vector<point<T>> b){
    auto cmp = [&](point<T> a, point<T> b){
        if(abs(a.x - b.x) > (T)EPS)
            return a.x < b.x;
        return a.y < b.y;
    };
    
    vector<point<T>> ans;

    int i0 = 0, j0 = 0;

    for(int k = 0; k < sz(a); k++)
        if(cmp(a[k], a[i0]))
            i0 = k;
    
    for(int k = 0; k < sz(b); k++)
        if(cmp(b[k], b[j0]))
            j0 = k;

    int i = i0, j = j0;

    do{
        ans.push_back(a[i] + b[j]);

        int new_j = (j + 1)%sz(b);
        int new_i = (i + 1)%sz(a);

        T cross = (a[new_i] - a[i]).cross(b[new_j] - b[j]);

        if(cross > (T)EPS)
            i = new_i;
        else if(cross < (T)-EPS)
            j = new_j;
        else{
            j = new_j;
            i = new_i;
        }
    }while(i != i0 || j != j0);

    return ans;
}