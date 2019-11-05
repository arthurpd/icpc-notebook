// https://www.spoj.com/problems/DCEPC13D/
#include "../../../../number_theory/factor/pollardrho.cpp"
#include "../../../../number_theory/crt/crt_system.cpp"
#include "../lucas.cpp"

vector<ll> fact[51];
ll m[51];
ll a[51];

void calc()
{
    for (int p = 2; p < 51; p++)
    {
        fact[p].resize(51);
        if (isPrime(p))
        {
            fact[p][0] = fact[p][1] = 1;
            for (int i = 2; i < 51; i++)
            {
                fact[p][i] = (fact[p][i - 1] * (i % p)) % p;
            }
        }
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    calc();
    while (t--)
    {
        ll M, R, N;
        scanf("%lld%lld%lld", &N, &R, &M);
        auto factors = factorize(M);

        for (int i = 0; i < sz(factors); i++)
        {
            a[i] = chooseModP(N, R, factors[i], fact[factors[i]]);
            m[i] = factors[i];
        }

        printf("%lld\n", crt_system(a, m, sz(factors)));
    }
}