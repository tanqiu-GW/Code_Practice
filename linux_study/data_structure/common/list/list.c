/******************************************************************************
 * 文 件 名 : list.c
 * 
 * 版权说明 : 版权所有(c) 2018  航空工业上海航空电器有限公司
 * 
 * 文件描述 : 双向链表
 * 
 * 修改日志 : 
 * ====================
 *     V1.00.00 2018-11-07 gw     创建
 * 
 * 备    注 : 
 * 
 ******************************************************************************/

/******************************************************************************
 *    头     文     件
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "list.h"

/******************************************************************************
 *   常   量   定   义
 ******************************************************************************/

/******************************************************************************
 *   类   型   定   义
 ******************************************************************************/

/******************************************************************************
 *   全 局 变 量 定 义
 ******************************************************************************/

/******************************************************************************
 *   局 部 变 量 定 义
 ******************************************************************************/
static List *list = NULL;

/******************************************************************************
 *   局 部 函 数 声 明
 ******************************************************************************/
static Node *createNode(void *pval);		//创建节点
static Node *getNode(int index);//获取index位置节点
static Node *getHeadNode(void);
static Node *getTailNode(void);

/******************************************************************************
 *
 * 函 数 名 : createNode
 *
 * 函数功能 : 新建节点。成功，返回节点指针；否则返回FULL。
 *
 * 参    数 : void * pval   - 节点数据域的值
 *
 * 返 回 值 : Node - 节点指针
 *
 * 备    注 : 
 *
 ******************************************************************************/
Node *createNode(void * pval)
{
	Node *pNode = NULL;
	pNode = (Node *)malloc(sizeof(Node));
	
	if(!pNode)
	{
		printf("create node error!\n");
		return NULL;
	}

	//默认pNode的前一节点和后一节点都指向它自身
	pNode->prev = pNode->next = pNode;
	//节点数据域值为pval
	pNode->data = pval;

	return pNode;
}

/******************************************************************************
 *
 * 函 数 名 : getNode
 *
 * 函数功能 : 获取第index位置的节点，返回该节点指针
 *
 * 参    数 : List list   - 链表
 *            int index   - 第index个位置节点
 *
 * 返 回 值 : Node - 第index位置节点指针
 *
 * 备    注 : 
 *
 ******************************************************************************/
Node *getNode(int index)
{
	int i = 0, j = 0;
	Node *pNode = NULL;
	
	if((index < 0) || (index > list->count))
	{
		printf("failed! index out of bound!\n");
		return NULL;
	}

	//正向查找
	if(index <= (list->count / 2))
	{
		pNode = list->head->next;
		while((i++ < index))
		{
			pNode = pNode->next;
		}
	}
	else	//反向查找
	{
		pNode = list->head->prev;
		while((j++) < (list->count - index - 1))
		{
			pNode = pNode->prev;
		}
	}

	return pNode;
}

/******************************************************************************
 *
 * 函 数 名 : getHeadNode
 *
 * 函数功能 : 获取链表头节点
 *
 * 参    数 : List list   - 双向链表
 *
 * 返 回 值 : 无
 *
 * 备    注 : 
 *
 ******************************************************************************/
Node *getHeadNode(void)
{
	return getNode(0);
}

/******************************************************************************
 *
 * 函 数 名 : getTailNode
 *
 * 函数功能 : 获取链表尾节点
 *
 * 参    数 : List list   - 双向链表
 *
 * 返 回 值 : 无
 *
 * 备    注 : 
 *
 ******************************************************************************/
Node *getTailNode(void)
{
	return getNode(list->count - 1);
}



/******************************************************************************
 *
 * 函 数 名 : createList
 *
 * 函数功能 : 新建双向链表。成功，则返回0；否则，返回-1
 *
 * 参    数 : 无
 *
 * 返 回 值 : int - 是否创建成功
 *
 * 备    注 : 
 *
 ******************************************************************************/
List *createList(void)
{
//	List *list = NULL;		//这里存在空指针赋值的问题！空指针是没有分配物理内存的，
//	list->head = NULL;		//当给其赋值时，就无法访问此指针内存。
//	List *list = (List *)malloc(sizeof(List));//解决办法可以是先给其分配内存，再赋值
//	List list_memory;
//	List *list = &list_memory;	//或用此种方法给其分配实际的物理内存
//	list = &list_memory;
	list = (List *)malloc(sizeof(List));
	list->head = createNode(NULL);

	if(!list->head)
	{
		return NULL;
	}

	//设置节点个数为0
	list->count = 0;

	return list;
}

/******************************************************************************
 *
 * 函 数 名 : isEmptyList
 *
 * 函数功能 : 链表为空则返回1，不为空返回0
 *
 * 参    数 : List list   - 双向链表
 *
 * 返 回 值 : int - 是否为空
 *
 * 备    注 : 
 *
 ******************************************************************************/
int isEmptyList(void)
{
	return (list->count == 0);
}

/******************************************************************************
 *
 * 函 数 名 : sizeList
 *
 * 函数功能 : 返回链表当前节点数
 *
 * 参    数 : List list   - 双向链表
 *
 * 返 回 值 : int - 链表节点数
 *
 * 备    注 : 
 *
 ******************************************************************************/
int sizeList(void)
{
	return list->count;
}

/******************************************************************************
 *
 * 函 数 名 : getList
 *
 * 函数功能 : 获取双向链表中第index位置的元素。成功则返回节点值；否则返回-1
 *
 * 参    数 : List list   - 双向链表
 *            int index   - 获取节点的位置
 *
 * 返 回 值 : 无
 *
 * 备    注 : 
 *
 ******************************************************************************/
void *getList(int index)
{
	Node *pindex = getNode(index);
	if(!pindex)
	{
		printf("failed!\n");
		return NULL;
	}

	return pindex->data;
}

void *getHeadList(void)
{
	return getList(0);
}

void *getTailList(void)
{
	return getList(list->count - 1);
}

/******************************************************************************
 *
 * 函 数 名 : insertList
 *
 * 函数功能 : 将pval插入到index位置。成功返回0，否则返回-1
 *
 * 参    数 : List list     - 双向链表
 *            int index     - 插入位置
 *            void * pval   - 插入值
 *
 * 返 回 值 : int - 是否成功
 *
 * 备    注 : 
 *
 ******************************************************************************/
int insertList(int index, void * pval)
{
	Node *pindex;
	Node *pNode;

	//插入表头
	if(index == 0)
	{
		return insertHeadList(pval);
	}

	//获取要插入位置对应的节点
	pindex = getNode(index);
	if(!pindex)
	{
		return -1;
	}

	//创建节点
	pNode = createNode(pval);
	if(!pNode)
	{
		return -1;
	}
	pNode->next = pindex;
	pNode->prev = pindex->prev;
	pindex->prev->next = pNode;
	pindex->prev = pNode;
	//节点数+1
	list->count++;

	return 0;
}

/******************************************************************************
 *
 * 函 数 名 : insertHeadList
 *
 * 函数功能 : 在双向链表表头插入pval，成功返回0
 *
 * 参    数 : List list     - 双向链表
 *            void * pval   - 插入值
 *
 * 返 回 值 : int - 返回是否成功
 *
 * 备    注 : 
 *
 ******************************************************************************/
int insertHeadList(void * pval)
{
//	Node *pNode;

	Node *pNode = createNode(pval);
	if(!pNode)
	{
		return -1;
	}

	pNode->prev = list->head;
	pNode->next = list->head->next;
	list->head->next->prev = pNode;
	list->head->next = pNode;
	
	//节点数+1
	list->count++;

	return 0;
}

/******************************************************************************
 *
 * 函 数 名 : insertTailList
 *
 * 函数功能 : 插入pval到双向链表表尾，成功返回0
 *
 * 参    数 : List list     - 双向链表
 *            void * pval   - 插入值
 *
 * 返 回 值 : int - 返回是否插入成功
 *
 * 备    注 : 
 *
 ******************************************************************************/
int insertTailList(void * pval)
{
	Node *pNode;

	pNode = createNode(pval);
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

/******************************************************************************
 *
 * 函 数 名 : deleteList
 *
 * 函数功能 : 删除双向链表中index位置节点，成功返回0
 *
 * 参    数 : List list   - 双向链表
 *            int index   - 删除节点的位置
 *
 * 返 回 值 : int - 是否删除成功
 *
 * 备    注 : 
 *
 ******************************************************************************/
int deleteList(int index)
{
	Node *pNode;

	pNode = getNode(index);
	if(!pNode)
	{
		return -1;
	}

	pNode->prev->next = pNode->next;
	pNode->next->prev = pNode->prev;
	free(pNode);

	list->count--;

	return 0;
}

/******************************************************************************
 *
 * 函 数 名 : deleteHeadList
 *
 * 函数功能 : 删除表头节点,成功返回0
 *
 * 参    数 : List list   - 双向链表
 *
 * 返 回 值 : int - 是否删除成功
 *
 * 备    注 : 
 *
 ******************************************************************************/
int deleteHeadList(void)
{
	return deleteList(0);
}

/******************************************************************************
 *
 * 函 数 名 : deleteTailList
 *
 * 函数功能 : 删除表尾节点，成功返回0
 *
 * 参    数 : List list   - 双向链表
 *
 * 返 回 值 : int - 是否删除成功
 *
 * 备    注 : 
 *
 ******************************************************************************/
int deleteTailList(void)
{
	return deleteList(list->count - 1);
}

/******************************************************************************
 *
 * 函 数 名 : destroyList
 *
 * 函数功能 : 销毁双向链表，成功返回0
 *
 * 参    数 : List list   - 双向链表
 *
 * 返 回 值 : int - 是否销毁成功
 *
 * 备    注 : 
 *
 ******************************************************************************/
int destroyList(void)
{
	Node *pNode;
	Node *pTemp = NULL;

	if(!list->head)
	{
		printf("failed! list is NULL!\n");
		return -1;
	}

	pNode = list->head->next;
	while(pNode != list->head)
	{
		pTemp = pNode;
		pNode = pNode->next;
		free(pTemp);
	}

	free(list);
	list->head = NULL;
	list->count = 0;

	return 0;
}

/******************************************************************************
 *
 * 函 数 名 : printfList
 *
 * 函数功能 : 打印链表元素
 *
 * 参    数 : List *list   - 双向链表
 *            int type     - 打印数据域的数据类型
 *
 * 返 回 值 : 无
 *
 * 备    注 : 
 *
 ******************************************************************************/
void printfList(int type)
{
	int i,size;
	int *p1;
	char *p2;

	size = sizeList();

	switch (type)
	{
		case INT:
			for(i = 0; i < size; i++)
			{
				p1 = (int *)getList(i);
				printf("getList(%d) = %d\n", i, *p1);
			}
			break;
		case CHAR:
			for(i = 0;i < size; i++)
			{
				p2 = (char *)getList(i);
				printf("getList(%d) = %s\n", i, p2);
			}
			break;
		default:
			break;
	}
	
}


/******************************************************************************
 *
 * 函 数 名 : cut_exchangeList
 *
 * 函数功能 : 从指定位置节点截断，并互换两段表的位置。-
                  成功返回0
 *
 * 参    数 : int index   - 被截断节点的位置
 *
 * 返 回 值 : int - 是否完成截断并互换
 *
 * 备    注 : 
 *
 ******************************************************************************/
int cut_exchangeList(int index)
{
	Node *cutNode = getNode(index);
	Node *temp = (Node *)malloc(sizeof(Node));

	if(!cutNode)
	{
		return -1;
	}

	
	temp->prev = list->head->prev;
	temp->next = list->head->next;

	//截断并互换位置
	list->head->prev = cutNode->prev;
	list->head->next = cutNode->next;
	cutNode->prev = temp->prev;
	cutNode->next = temp->next;
	list->head->prev->next = list->head;
	list->head->next->prev = list->head;
	cutNode->prev->next = cutNode;
	cutNode->next->prev = cutNode;
//	list->head->prev->next = cutNode;
//	list->head->next->prev = cutNode;
//	cutNode->prev->next = list->head;
//	cutNode->next->prev = list->head;

	free(temp);
	
	return 0;
}


/******************************************************************************
 *    文     件     尾
 ******************************************************************************/


