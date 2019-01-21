/********************************************************************************

 *************************Copyright (C), 2019, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : array_exchange.c
 * @brief   	 : 二维数组行交换
 * @author       : gw
 * @version      : 1.0
 * @date         : 2019-01-10
 * 
 * 
 * @note History:
 * @note        : 
 * @note        : 
 * Modification : Created file

********************************************************************************/
/* 头文件 */
#include <stdio.h>
#include <string.h>

/* 宏定义 */
#define ROW_NUM		5
#define COLUMN_NUM	5

static int array_exchange(int row_num1, int row_num2, int array[][COLUMN_NUM]);

/* row_num1行和row_num2行交换 */
int array_exchange(int row_num1, int row_num2, int array[][COLUMN_NUM])
{
	int (*p)[ROW_NUM] = array;	//定义二维数组指针，指向array
	if((row_num1 > ROW_NUM) || (row_num2 > ROW_NUM))
	{
		printf("exceeding array size!");
		return -1;
	}
	int temp[COLUMN_NUM];
	memcpy(temp, *(p + row_num1), COLUMN_NUM * sizeof(int));
	memcpy(*(p + row_num1), *(p + row_num2), COLUMN_NUM * sizeof(int));
	memcpy(*(p + row_num2), temp, COLUMN_NUM * sizeof(int));

	return 0;
}

int main(void)
{
	int array[5][5] = {{1,1,1,1,1},{2,2,2,2,2},
		{3,3,3,3,3},{4,4,4,4,4},{5,5,5,5,5}};	
	array_exchange(0, 4, array);
	
	return 0;
}