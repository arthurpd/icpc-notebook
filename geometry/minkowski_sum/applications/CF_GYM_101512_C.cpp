/*
    Problem: C from https://codeforces.com/gym/101512
*/

#include "../convex_mikowski_sum.cpp"

typedef long long ll;
typedef point<ll> P;

int main(){
    ios::sync_with_stdio(false);
    
    int t;
    cin >> t;
    
    while(t--){
        int n;
        cin >> n;

        vector<P> v(n), u1, u2;

        for(int i = 0; i < n; i++)
            cin >> v[i].x >> v[i].y;

        u1 = CH(v);
        for(int i = 0; i < sz(u1); i++)
            u2.push_back(u1[i]*(-1));
        
        v = convex_minkowski_sum(u1, u2);

        int j = 0;

        ll mx = 0;

        for(int i = 0; i < sz(v); i++){
            while(v[i].cross(v[(j + 1)%sz(v)]) > v[i].cross(v[j]))
                j = (j + 1)%sz(v);
            
            mx = max(mx, v[i].cross(v[j]));
        }

        if(mx%2)
            cout << mx/2 << ".5" << endl;
        else
            cout << mx/2 << endl;
    }
}