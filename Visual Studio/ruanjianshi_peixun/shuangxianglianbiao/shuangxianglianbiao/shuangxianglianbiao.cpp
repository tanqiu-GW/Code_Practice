// shuangxianglianbiao.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"



/*	类型声明	*/
typedef struct node
{
	struct node *prev;
	struct node *next;
	int data;
}Node;



/*	函数声明	*/
Node *initList(Node *list, int number);
Node *insertList(Node *list, int data, int add);
Node *deleteList(Node *list, int data);
void printf(Node *list);


/*	主函数	*/
int main()
{
	Node *list = NULL;
	list = initList(list, 10);
	printf(list);
	list = insertList(list, 55, 5);
	printf(list);
	list = deleteList(list, 55);
	printf(list);
    return 0;
}



//初始化链表
Node *initList(Node *list, int number)
{
	list = (Node *)malloc(sizeof(Node));	//创建链表的第一个节点
	list->prev = NULL;
	list->next = NULL;
	list->data = 1;
	Node *temp = list;
	int i;
	for (i = 2; i <= number; i++)
	{
		Node *point = (Node *)malloc(sizeof(Node));	//创建并初始化一个新节点
		point->prev = NULL;
		point->next = NULL;
		point->data = i;

		temp->next = point;		//前驱节点的next指针指向新节点
		point->prev = temp;		//新节点的prev指针指向前驱节点
		temp = temp->next;
	}
	return list;
}

//链表中插入节点
Node *insertList(Node *list, int data, int add)
{
	Node *temp = (Node *)malloc(sizeof(Node));	//创建一个新节点
	temp->prev = NULL;
	temp->next = NULL;
	temp->data = data;

	if (add == 1)	//插入位置在表头
	{
		temp->next = list;
		list->prev = temp;
		list = temp;
	}
	else
	{
		Node *point = list;
		int i;
		for (i = 1; i < add - 1; i++)	//找到要插入位置的前一个节点
			point = point->next;
		if (point->next == NULL)	//插入位置在表尾
		{
			point->next = temp;
			temp->prev = point;
		}
		else						//插入位置在表中
		{
			point->next->prev = temp;
			temp->next = point->next;
			point->next = temp;
			temp->prev = point;
		}
	}
	return list;
}

//删除链表节点
Node *deleteList(Node *list, int data)
{
	Node *temp = list;
	while (temp)		//遍历链表
	{
		if (temp->data == data)
		{
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			free(temp);
			return list;
		}
		temp = temp->next;
	}
	printf("链表中无此数据\n");
	return list;
}

//打印链表
void printf(Node *list)
{
	Node *temp = list;
	while (temp)
	{
		if (temp->next == NULL)
		{
			printf("%d\n", temp->data);
		}
		else
		{
			printf("%d   ", temp->data);
		}
		temp = temp->next;
	}
}