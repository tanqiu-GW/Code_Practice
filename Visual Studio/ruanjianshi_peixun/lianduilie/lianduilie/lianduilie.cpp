// lianduilie.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdlib.h"
#include "string.h"
#include "malloc.h"



#define Uint8	unsigned char



typedef struct Node
{
	Uint8 character;		//结点数据域，字符型数据
	struct Node *next;
}pNode;

typedef struct Queue
{
	pNode *front;			//队列头指针
	pNode *tail;			//尾指针
}pQueue;

pQueue *initQueue(pQueue *queue)
{
	pNode  *Node;
	Node = (pNode *)malloc(sizeof(pNode));
	/*Node->next = NULL;
	Node->character = 0;
	memset(Node, 0, sizeof(Node));*/
	queue->front = Node;
	queue->tail = Node;
	queue->front->next = NULL;
	memset(queue, 0, sizeof(queue));
	return queue;
}

bool isEmptyQueue(pQueue *queue)
{
	if (queue->front == queue->tail)
		return true;
	else
		return false;
}

pQueue *enterQueue(pQueue *queue, Uint8 data)
{
	pNode *Node;
	Node = (pNode *)malloc(sizeof(pNode));
	Node->character = data;
	Node->next = NULL;
	//尾插法插入字符到链队列
	queue->tail->next = Node;		//上个队列尾指针指向新队列元素
	queue->tail = Node;				//更新队尾指针，重新指向队列最后元素
	return queue;
}

Uint8 outQueue(pQueue *queue)
{
	Uint8 character;
	pNode *temp;
	temp = (pNode *)malloc(sizeof(pNode));
	if (!isEmptyQueue(queue))
	{
		temp = queue->front->next;
		character = temp->character;
		queue->front->next = temp->next;	//更新队列头指针
		if (queue->tail == temp)
			temp = NULL;
		return character;
	}
	else
	{
		return false;
	}
}




int main()
{
	Uint8 buf;
	pQueue *queue;
	queue = (pQueue *)malloc(sizeof(pQueue));
	initQueue(queue);
	enterQueue(queue, 'a');
	buf = outQueue(queue);
	return 0;
}

