// https://www.spoj.com/problems/WORDS1/

#include "../eulertour.cpp"

char aux[1123];

void reset()
{
    for (int i = 0; i < euler::n; i++)
    {
        euler::vertices[i].outs.clear();
        euler::vertices[i].in_degree = 0;
    }
    for (int i = 0; i < euler::m; i++)
    {
        euler::used_edge[i] = false;
    }
    
}

int find_src()
{
	int src = 0;
	for (int i = 0; i < euler::n; i++)
	{
		if ((int)sz(euler::vertices[i].outs) > euler::vertices[i].in_degree)
		{
			src = i;
			break;
		}
		if (euler::vertices[i].in_degree)
			src = i;
	}
 
	return src;
}

bool check_condition()
{
	int c = 0;
	for (int i = 0; i < euler::n; ++i)
	    c += abs(euler::vertices[i].in_degree - sz(euler::vertices[i].outs));
	return c <= 2;
}

int main()
{
    int t;
    scanf("%d", &t);
    euler::n = 26;
    while (t--)
    {
        scanf("%d", &euler::m);
        for (int i = 0; i < euler::m; i++)
        {
            scanf("%s", aux);
            string str = aux;
            int u = str[0] - 'a';
            int v = str.back() - 'a';
            euler::edges[i] = {u, v, i};
            euler::vertices[u].outs.push_back(i);
            euler::vertices[v].in_degree++;
        }

        euler::init();

        if (!check_condition() || euler::euler_tour(euler::m, find_src()).empty())
        {
            printf("The door cannot be opened.\n");
        }
        else
        {
            printf("Ordering is possible.\n");
        }
        
        reset();
    }
    
}