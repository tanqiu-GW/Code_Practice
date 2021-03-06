/******************************************************************************
 * 文 件 名 : list.h
 * 
 * 版权说明 : 版权所有(c) 2018  航空工业上海航空电器有限公司
 * 
 * 文件描述 : list.c 的头文件
 * 
 * 修改日志 : 
 * ====================
 *     V1.00.00 2018-11-07 gw     创建
 * 
 * 备    注 : 
 * 
 ******************************************************************************/

#ifndef __LIST_H__
#define __LIST_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/******************************************************************************
 *    头     文     件
 ******************************************************************************/

/******************************************************************************
 *   常   量   定   义
 ******************************************************************************/

/******************************************************************************
 *   类   型   定   义
 ******************************************************************************/
typedef struct _Node		//双向链表节点类型
{
	struct _Node *prev;
	struct _Node *next;
	void *data;
}Node;

typedef struct _List
{
	Node *head;			//记录链表头
	int count;			//记录链表元素个数
}List;

typedef enum _datatype
{
	INT = 0,
	CHAR = 1
}datatype;

/******************************************************************************
 *   全 局 变 量 声 明
 ******************************************************************************/

/******************************************************************************
 *   全 局 函 数 声 明
 ******************************************************************************/
extern List *createList(void);				//创建双向链表。成功返回链表指针，否则返回NULL
extern int isEmptyList(void);			//链表是否为空。为空返回1，否则返回0
extern int sizeList(void);			//返回双向链表大小
extern int destroyList(void);			//销毁链表，成功返回0，否则返回-1
extern void *getList(int index);//获取链表中第index位置元素。成功返回节点指针，否则返回NULL
extern void *getHeadList(void);		//获取链表第一个元素。成功返回节点指针，否则返回NULL
extern void *getTailList(void);		//获取链表最后一个元素。成功返回节点指针，否则返回NULL
extern int insertList(int index, void *pval);//将val插入到index位置。成功返回0，否则返回-1
extern int insertHeadList(void *pval);//插入到表头。成功返回0，否则返回-1
extern int insertTailList(void *pval);//插入到表尾。成功返回0，否则返回-1
extern int deleteList(int index);//删除链表中第index位置节点。成功返回0，否则返回-1
extern int deleteHeadList(void);
extern int deleteTailList(void);
extern void printfList(int type);//打印链表中的全部数据

//从index位置截断链表，并互换前后两段链表后重新连接。例如a->b->c->d->e->f转换为d->e->f->c->a->b
extern int cut_exchangeList(int index);//成功则返回0，否则返回1


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LIST_H__ */


/******************************************************************************
 *    文     件     尾
 ******************************************************************************/


