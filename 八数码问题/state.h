#pragma once
#include <iostream>
#include <cmath>
#include <windows.h>
using namespace std;
/* ������ƶ���ָ��λ�� */
void gotoxy(HANDLE hout, const int X, const int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(hout, coord);
}

/* ����ָ������ɫ

��ɫ��ȡֵ�ɱ���ɫ+ǰ��ɫ��ɣ���16��
fg_color��0-7    ��   ��   ��   ��   ��   ��   ��   ��
8-15 ���� ���� ���� ���� ���� ���� ���� ����
bg_color��0-7    ��   ��   ��   ��   ��   ��   ��   ��
8-15 ���� ���� ���� ���� ���� ���� ���� ����
���յ���ɫΪ ����ɫ*16+ǰ��ɫ */
void setcolor(HANDLE hout, const int bg_color, const int fg_color)
{
	SetConsoleTextAttribute(hout, bg_color * 16 + fg_color);
}
class EightCode
{
protected:
	int table[3][3];
	int x, y;
	int steps;
public:
	EightCode(int table[3][3], int steps = 0);
	EightCode() {}
	bool operator == (EightCode t);
	void print();
	int move(int i);    //1�� 2�� 3�� 4��
	EightCode extend(int i);
	int h(int f[3][3]);
};
EightCode::EightCode(int table[3][3], int steps)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			this->table[i][j] = table[i][j];
			if (table[i][j] == 0)
			{
				x = j;
				y = i;
			}
		}
	}
	this->steps = steps;
}
bool EightCode::operator == (EightCode t)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (this->table[i][j] != t.table[i][j])
				return 0;
		}
	}
	return 1;
}
void EightCode::print()
{
	cout << "�X�T�j�T�j�T�[" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "�U";
		for (int j = 0; j < 3; j++)
		{
			if (table[i][j] == 0)
				cout << "  " << "�U";
			else
				cout << ' ' << table[i][j] << "�U";
		}
		cout << endl;
		if (i == 0 || i == 1)
		{
			cout << "�d�T�p�T�p�T�g";
			cout << endl;
		}

	}
	cout << "�^�T�m�T�m�T�a";
}
int EightCode::move(int i)    //1�� 2�� 3�� 4��
{
	if (i == 1)
		return y > 0;
	if (i == 2)
		return y < 2;
	if (i == 3)
		return x > 0;
	if (i == 4)
		return x < 2;
}
EightCode EightCode::extend(int i)
{
	int newstate[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			newstate[i][j] = table[i][j];
	if (i == 1)
	{
		int temp = newstate[y - 1][x];
		newstate[y - 1][x] = 0;
		newstate[y][x] = temp;
		return EightCode(newstate);
	}
	if (i == 2)
	{
		int temp = newstate[y + 1][x];
		newstate[y + 1][x] = 0;
		newstate[y][x] = temp;
		return EightCode(newstate);
	}
	if (i == 3)
	{
		int temp = newstate[y][x - 1];
		newstate[y][x - 1] = 0;
		newstate[y][x] = temp;
		return EightCode(newstate);
	}
	if (i == 4)
	{
		int temp = newstate[y][x + 1];
		newstate[y][x + 1] = 0;
		newstate[y][x] = temp;
		return EightCode(newstate);
	}
}
int EightCode::h(int f[3][3])
{
	int weight = this->steps;
	for (int i = 0; i <= 2; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
			for (int m = 0; m <= 2; m++)
			{
				for (int n = 0; n <= 2; n++)
				{
					if (table[i][j] == f[m][n])
					{
						if (table[i][j] != 0)
							weight += (abs(m - i) + abs(n - j));
						break;
					}
				}
			}
		}
	}
	return weight;
}
