#include<iostream>
#include<fstream>
using namespace std;
int len=0;
int e;
void split(int a[], int left, int right,int middle,int &l,int&r)
{
	int i, j;
	i = (left + right) / 2;
	j = (left + right) / 2;
	for (; a[i] == a[middle]; i--);
	l = i + 1;
	for (; a[j] == a[middle]; j++);
	r = j - 1;
}

void most(int a[], int left, int right)
{
	int l, r;
	int middle = (left + right) / 2;
	split(a, left, right, middle, l, r);
	if (len < r - l + 1)
	{
		len = r - l + 1;
		e = a[middle];
	}
	if (l - left > len)
		most(a, left, l - 1);
	if (right - r > len)
		most(a, r + 1, right);
}

int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("input.txt", ios::in);
	if (!fin.is_open())
		return 0;
	int i;
	fin >> i;
	int *a;
	a = new int[i];
	for (int k = 0; k < i; k++)
		fin >> a[k];
	fin.close();
	most(a, 0, i - 1);
	fout.open("output.txt", ios::out);
	if (!fout.is_open())
		return 0;
	fout << e << endl << len << endl;
	fout.close();
	delete a;
	return 0;
}