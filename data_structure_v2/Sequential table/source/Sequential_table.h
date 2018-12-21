/********************************************************************************

 *************************Copyright (C), 2018, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : Sequential_table.h
 * @brief   		  : Sequential_table.c header file
 * @author       : gw
 * @version        : 1.0
 * @date          : 2018-12-01
 * 
 * 
 * @note History:
 * @note        :  2018-12-01
 * @note        : 
 *   Modification: Created file

********************************************************************************/

#ifndef __SEQUENTIAL_TABLE_H__
#define __SEQUENTIAL_TABLE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/* 头文件 */
#include "..\..\common\type.h"




/* 类型定义 */
typedef struct tagtable
{
	void *data;		//顺序表数据指针
	U32 count;		//顺序表元素计数
	U32 size;		//顺序表存储容量
}Table;
/* 查找顺序表元素的方式 */
typedef enum taghowtofind
{
	POSITION = 0,
	ELEMENT = 1
}HowToFind;
/* 元素在顺序表中的位置和元素值 */
typedef struct tagTableElement
{
	U32 position;
	void *element;
}TableElem;



/* 全局函数声明 */
extern Table *initTable(Type type ,U32 size);		//初始化顺序表
extern void printfTable(Type type);					//打印顺序表元素
extern void freememory(Table *table);				//是否顺序表占用的堆内存
extern status insertTable(Type type, U32 index, void *pdata);//插入数据到顺序表指定位置
extern status deleteTable(Type type, U32 index);	//删除index位置的元素
extern TableElem selectTable(Type type, HowToFind way, U32 index, void *elem);//按位置或元素值查找顺序表元素


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __SEQUENTIAL_TABLE_H__ */
