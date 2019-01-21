/********************************************************************************

 *************************Copyright (C), 2018, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : list.c
 * @brief   		  : .C file function description
 * @author       : gw
 * @version        : 1.0
 * @date          : 2018-11-08
 * 
 * 
 * @note History:
 * @note        : 循环双向链表函数 2018-11-08
 * @note        : 
 *   Modification: Created file

********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "list.h"


//局部变量
static List *list;	//链表头指针


//局部函数
static Node *createNode(void *pval);		//创建节点。成功返回节点指针，否则返回NULL
static Node *getNode(int index);			//获取链表中第index位置节点
static Node *getFirstNode(void);			//获取链表中第一个节点
static Node *getLastNode(void);				//获取链表中最后一个节点



/**
 * @fn       Node *createNode(void * pval)
 * @brief    创建新的节点
 * 
 * @param[in]          void * pval  
 * @return         Node
 */
Node *createNode(void * pval)
{
	Node *pNode = (Node *)malloc(sizeof(Node));

	if(!pNode)
	{
		printf("create node error!\n");
		return NULL;
	}

	//默认pNode的前一节点和后一节点都指向它自身
	pNode->prev = pNode->next = pNode;
	pNode->data = pval;

	return pNode;
}

/**
 * @fn       Node *getNode(int index)
 * @brief    获取链表中index位置的节点，返回此节点指针
 * 
 * @param[in]          int index  
 * @return         Node
 */
Node *getNode(int index)
{
	int i = 0;
	Node *pNode;

	if(index < 0 || index >= list->count)
	{
		printf("failed! index out of bound!\n");
		return NULL;
	}

	//正向查找
	if(index <= (list->count / 2))
	{
		pNode = list->head->next;
		while((i++) < index)
		{
			pNode = pNode->next;
		}
	}
	else	//反向查找
	{
		pNode = list->head->prev;
		while((i++) < (list->count - index - 1))
		{
			pNode = pNode->prev;
		}
	}

	return pNode;
}

/**
 * @fn       Node *getFirstNode(void)
 * @brief    获取链表中第一个节点，返回节点指针
 * 
 * @param[in]          void  
 * @return         Node
 */
Node *getFirstNode(void)
{
	return getNode(0);
}

/**
 * @fn       Node *getLastNode(void)
 * @brief    获取链表中最后一个节点，返回节点指针
 * 
 * @param[in]          void  
 * @return         Node
 */
Node *getLastNode(void)
{
	return getNode(list->count - 1);
}


/**
 * @fn       List *createList(void)
 * @brief    创建新的双向链表，返回链表头节点指针
 * 
 * @param[in]          void  
 * @return         List
 */
List *createList(void)
{
	list = (List *)malloc(sizeof(List));
	list->head = createNode(NULL);

	if(!list->head)
	{
		return NULL;
	}

	list->count = 0;

	return list;
}

/**
 * @fn       int isEmptyList(void)
 * @brief    判断双向链表是否为空
 * 
 * @param[in]          void  
 * @return         
 */
int isEmptyList(void)
{
	return (list->count == 0);
}

/**
 * @fn       int sizeList(void)
 * @brief    返回双向链表大小
 * 
 * @param[in]          void  
 * @return         
 */
int sizeList(void)
{
	return list->count;
}

/**
 * @fn       void *getList(int index)
 * @brief    获取双向链表中第index位置的元素。成功则返回-
             节点指针
 * 
 * @param[in]          int index  
 * @return         void
 */
void *getList(int index)
{
	Node *pNode = getNode(index);
	
	if(!pNode)
	{
		printf("failed!\n");
		return NULL;
	}

	return pNode->data;
}

/**
 * @fn       void *getFirstList(void)
 * @brief    获取链表第一个元素
 * 
 * @param[in]          void  
 * @return         void
 */
void *getFirstList(void)
{
	return getList(0);
}


void *getLastList(void)
{
	return getList(list->count - 1);
}

/**
 * @fn       int insertList(int index, void * pval)
 * @brief    将vpal插入到index位置。成功则返回0
 * 
 * @param[in]          int index    
 * @param[in]        void * pval  
 * @return         
 */
int insertList(int index, void * pval)
{
	Node *pIndex, *pNode;
	
	//插入表头
	if(index == 0)
	{
		return insertFirstList(pval);
	}

	//获取要插入位置对应的节点
	pIndex = getNode(index);
	if(!pIndex)
	{
		return -1;
	}

	//创建节点
	pNode = createNode(pval);
	if(!pNode)
	{
		return -1;
	}

	pNode->prev = pIndex->prev;
	pNode->next = pIndex;
	pIndex->prev->next = pNode;
	pIndex->prev = pNode;

	//节点数+1
	list->count++;

	return 0;
}

/**
 * @fn       int insertFirstList(void * pval)
 * @brief    插入pval到表头位置
 * 
 * @param[in]          void * pval  
 * @return         
 */
int insertFirstList(void * pval)
{
	Node *pNode = createNode(pval);
	if(!pNode)
	{
		return -1;
	}

	pNode->prev = list->head;
	pNode->next = list->head->next;
	list->head->next->prev = pNode;
	list->head->next = pNode;

	list->count++;

	return 0;
}

/**
 * @fn       int insertLastList(void * pval)
 * @brief    插入pval到表尾，成功返回0
 * 
 * @param[in]          void * pval  
 * @return         
 */
int insertLastList(void * pval)
{
	Node *pNode = createNode(pval);
	if(!pNode)
	{
		return -1;
	}

	pNode->next = list->head;
	pNode->prev = list->head->prev;
	list->head->prev->next = pNode;
	list->head->prev = pNode;

	list->count++;

	return 0;
}

/**
 * @fn       int deleteList(int index)
 * @brief    删除index位置节点，成功返回0
 * 
 * @param[in]          int index  
 * @return         
 */
int deleteList(int index)
{
	Node *pIndex = getNode(index);
	if(!pIndex)
	{
		return -1;
	}

	pIndex->next->prev = pIndex->prev;
	pIndex->prev->next = pIndex->next;
	free(pIndex);

	list->count--;

	return 0;
}

/**
 * @fn       int deleteFirstList(void)
 * @brief    删除表头节点
 * 
 * @param[in]          void  
 * @return         
 */
int deleteFirstList(void)
{
	return deleteList(0);
}

/**
 * @fn       int deleteFirstList(void)
 * @brief    删除表尾的节点
 * 
 * @param[in]          void  
 * @return         
 */
int deleteLastList(void)
{
	return deleteList(list->count - 1);
}

/**
 * @fn       int destroyList(void)
 * @brief    销毁双向链表
 * 
 * @param[in]          void  
 * @return         
 */
int destroyList(void)
{
	Node *pNode = list->head->next;
	Node *pTemp = NULL;

	if(!list->head)
	{
		printf("failed! list is NULL!\n");
		return -1;
	}

	while(pNode != list->head)
	{
		pTemp = pNode;
		pNode = pNode->next;
		free(pTemp);
	}

	free(list);
	list->head = NULL;
	list->count =0;

	return 0;
}

/**
 * @fn       void printfList(Type type)
 * @brief    打印不同类型的双向链表的数据
 * 
 * @param[in]          Type type  
 * @return         
 */
void printfList(Type type)
{
	int i = 0;
	int *p;
	char *q;

	switch(type)
	{
		case INT:
			for(; i < sizeList(); i++)
			{
				p = (int *)getList(i);
				printf("getList(%d) = %d\n", i, *p);
			}
			break;
		case CHAR:
			for(; i < sizeList(); i++)
			{
				q = (char *)getList(i);
				printf("getList(%d) = %c\n", i, *q);
			}
			break;
		default:
			break;
	}

	printf("\n");

}


/**
 * @fn       List *cut_exchangeList(int index)
 * @brief    从index位置节点截断链表，将前后两段表重新组-
             合。成功则返回链表头节点指针
 * @param[in]          int index  
 * @return         List
 */
List *cut_exchangeList(int index)/* 此函数可看作是将头节点和截断点节点互换位置 */
{
	Node *cutNode = getNode(index);
	Node *temp = (Node *)malloc(sizeof(Node));

#if 0
	temp->prev = pNode->prev;
	temp->next = pNode->next;
	temp->data = pNode->data;
	//截断并重组
	cutNode->prev->next = list->head;
	cutNode->next->prev = list->head;
	cutNode->prev = list->head->prev;
	cutNode->next = list->head->next;
	list->head->prev = temp->prev;
	list->head->next = temp->next;
	list->head->prev->next = temp;
	list->head->next->prev = temp;
#endif
	//暂存链表头节点指针
	temp->prev = list->head->prev;
	temp->next = list->head->next;
	//截断并重组
	list->head->prev = cutNode->prev;
	list->head->next = cutNode->next;
	cutNode->prev = temp->prev;
	cutNode->next = temp->next;
	list->head->prev->next = list->head;
	list->head->next->prev = list->head;
	cutNode->prev->next = cutNode;
	cutNode->next->prev = cutNode;

	if(!list->head)
	{
		return NULL;
	}

	free(temp);

	return list;
}


