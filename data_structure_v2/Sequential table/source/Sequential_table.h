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
#include "type.h"



/* 类型定义 */
typedef struct tagtable
{
	void *data;		//顺序表数据指针
	int count;		//顺序表元素计数
	int size;		//顺序表存储容量
}Table;





/* 全局函数声明 */
extern Table *initTable(Type type ,int size);		//初始化顺序表
extern void printfTable(Type type);					//打印顺序表元素


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __SEQUENTIAL_TABLE_H__ */
