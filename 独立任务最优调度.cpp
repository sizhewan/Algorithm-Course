#include<iostream>
#include<fstream>
using namespace std;

struct item
{
	int a;
	int b;
};

int main()
{
	ifstream fin;
	fin.open("input.txt", ios::in);
	if (!fin.is_open())
		return 0;
	int n;
	fin >> n;
	item* p;
	p = new item[n];
	for (int i = 0; i < n; i++)
		fin >> p[i].a;
	for (int i = 0; i < n; i++)
		fin >> p[i].b;
	fin.close();
	item k;
	k.a = 0;
	k.b = 0;
	for (int i = 0; i < n; i++)
	{
		int _a = k.a + p[i].a;
		int _b = k.b + p[i].b;
		if (_a <= _b)
			k.a = _a;
		else
			k.b = _b;
	}
	ofstream fout;
	fout.open("output.txt", ios::out);
	if (!fout.is_open())
		return 0;
	fout << (k.a >= k.b ? k.a : k.b);
	fout.close();
	return 0;
}