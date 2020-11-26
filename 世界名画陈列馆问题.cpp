#include<iostream>
#include<fstream>
using namespace std;
#define MAX 21
int room[MAX][MAX] = { 0 }, robot[MAX][MAX] = { 0 }, best[MAX][MAX] = { 0 };
int m=0, n=0;
int rmin = 10000000 ;
int k = 0, t = 0;
int t1, t2, more;
int dx[] = { 0,1,-1,0,0 };
int dy[] = { 0,0,0,1,-1 };

void change(int i, int j)
{
	robot[i][j] = 1;
	k++;
	for (int d = 0; d < 5; d++)
	{
		int p = i + dx[d];
		int q = j + dy[d];
		room[p][q]++;
		if (room[p][q] == 1)
			t++;
	}
}

void restore(int i, int j)
{
	robot[i][j] = 0;
	k--;
	for (int d = 0; d < 5; d++)
	{
		int p = i + dx[d];
		int q = j + dy[d];
		room[p][q]--;
		if (room[p][q] == 1)
			t--;
	}
}

void backtrack(int i,int j)
{
	do
	{
		j++;
		if (j > n)
		{
			i++;
			j = 1;
		}
	} while (room[i][j] != 0 && i <= n);

	if (i > n)
		{
			if (k < rmin)
			{
				rmin = k;
				for (int i = 1; i <= m; i++)
					for (int j = 1; j <= n; j++)
						best[i][j] = robot[i][j];
			}
		}

	if (k + (t1 - t) / 5 >= rmin)
		return;
	if (i < n - 1 && (k + (t2 - t) / 5 >= rmin))
		return;
	if (i < n)
	{
		change(i + 1, j);
		backtrack(i, j);
		restore(i + 1, j);
	}
	if (j < m && (room[i][j + 1] == 0 || room[i][j + 2] == 0))
	{
		change(i , j+1);
		backtrack(i, j);
		restore(i , j+1);
	}
	if (room[i+1][j ] == 0 &&room[i][j + 1] == 0)
	{
		change(i, j );
		backtrack(i, j);
		restore(i, j );
	}
}

void compute()
{
	more = m / 4 + 1;
	if (m % 4 == 3)
		more++;
	else if (m % 4 == 2)
		more += 2;
	t2 = m*n + more + 4;
	t1 = m*n + 4;

	if (n == 1 && m == 1)
		best[1][1] = 1;
	else
		backtrack(1, 0);
}

int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("input.txt", ios::in);
	if (!fin.is_open())
		return 0;

	/***开始输入***/
	fin >> m >> n;
	/***************/

	fin.close();

	/***开始算法***/
	compute();
	/***************/

	fout.open("output.txt", ios::out);
	if (!fout.is_open())
		return 0;

	/***开始输出***/
	fout << rmin << endl;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
			fout << best[i][j] << ' ';
		fout << endl;
	}
	/***************/

	fout.close();

	return 0;
}