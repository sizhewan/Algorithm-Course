#include<iostream>
#include<fstream>
using namespace std;

int half(int n);
int sigma(int buttom, int top);

int half(int n)
{
	if (n == 1)
		return 1;
	else if (n == 2)
		return 2;
	else if (n == 3)
		return 2;
	else
		return 1 + sigma(1, n / 2);
}

int sigma(int buttom, int top)
{
	int sum = 0;
	for (int i = buttom; i <= top; i++)
		sum += half(i);
	return sum;
}

int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("input.txt", ios::in);
	if (!fin.is_open())
		return 0;
	int n;
	fin >> n;
	fin.close();
	fout.open("output.txt", ios::out);
	if (!fout.is_open())
		return 0;
	fout << half(n) << endl;
	fout.close();
	return 0;
}