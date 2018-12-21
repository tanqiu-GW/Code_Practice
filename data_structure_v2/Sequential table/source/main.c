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

#include "..\..\common\type.h"
#include "Sequential_table.h"





int main(void)
{
	Table *table1 = initTable(INT, 10);
	int a = 1;
	insertTable(INT, 1, &a);
	insertTable(INT, 2, &a);
	deleteTable(INT, 2);
	printfTable(INT);
	freememory(table1);

	Table *table2 = initTable(CHAR, 10);
	char b = 'g', c = 'w';
	insertTable(CHAR, 1, &b);
	insertTable(CHAR, 2, &c);
	deleteTable(CHAR, 2);
	printfTable(CHAR);
	freememory(table2);

	return 0;
}


