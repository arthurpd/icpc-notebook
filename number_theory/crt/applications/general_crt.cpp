// https://open.kattis.com/problems/generalchineseremainder
#include "../crt.cpp"

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        ll rem[2], mod[2];
        scanf("%lld%lld%lld%lld", &rem[0], &mod[0], &rem[1], &mod[1]);
        ll lcm = (mod[0] * mod[1]) / __gcd(mod[0], mod[1]);
        ll ans = crt(rem[0], mod[0], rem[1], mod[1]);
        if (ans != -1)
        {
            printf("%lld %lld\n", ans, lcm);
        }
        else
            printf("no solution\n");
    }
}