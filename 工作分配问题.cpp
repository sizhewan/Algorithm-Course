#include<iostream>
#include<fstream>
using namespace std;

int n;
int **p;
int *f;
int sum=0, min=1000000;

void backtrack(int i)
{
	if (i < n)
	{
		for (int j = 0; j < n; j++)
		{
			if (f[j] == 0)
			{
				sum += p[j][i];
				f[j] = 1;
				if (i == n - 1)
					min = sum < min ? sum : min;
				backtrack(i + 1);
				sum -= p[j][i];
				f[j] = 0;
			}
		}
	}
}

int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("input.txt", ios::in);
	if (!fin.is_open())
		return 0;
	/***开始输入***/
	fin >> n;
	p = new int*[n];
	for (int i = 0; i < n; i++)
	{
		p[i] = new int[n];
		for (int j = 0; j < n; j++)
			fin >> p[i][j];
	}
	f = new int[n];
	for (int i = 0; i < n; i++)
		f[i] = 0;
	/***************/
	fin.close();
	/***开始算法***/
	backtrack(0);
	/***************/
	fout.open("output.txt", ios::out);
	if (!fout.is_open())
		return 0;
	/***开始输出***/
	fout << min;
	/***************/
	fin.close();

	return 0;
}