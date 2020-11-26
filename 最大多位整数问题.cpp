#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
using namespace std;

int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("input.txt", ios::in);
	if (!fin.is_open())
		return 0;
	int n;
	fin >> n;
	string* p = new string [n];
	for (int i = 0; i < n; i++)
		fin >> p[i];
	fin.close();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			if (p[j] + p[j + 1] > p[j + 1] + p[j])
			{
				string temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}
	fout.open("output.txt", ios::out);
	if (!fout.is_open())
		return 0;
	for (int i = n - 1; i >= 0; i--)
		fout << p[i];
	fout.close();
	return 0;
}