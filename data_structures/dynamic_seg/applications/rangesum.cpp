#include "../dynamic_seg.cpp"

#define node node<ll>

int main(void)
{
	int s = 1e5;
	int n, a, b, c, q, tp;
	cin >> n;	
	node *root = new node();
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &a);
		root->update(0, 2e5, s + i, a);
	}

	cin >> q;
	while(q--)
	{
		scanf("%d", &tp);
		if (tp == 1)
		{
			scanf("%d %d", &a, &b);
			printf("%lld\n", root->get(0, 2e5, s + a - 1, s + b - 1));
		}
		else
		{
			scanf("%d", &a);
			s--;
			root->update(0, 2e5, s, a);
		}
	}
}

