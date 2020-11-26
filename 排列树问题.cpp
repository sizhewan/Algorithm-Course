#include<iostream>
#include<fstream>
using namespace std;

class circle
{
	friend float circleperm(int, float*);
private:
	float center(int t);
	void compute(void);
	void backtrack(int t);
	float min, *x, *r;
	int n;
};

float circle::center(int t)
{
	float temp = 0;
	for (int j = 1; j < t; j++)
	{
		float valuex = x[j] + 2.0*sqrt(r[t] * r[j]);
		if (valuex >= temp)
			temp = valuex;
	}
	return temp;
}

void circle::compute(void)
{
	float low = 0, high = 0;
	for (int i = 1; i <= n; i++)
	{
		if (x[i] - r[i] < low)
			low = x[i] - r[i];
		if (x[i] + r[i] > high)
			high = x[i] + r[i];
	}
	if (high - low < min)
		min = high - low;
}

void circle::backtrack(int t)
{
	if (t > n)
		compute();
	else
	{
		for (int j = t; j <= n; j++)
		{
			swap(r[t], r[j]);
			float centerx = center(t);
			if (centerx + r[t] + r[1] < min)
			{
				x[t] = centerx;
				backtrack(t + 1);
			}
			swap(r[t], r[j]);
		}
	}
}

float circleperm(int n, float *a)
{
	circle X;
	X.n = n;
	X.r = a;
	X.min = 1000000;
	float *x = new float[n + 1];
	X.x = x;
	X.backtrack(1);
	delete[]x;
	return X.min;
}

int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("input.txt", ios::in);
	if (!fin.is_open())
		return 0;
	/***开始输入***/
	int n;
	fin >> n;
	float *a;
	a = new float[n + 1];
	for (int i = 1; i <= n; i++)
		fin >> a[i];
	/***************/
	fin.close();
	/***开始算法***/
	float y=circleperm(n, a);

	/***************/
	fout.open("output.txt", ios::out);
	if (!fout.is_open())
		return 0;
	/***开始输出***/
	fout << y;

	/***************/
	fout.close();

	return 0;
}