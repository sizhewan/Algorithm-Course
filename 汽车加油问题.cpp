#include<iostream>
#include<fstream>
using namespace std;

int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("input.txt", ios::in);
	if (!fin.is_open())
		return 0;
	int n, k, t, m;
	m = 0;
	fin >> n >> k;
	int *p = new int[n+1];
	for (int i = 0; i < k+1; i++)
	{
		fin >> t;
		if (t > n)
			m = -1;
		p[i] = t;
	}
	fin.close();
	if (m != -1)
	{
		int a = n;
		for (int i = 0; i < k+1; i++)
		{
			if (a < p[i])
			{
				a = n;
				m++;
			}
			a = a - p[i];
		}
	}
	fout.open("output.txt", ios::out);
	if (!fout.is_open())
		return 0;
	if (m == -1)
		fout << "No Solution";
	else
		fout << m;
	fout.close();
	return 0;
}