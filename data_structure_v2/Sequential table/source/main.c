/********************************************************************************

 *************************Copyright (C), 2018, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : main.c
 * @brief   		  : .C file function description
 * @author       : gw
 * @version        : 1.0
 * @date          : 2018-12-01
 * 
 * 
 * @note History:
 * @note        : 顺序表测试主函数 2018-12-01
 * @note        : 
 *   Modification: Created file

********************************************************************************/

/* 头文件 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "type.h"
#include "Sequential_table.h"





int main(void)
{
	Table *table;

	table = initTable(INT, 10);
#if 0
	U32 test = 0;
	test++;
	table->data = &test;
	table->count++;
#endif
	printfTable(INT);

	return 0;
}


