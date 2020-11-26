#include<iostream>
#include<fstream>
using namespace std;

struct event
{
	int start;
	int end;
};

int main()
{
	int m = 0;
	ifstream fin;
	ofstream fout;
	fin.open("input.txt", ios::in);
	if (!fin.is_open())
		return 0;
	int n;
	fin >> n;
	event* p = new event[n];
	for (int i = 0; i < n; i++)
		fin >> p[i].start >> p[i].end;
	fin.close();
	int* c = new int[n];
	for (int i = 0; i < n; i++)
		c[i] = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (p[i].start >= c[j])
			{
				c[j] = p[i].end;
				m = (m < j) ? j : m;
				break;
			}
		}
	}
	fout.open("output.txt", ios::out);
	if (!fout.is_open())
		return 0;
	fout << m + 1;
	fout.close();
	return 0;
}