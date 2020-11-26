#include<iostream>
#include<fstream>
using namespace std;

int com(int m, int n)
{
	if (m < n)
		return 0;
	else if (n == 0)
		return 1;
	else if (n == 1)
		return m;
	else
		return com(m - 1, n - 1) + com(m-1, n );
}

int main()
{
	int n;
	ifstream fin;
	fin.open("input.txt", ios::in);
	if (!fin.is_open())
		return 0;
	else
	{
		fin >> n;
		int* p;
		p = new int[n];

		for (int k = 0; k < n; k++)
		{
			int num = 0;
			int temp = 0;
			char str[7];

			fin >> str;
			int len = strlen(str);
			if (len == 1)
				num = str[0] - 96;
			else
			{
				int tab[27];
				for (int i = 0; i < 27; i++)
					tab[i] = 0;
				for (int i = 0; i < len; i++)
					tab[str[i] - 96] = 1;
				temp = len;
				for (int i = 1; i < len; i++)
				{
					num += com(26, i);
				}
				for (int i = 1; i <= 26; i++)
				{
					if (tab[i] == 0 && temp > 1)
					{
						num += com(26 - i, temp - 1);
					}
					else if (tab[i] == 1)
						temp--;
					else if (temp == 1)
						break;
				}
				num += str[len - 1] - str[len - 2];
			}

			p[k] = num;
		}
		fin.close();

		ofstream fout;
		fout.open("output.txt", ios::out);
		for (int k = 0; k < n; k++)
		{
			fout << p[k] << endl;
		}
	}
	return 0;
}