#include<iostream>
#include<fstream>
using namespace std;
 
int min(int a, int b, int c)
{
	int t = a < b ? a : b;
	return t < c ? t : c;
}

int main()
{
	ifstream fin;
	fin.open("input.txt",ios::in);
	if (!fin.is_open())
		return 0;
	char a[10], b[10];
	fin >> a;
	fin >> b;
	fin.close();
	int m = strlen(a);
	int n = strlen(b);
	int **p = new int*[m + 1];
	for (int i = 0; i < m + 1; i++)
		(p[i]) = new int[n + 1];
	for (int i = 0; i < m + 1; i++)
	{
		p[i][0] = i;
	}
	for (int i = 0; i < n + 1; i++)
	{
		p[0][i] = i;
	}
	for(int i=1;i<m+1;i++)
		for (int j = 1; j < n + 1; j++)
		{
			if (a[i] == b[j])
				p[i][j] = p[i - 1][j - 1];
			else
				p[i][j] = min(p[i - 1][j] + 1, p[i][j - 1] + 1, p[i - 1][j - 1] + 1);
		}
	ofstream fout;
	fout.open("output.txt", ios::out);
	if (!fout.is_open())
		return 0;
	fout << p[m][n];
	fout.close();
	return 0;
}