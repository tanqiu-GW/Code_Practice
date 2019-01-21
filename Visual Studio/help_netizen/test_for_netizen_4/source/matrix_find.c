/********************************************************************************

 *************************Copyright (C), 2018, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : matrix_find.c
 * @brief   		  : .C file function description
 * @author       : gw
 * @version        : 1.0
 * @date          : 2018-11-22
 * 
 * 
 * @note History:
 * @note        : 矩阵最大值查找主函数 2018-11-22
 * @note        : 
 *   Modification: Created file

********************************************************************************/

#include <stdio.h>
#include <malloc.h>


static void swap(int *data1, int *data2);
static int **row_max(int **matrix, int row_num, int colum_num);
static int **colum_max(int **matrix, int row_num, int colum_num);


int main(void)
{
	int **tmp;
	int matrix[3][4];
	int colum_num = sizeof(matrix[0]) / sizeof(int);
	int row_num = (sizeof(matrix) / sizeof(int)) / (sizeof(matrix[0]) / sizeof(int));

	printf("please input data\n");
	for(int i = 0; i < row_num; i++)
	{
		for(int j = 0; j < colum_num; j++)
			scanf_s("%d", &matrix[i][j]);
	}

	tmp = row_max((int **)matrix, row_num, colum_num);

	printf("output data\n");
	for(int n = 0; n < row_num; n++)
	{
		swap(&matrix[n][0], &matrix[n][tmp[n][1]]);
		for(int k = 0; k < colum_num; k++)
		{
			printf("%d ", matrix[n][k]);
		}
		printf("\n");
	}

	for(int q = 0; q < row_num; q++)
		free(tmp[q]);
	free(tmp);
	
	return 0;
}



/**
 * @fn       void swap(int * data1, int * data2)
 * @brief    交换两个数据
 * 
 * @param[in]          int * data1  
 * @param[in]        int * data2  
 * @return         
 */
void swap(int * data1, int * data2)
{
	int tmp;

	tmp 	= *data1;
	*data1	= *data2;
	*data2	= tmp;
}

/**
 * @fn       int **row_max(int * * matrix, int row_num, int colum_num)
 * @brief    找出矩阵每行最大值，放在每行第一个位置
 * 
 * @param[in]          int * * matrix  
 * @param[in]        int row_num     
 * @param[in]        int colum_num   
 * @return         int **
 */
int **row_max(int * * matrix, int row_num, int colum_num)
{
	int **tmp;

	tmp = (int **)malloc(row_num * sizeof(int *));
	for(int m = 0; m < row_num; m++)
	{
		tmp[m] = (int *)malloc(2 * sizeof(int));
	}

	for(int i = 0; i < row_num; i++)
	{
		int max = *((int *)matrix + i * colum_num);	//每行的第一个元素
		for(int j = 0; j< colum_num; j++)
		{
			if(max < *((int *)matrix + i * colum_num + j))
			{
				max = *((int *)matrix + i * colum_num + j);
				tmp[i][0] = max;
				tmp[i][1] = j;
			}
		}
	}

	return tmp;
}

/**
 * @fn       int **colum_max(int * * matrix, int row_num, int colum_num)
 * @brief    找出矩阵每列最大值，放在每列第一个位置
 * 
 * @param[in]          int * * matrix  
 * @param[in]        int row_num     
 * @param[in]        int colum_num   
 * @return         int **
 */
int **colum_max(int * * matrix, int row_num, int colum_num)
{
}

