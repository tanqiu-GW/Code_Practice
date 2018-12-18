/********************************************************************************

 *************************Copyright (C), 2018, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : Sequential_table.c
 * @brief   		  : .C file function description
 * @author       : gw
 * @version        : 1.0
 * @date          : 2018-12-01
 * 
 * 
 * @note History:
 * @note        : 顺序表功能函数 2018-12-01
 * @note        : 
 *   Modification: Created file

********************************************************************************/

/* 头文件 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "Sequential_table.h"



/* 局部变量 */
static Table *table;



/**
 * @fn       Table *initTable(Type type, int size)
 * @brief    初始化顺序表
 * 
 * @param[in]          Type type  
 * @param[in]        int size   
 * @return         
 */
Table *initTable(Type type, U32 size)
{
	table = (Table *)malloc(sizeof(Table));	//为顺序表指针申请动态内存

	switch (type)		//为顺序表元素申请动态内存
	{
		case INT:
			table->data = (int *)malloc(sizeof(int) * size);
			memset(table->data, 0, sizeof(int) * size);
			break;
		case CHAR:
			table->data = (char *)malloc(sizeof(char) * size);
			memset(table->data, 0, sizeof(char) * size);
		default:
			break;
	}

	if((!table) || (!table->data))	//申请内存失败
	{
		printf("初始化顺序表失败\n");
		exit(0);
	}
	
	table->count = 0;
	table->size = size;

	return table;
}
#if 1
/**
 * @fn       void printfTable(Type Type)
 * @brief    打印顺序表元素
 *   
 * @param[in]        Type type    
 * @return         
 */
void printfTable(Type type)
{
	U32 i = 0;
	U32 *data1;
	U8 *data2;
	
	switch (type)
	{
		case INT:
		#if 0
			for(; i < table->count; i++)
			{												//table.data声明为void *类型。
				data1 = (int *)table->data++;				//此处编译不通过，报错void *未知大小。
				printf("getTableData(%d) = %d\n", i, *data1);//原因是指针大小未知，不能进行++运算。
			}												//但是我做了强制转换为int型指针了，还是报错
			break;											//此时报错原因不知。
		#endif
			data1 = (int *)table->data;
			for(; i < table->count; i++)
			{
				printf("getTableData(%d) = %d\n", i, *data1);
				data1++;
			}
			break;
		case CHAR:
			data2 = (char *)table->data;
			for(; i < table->count; i++)
			{
				//data2 = (char *)table->data++;
				printf("getTableData(%d) = %c\n", i, *data2);
				data2++;
			}

			if(table->count > 0)
			{
				printf("the full string is [%s]", (char *)table->data);
			}
			break;
		default:
			break;
	}
	printf("\n");
}
#endif


