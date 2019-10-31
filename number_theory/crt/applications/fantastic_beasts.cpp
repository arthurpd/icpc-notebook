// https://www.urionlinejudge.com.br/judge/pt/problems/view/2908
#include "../crt_system.cpp"

#define MAXB 11
#define MAXZ 112

int B, Z;
int curr_pos[MAXB];
int next_pos[MAXB][MAXZ];
ll a[MAXZ][MAXB], m[MAXZ][MAXB];

int main()
{
    scanf("%d%d", &B, &Z);
    for (int i = 0; i < B; i++)
    {
        scanf("%d", &curr_pos[i]);
        --curr_pos[i];
        for (int j = 0; j < Z; j++)
        {
            scanf("%d", &next_pos[i][j]);
            --next_pos[i][j];
        }
    }

    int time;
    for (time = 0; time < 300; time++)
    {
        if (count(curr_pos, curr_pos + B, curr_pos[0]) == B)
        {
            return !printf("%d %d\n", curr_pos[0] + 1, time);
        }

        for (int i = 0; i < B; i++)
        {
            curr_pos[i] = next_pos[i][curr_pos[i]];
        }
    }

    vi possible_zoo(Z, 1);

    for (int i = 0; i < B; i++)
    {
        vi vis(Z, -1);
        int cycle_sz = 0;

        while (vis[curr_pos[i]] == -1)
        {
            vis[curr_pos[i]] = cycle_sz;
            cycle_sz++;
            curr_pos[i] = next_pos[i][curr_pos[i]];
        }

        for (int j = 0; j < Z; j++)
        {
            if (vis[j] == -1)
            {
                possible_zoo[j] = 0;
            }
            else
            {
                a[j][i] = vis[j];
                m[j][i] = cycle_sz;
            }
        }
    }

    ll best = 2 * infll;
    int best_zoo;
    for (int i = 0; i < Z; i++)
    {
        if (possible_zoo[i])
        {
            ll x = crt_system(a[i], m[i], B);
            if (x != -1)
            {
                if (x < best)
                {
                    best = x;
                    best_zoo = i;
                }
            }
        }
    }

    if (best == 2 * infll)
        printf("*\n");
    else
        printf("%d %lld\n", best_zoo + 1, best + time);
}