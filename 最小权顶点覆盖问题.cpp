#define _SCL_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<queue>
#include<algorithm>
using namespace std;

const int MAX= 50;
int G[MAX][MAX];
int bestx[MAX];
int w[MAX];	
int n, e;

class node
{
public:
	int depth;
	int value;
	int *x;
	int *c;
	node()
	{
		x = new int[n + 1];
		c = new int[n + 1];
	}

};

class compare
{
public:
	bool operator ()(node a, node b)const
	{
		return a.value > b.value ? true : false;
	}
};

priority_queue<node,vector<node>,compare> q;

bool cover(node N)
{
	for (int i = 1; i <= n; i++)
		if (N.x[i] == 0 && N.c[i] == 0)
			return false;
	return true;
}

void addnode(node N, int i, int v, bool is_left)
{
	node now;
	now.depth = i;
	copy(N.x, N.x + n + 1, now.x);
	copy(N.c, N.c + n + 1, now.c);
	if (is_left)
	{
		now.value = v + w[i];
		now.x[i] = 1;
		for (int j = 1; j <= n; j++)
			if (G[j][i])
				now.c[j]++;
	}
	else
	{
		now.value = v;
		now.x[i] = 0;
	}
	q.push(now);
}

int search()
{
	node N;
	for (int j = 1; j <= n; j++)
	{
		N.x[j] = 0;
		N.c[j] = 0;
	}
	int best;
	int i = 1;
	int value = 0;
	while (1)
	{
		if (i > n)
		{
			if (cover(N))
			{
				best = value;
				copy(N.x, N.x + n + 1, bestx);
				break;
			}
		}
		else
		{
			if (!cover(N))
				addnode(N, i, value, true);
			addnode(N, i, value, false);
		}
		if (q.empty())
			break;
		else
		{
			N = q.top();
			q.pop();
			i = N.depth + 1;
			value = N.value;
		}
	}
	return best;
}

int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("input.txt", ios::in);
	if (!fin.is_open())
		return 0;
	/***开始输入***/
	fin >> n >> e;
	for (int i = 1; i <= n; i++)
	{
		fin >> w[i];
	}
	int a, b;
	memset(G, 0, sizeof(G));
	for (int i = 0; i <= e; i++)
	{
		fin >> a >> b;
		G[a][b] = G[b][a] = 1;
	}
	/***************/
	fin.close();
	/***开始算法***/
	int best = search();
	/***************/
	fout.open("output.txt", ios::out);
	if (!fout.is_open())
		return 0;
	/***开始输出***/
	fout << best << endl;
	for (int i = 1; i <= n; i++)
		fout << bestx[i] << ' ';
	/***************/
	fin.close();

	return 0;
	
}