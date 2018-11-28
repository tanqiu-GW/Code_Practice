/********************************************************************************

 *************************Copyright (C), 2018, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : main.c
 * @brief   		  : .C file function description
 * @author       : gw
 * @version        : 1.0
 * @date          : 2018-11-08
 * 
 * 
 * @note History:
 * @note        : 循环双向链表测试主函数 2018-11-08
 * @note        : 
 *   Modification: Created file

********************************************************************************/
#include <stdio.h>
#include "list.h"



int main(void)
{
	{
		int i = 0;
		int arr[] = {11, 22, 33, 44, 55, 66, 77, 88, 99};

		List *list = createList();
		for(; i < sizeof(arr) / sizeof(int); i++)
		{
			insertLastList(&arr[i]);
		}
		printfList(INT);
		deleteLastList();
		printfList(INT);
		list = cut_exchangeList(3);
		printfList(INT);

		destroyList();
	}

	{
		int j = 0;
		//char *phead;
		char string[] = "Sharing is happy!";
		printf("%s\n", string);

		List *string_list = createList();
		for(; j < sizeof(string) / sizeof(char); j++)
		{
			insertLastList(&string[j]);
		}
		printfList(CHAR);
		//phead = (char *)getList(0);
		//printf("%s\n", phead);
		printf("The full string is [%s].\n", (char *)getList(0));

		destroyList();
	}
	
	return 0;
}

