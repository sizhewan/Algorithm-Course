#include "queue.h"
#include <windows.h>
using namespace std;
int steps = 0;
int main()
{
	int s[3][3] = { { 0,2,3 },{ 1,5,4 } ,{ 6,8,7 } };
	EightCode start(s, steps);
	int f[3][3] = { { 0,1,2 },{ 3,4,5 } ,{ 6,7,8 } };
	EightCode finish(f, steps);
	LinkQueue Q;
	InitQueue(Q);
	EnQueue(Q, start, NULL, f);
	QueuePtr head = Q.rear;
	int find = 0;
	int count = 0;
	QueuePtr aim;
	int available = 0;
	int a[8];
	int t = 0;
	for (int i = 0; i<3; i++)
		for (int j = 0; j < 3; j++)
		{
			if (s[i][j] != 0)
				a[t++] = s[i][j];
		}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (a[j] < a[i])
				available++;
		}
	}
	if (available % 2)
	{
		cout << "²»¿É´ï£¡£¡";
		getchar();
		getchar();
		return 0;
	}
	while (1)
	{
		EightCode temp;
		temp = head->data;
		steps++;
		for (int i = 1; i <= 4; i++)
		{
			if (temp.move(i))
			{
				int flag = 1;
				QueuePtr s = Q.front->next;
				while (s)
				{
					if (temp.extend(i) == s->data)
					{
						flag = 0;
						break;
					}
					s = s->next;
				}
				if (flag)
				{
					aim = EnQueue(Q, temp.extend(i), head, f);
					if (temp.extend(i) == finish)
					{
						find = 1;
						break;
					}
				}
			}
		}
		if (find == 1)
			break;
		head->read = 1;
		head = Q.front->next;
		while (1)
		{
			if (head->read)
				head = head->next;
			else
				break;
		}
	}
	cout << "find" << endl; getchar();
	QueuePtr backtrack = aim;
	while (1)
	{
		count++;
		if (backtrack->data == start)
			break;
		backtrack = backtrack->father;
	}
	EightCode *method = new EightCode[count];
	backtrack = aim;
	for (int i = count - 1; i >= 0; i--)
	{
		method[i] = backtrack->data;
		backtrack = backtrack->father;
	}

	for (int i = 0; i < count; i++)
	{
		system("cls");
		method[i].print();
		getchar();
	}
	DestroyQueue(Q);
	return 0;
}