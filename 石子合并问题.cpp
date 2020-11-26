#include<iostream>
#include<fstream>
using namespace std;
int *p;
int n;

struct elem
{
	int max;
	int min;
};

elem **d;

int sum(int i, int j)
{
	int s = 0;
	for (int k = 0; k <= j; k++)
		s = s + p[(i+k)%n];
	return s;
}

int min(int i, int j, int m )
{
	int s = 10000000;
	for (int k = 0; k < j; k++)
	{
		s = (d[i][k].min + d[(i+k + 1)%n][j-k-1].min+m) < s ? (d[i][k].min + d[(i + k + 1) % n][j - k - 1].min + m) : s;
	}
	return s;
}

int max(int i, int j,int m)
{
	int s =0;
	for (int k = 0; k < j; k++)
	{
		s = (d[i][k].max + d[(i+k + 1)%n][j-k-1].max+m) > s ? (d[i][k].max + d[(i + k + 1) % n][j - k - 1].max+m) : s;
	}
	return s;
}

int main()
{
	ifstream fin;
	fin.open("input.txt", ios::in);
	if (!fin.is_open())
		return 0;
	fin >> n;
	p = new int[n];
	for (int i = 0; i < n; i++)
		fin >> p[i];
	fin.close();
	d = new elem*[n];
	for (int i = 0; i < n; i++)
		d[i] = new elem[n];
	for (int i = 0; i < n; i++)
	{
		d[i][0] = { 0, 0};
	}
	for(int j=1;j<n;j++)
		for (int i = 0; i < n;i++)
		{
			d[i][j].max = max(i, j, sum(i, j));
			d[i][j].min = min(i, j, sum(i, j));
		}
	ofstream fout;
	fout.open("output.txt", ios::out);
	if (!fout.is_open())
		return 0;
	fout << d[0][n - 1].min << endl;
	fout << d[0][n - 1].max;
	fout.close();
}