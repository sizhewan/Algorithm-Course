#include<iostream>
using namespace std;

void swap(char* a, char *b)
{
	int m;
	m = *a;
	*a = *b;
	*b = m;
	return;
}
void perm(char* list, int k, int m, const int len)
{
	int i;
	if (k == m)
	{
			for (i = 0; i <= m; i++)
				cout << ' ' << list[i];
			cout << endl;
	}
	else
	{
		for (i = k; i <= m; i++)
		{
			swap(&list[k], &list[i]);
			perm(list, k + 1, m, len);
			swap(&list[k], &list[i]);
		}
	}
	return;
}
int main()
{
	char list[10];	
	cin >> list;

	cout << endl;
	perm(list, 0, strlen(list) - 1, strlen(list));
	cout << endl;
	return 0;
}