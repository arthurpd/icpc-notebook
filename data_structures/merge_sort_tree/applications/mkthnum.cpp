#include "../merge_sort_tree.cpp"

int main(void)
{
	int n, q, x, y, z;
	scanf("%d %d", &n, &q);
	vector<int> v(n);
	for (int i = 0; i < n; i++)
		scanf("%d", &v[i]);

	merge_sort_tree mst(v);
	for (int i = 0; i < q; i++)
	{
		scanf("%d %d %d", &x, &y, &z);
		printf("%d\n", mst.kth(x - 1, y - 1, z));
	}
}
