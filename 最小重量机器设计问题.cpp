#include<iostream>
#include<fstream>
using namespace std;

int n, m, d;
int **w,**c;
int csum=0,wsum=0, min=1000000;
int *f, *tf;
void backtrack(int i)
{
	if (i < n)
	{
		for (int j = 0; j < m; j++)
		{
			wsum += w[i][j];
			csum += c[i][j];
			tf[i] = j+1;
			if (i == n-1&&wsum < min&&csum <= d)
			{
				min = wsum;
				for (int k = 0; k < n; k++)
					f[k] = tf[k];
			}
			backtrack(i + 1);
			wsum -= w[i][j];
			csum -= c[i][j];
			tf[i] = 0;
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
	fin >> n >> m >> d;
	c= new int*[n];
	w = new int*[n];
	f = new int[n];
	tf = new int[n];
	for (int i = 0; i < n; i++)
	{
		f[i] = 0;
		tf[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		c[i] = new int[m];
		for (int j = 0; j < m; j++)
			fin >> c[i][j];
	}
	for (int i = 0; i < n; i++)
	{
		w[i] = new int[m];
		for (int j = 0; j < m; j++)
			fin >> w[i][j];
	}
	/***************/
	fin.close();
	/***开始算法***/
	backtrack(0);
	/***************/
	fout.open("output.txt", ios::out);
	if (!fout.is_open())
		return 0;
	/***开始输出***/
	fout << min << endl;
	for (int i = 0; i < n; i++)
		fout << f[i] << ' ';
	/***************/
	fin.close();

	return 0;
}