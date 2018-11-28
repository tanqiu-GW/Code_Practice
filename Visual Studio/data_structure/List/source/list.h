/********************************************************************************

 *************************Copyright (C), 2018, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : list.h
 * @brief   		  : list.c header file
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

#ifndef __LIST_H__
#define __LIST_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


//节点结构
typedef struct _Node
{
    struct _Node *prev;
    struct _Node *next;
    void *data;
}Node;

//链表头节点和节点数
typedef struct _List
{
    Node *head;
    int count;
}List;

//链表数据类型
typedef enum _Type
{
	INT = 0,
	CHAR = 1,
	STRUCT = 2
}Type;



//全局函数
extern List *createList(void);			//创建双向链表。成功返回头节点，否则返回NULL
extern int destroyList(void);			//销毁双向链表。成功返回0，否则返回-1
extern int isEmptyList(void);			//双向链表是否为空。为空返回0
extern int sizeList(void);				//返回双向链表大小
extern void *getList(int index);		//获取双向链表第index位置的元素。成功则返回节点指针，否则返回NULL
extern void *getFirstList(void);		//获取双向链表第一个元素。成功则返回节点指针
extern void *getLastList(void);			//获取双向链表最后一个元素
extern int insertList(int index, void *pval);//将val插入到index位置。成功返回0
extern int insertFirstList(void *pval);//将val插入到表头。成功返回0
extern int insertLastList(void *pval);//将val插入到表尾。成功返回0
extern int deleteList(int index);		//删除双向链表index位置的节点。成功返回0
extern int deleteFirstList(void);	//删除表头节点
extern int deleteLastList(void);		//删除表尾节点
extern void printfList(Type type);		//打印双向链表

//从index位置节点截断链表，将前后两段表重新组合。例如a->b->c->d->e，从c截断后重组为
extern List *cut_exchangeList(int index);//d->e->c->a->b链表。成功返回链表头节点指针


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __LIST_H__ */
