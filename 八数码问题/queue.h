#pragma once
#include "state.h"
typedef EightCode QElemType;
typedef  struct QNode
{	       //Ԫ�ؽ��
	QElemType    data;
	int read;
	struct QNode *next;
	struct QNode *father;
}QNode, *QueuePtr;
typedef struct           //ͷ�ڵ�
{
	QueuePtr  front;  	//��ͷָ��
	QueuePtr  rear;	     //��βָ��
}LinkQueue;
int InitQueue(LinkQueue &Q)
{
	Q.front = new QNode;
	if (!Q.front)
		return 0;
	Q.rear = Q.front;
	Q.front->next = NULL;
}//�����ն��У���ʱ������ڵ㲻�洢Ԫ�ء�
int DestroyQueue(LinkQueue &Q)
{
	while (Q.front)
	{
		QueuePtr q = Q.front->next;
		delete Q.front;
		Q.front = q;
	}
	return 1;
}
QueuePtr EnQueue(LinkQueue &Q, QElemType e, QueuePtr dad, int f[3][3])
{
	QueuePtr q = new QNode;
	if (!q)
		return 0;
	q->data = e;
	q->read = 0;
	q->father = dad;
	if (Q.rear == Q.front || q->data.h(f) >= Q.rear->data.h(f))
	{
		q->next = NULL;
		Q.rear->next = q;
		Q.rear = q;
		return q;
	}
	else if (q->data.h(f) < Q.front->next->data.h(f))
	{
		q->next = Q.front->next;
		Q.front->next = q;
		return q;
	}
	else
	{
		QueuePtr temp = Q.front->next;
		while (1)
		{
			if (q->data.h(f) >= temp->data.h(f) && q->data.h(f) < temp->next->data.h(f))
			{
				q->next = temp->next;
				temp->next = q;
				break;
			}
			temp = temp->next;
		}
		return q;
	}
}
