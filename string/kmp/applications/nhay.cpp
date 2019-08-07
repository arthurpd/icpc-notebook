// https://www.spoj.com/problems/NHAY/

#include "../kmp.cpp"

int main(void)
{
	int n;
	string key;
	while (scanf("%d", &n) != EOF)
	{
		string text;
		cin >> key;
		scanf(" ");
		char c;
		while ((c = getchar()) != '\n')
			text += c;

		for (int x : kmp(text, key))
			printf("%d\n", x);
		printf("\n");
	}
}
