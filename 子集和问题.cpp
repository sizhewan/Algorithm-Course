#include<iostream>
#include<fstream>
using namespace std;
int n, c;
int *p, *k;
int ok = 0;
int sum = 0;

void backtrack(int i)
{
	if (i < n)
	{
		if (sum == c)
		{
			ok = 1;
			return;
		}
		else
		{
			if (sum + p[i] <= c)
			{
				k[i] = 1;
				sum += p[i];
				backtrack(i + 1);
				if (ok)
					return;
				k[i] = 0;
				sum -= p[i];
			}
			backtrack(i + 1);
		}
	}
	else
		ok = 0;
}

int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("input.txt", ios::in);
	if (!fin.is_open())
		return 0;
	fin >> n >> c;
	p = new int[n];
	k = new int[n];
	for (int i = 0; i < n; i++)
	{
		fin >> p[i];
		k[i] = 0;
	}
	fin.close();
	backtrack(0);
	fout.open("output.txt", ios::out);
	if (!fout.is_open())
		return 0;
	if (!ok)
		fout << "No Solution !";
	else
		for (int i = 0; i < n; i++)
			if (k[i])
				fout << p[i]<<" ";
	fout.close();
	return 0;
}