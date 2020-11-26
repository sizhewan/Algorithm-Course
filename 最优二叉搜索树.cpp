#include<iostream>
using namespace std;

void OBST(int* a, int *b, int n, int **m, int **s, int**w)
{
	for (int i = 0; i <= n; i++)
	{
		w[i + 1][i] = a[i];
		m[i + 1][i] = 0;
	}
	for (int r = 0; r < n; r++)
		for(int i=1;i<=n-r;i++)
	{
		int j = i + r;
		w[i][j] = w[i][j - 1] + a[j] + b[j];
		m[i][j] = m[i + 1][j];
		s[i][j] = 1;
		for (int k = i + 1; k <= j; k++)
		{
			int t = m[i][k - 1] + m[k + 1][j];
			if (t < m[i][j])
			{
				m[i][j] = t;
				s[i][j] = k;
			}
		}
		m[i][j] += w[i][j];
	}
}