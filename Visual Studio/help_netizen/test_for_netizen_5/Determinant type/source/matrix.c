/********************************************************************************

 *************************Copyright (C), 2018, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : matrix.c
 * @brief   		  : .C file function description
 * @author       : gw
 * @version        : 1.0
 * @date          : 2018-12-05
 * 
 * 
 * @note History:
 * @note        : 关于矩阵运算的一些函数 2018-12-05
 * @note        : 
 *   Modification: Created file

********************************************************************************/
/* 头文件 */
#include <stdio.h>
#include <string.h>
#include <malloc.h>



/* 类型定义 */
typedef struct tagMatrix
{
	int row;	//行数
	int column;	//列数
	int **matrix;	//矩阵
}t_Matrix;



/* 局部变量 */
static t_Matrix *l_matrix[2];		//声明矩阵类型指针



/* 局部函数 */
t_Matrix *createMatrix(int row, int column);			//创建row*column矩阵
void inputMatrix(t_Matrix *matrix);						//输入矩阵元素值
void outputMatrix(t_Matrix *matrix);					//输出矩阵，打印
void freeMatrix(t_Matrix *matrix);						//释放为矩阵申请的堆内存空间
int determinant_caculation(t_Matrix *matrix);			//行列式计算(采用对角线计算方法)
t_Matrix *transposeMatrix(t_Matrix *matrix);			//求矩阵转置
t_Matrix *add_subMatrix(t_Matrix *matrix1, t_Matrix *matrix2);//矩阵加减
t_Matrix *multiplyMatrix(t_Matrix *matrix1, t_Matrix *matrix2);//两矩阵相乘
t_Matrix *number_multiplyMatrix(int number, t_Matrix *matrix);//数与矩阵相乘
t_Matrix *inverseMatrix(t_Matrix *matrix);				//求逆矩阵



/**
 * @fn       t_Matrix *createMatrix(int row, int column)
 * @brief    创建row*column矩阵，为其动态申请内存
 * 
 * @param[in]          int row     
 * @param[in]        int column  
 * @return         t_Matrix *
 */
t_Matrix *createMatrix(int row, int column)
{
	if(row <= 0 || column <= 0)
	{
		printf("please input correct row or column .\n");
		return NULL;
	}

	t_Matrix *l_matrix = (t_Matrix *)malloc(sizeof(t_Matrix *));
	l_matrix->row = row;
	l_matrix->column = column;

	//为矩阵申请堆内存
	l_matrix->matrix = (int **)malloc(sizeof(int *) * row);
	//矩阵每行申请空间
	for(int k = 0; k < row; k++)
	{
		l_matrix->matrix[k] = (int *)malloc(sizeof(int) * column);
		memset(l_matrix->matrix[k], 0, sizeof(int) * column);		//初始化元素为0
	}

	if(l_matrix == NULL)
	{
		printf("create matrix failed.\n");
		return NULL;
	}

	return l_matrix;
}

/**
 * @fn       void inputMatrix(t_Matrix * matrix)
 * @brief    输入矩阵元素
 * 
 * @param[in]          t_Matrix * matrix  
 * @return         
 */
void inputMatrix(t_Matrix * matrix)
{
	//输入n阶矩阵元素
	printf("please input matrix data\n");
	for(int i = 0; i < matrix->row; i++)
	{
		for(int j = 0; j < matrix->column; j++)
		{
			scanf_s("%d", &matrix->matrix[i][j]);
		}
	}
}

/**
 * @fn       void outputMatrix(t_Matrix * matrix)
 * @brief    输出打印矩阵元素
 * 
 * @param[in]          t_Matrix * matrix  
 * @return         
 */
void outputMatrix(t_Matrix * matrix)
{
	printf("after the operation of matrix\n");
	for(int i = 0; i < matrix->row; i++)
	{
		for(int j = 0; j < matrix->column; j++)
		{
			printf("%d", matrix->matrix[i][j]);
		}
		printf("\n");
	}
}

/**
 * @fn       void freeMatrix(t_Matrix * matrix)
 * @brief    释放矩阵内存
 * 
 * @param[in]          t_Matrix * matrix  
 * @return         
 */
void freeMatrix(t_Matrix * matrix)
{
	for(int i = 0; i < matrix->row; i++)
	{
		free(matrix->matrix[i]);
	}
	free(matrix->matrix);
	free(matrix);
}

/**
 * @fn       int determinant_caculation(t_Matrix * matrix)
 * @brief    计算矩阵行列式的值(采用对角线方法计算行列式)
 * 
 * @param[in]          t_Matrix * matrix  
 * @return         int
 */
int determinant_caculation(t_Matrix * matrix)
{
	static int result;

	if(matrix->row != matrix->column)
	{
		printf("matrix is not square!");
		return -1;
	}

	if(matrix->row == 1)
	{
		return matrix->matrix[0][0];
	}

	t_Matrix *temp = createMatrix(matrix->row - 1, matrix->row - 1);

	for(int i = 0; i < matrix->row; i++)
	{
		for(int j = 0; j < matrix->row - 1; j++)
		{
			for(int k = 0; k < matrix->row - 1; k++)
			{
				int flag;
				if(j < i)
					flag = 0;
				else
					flag = 1;
				temp->matrix[j][k] = matrix->matrix[j + flag][k + 1];
			}
		}
		//每项的符号位
		int sign = -1;
		if(i % 2 == 0)
			sign = 1;
		//递归求和
		result += sign * matrix->matrix[i][0] * determinant_caculation(temp);
	}

	//freeMatrix(temp);

	return result;
}

/**
 * @fn       t_Matrix *transposeMatrix(t_Matrix * matrix)
 * @brief    求矩阵的转置矩阵
 * 
 * @param[in]          t_Matrix * matrix  
 * @return         t_Matrix *
 */
t_Matrix *transposeMatrix(t_Matrix * matrix)
{
	t_Matrix *result;

	result = createMatrix(matrix->row, matrix->column);	//创建一个临时空间
	
	for(int i = 0; i < matrix->row; i++)
	{
		for(int j = 0; j< matrix->column; j++)
		{
			result->matrix[i][j] = matrix->matrix[j][i];
		}
	}

	return result;
}

/**
 * @fn       add_subMatrix(t_Matrix * matrix1, t_Matrix matrix2)
 * @brief    矩阵加减
 * 
 * @param[in]          t_Matrix * matrix1  
 * @param[in]        t_Matrix * matrix2    
 * @return         t_matrix *
 */
t_Matrix *add_subMatrix(t_Matrix * matrix1, t_Matrix *matrix2)
{
	if((matrix1->row != matrix2->row) || (matrix1->column != matrix2->column))
	{
		printf("only homogeneous matrix can add or sub.\n");
		return NULL;
	}

	t_Matrix *result = createMatrix(matrix1->row, matrix1->column);

	for(int i = 0; i < result->row; i++)
	{
		for(int j = 0; j < result->column; j++)
		{
			result->matrix[i][j] = matrix1->matrix[i][j] + matrix2->matrix[i][j];
		}
	}

	return result;
}

/**
 * @fn       t_Matrix *multiplyMatrix(t_Matrix * matrix, t_Matrix matrix2)
 * @brief    两矩阵相乘
 * 
 * @param[in]          t_Matrix * matrix  
 * @param[in]        t_Matrix *matrix2   
 * @return         t_Matrix*
 */
t_Matrix *multiplyMatrix(t_Matrix * matrix1, t_Matrix *matrix2)
{
	if(matrix1->column != matrix2->row)
	{
		printf("need to be left row right column\n");
		return NULL;
	}

	t_Matrix *result = createMatrix(matrix1->row, matrix2->column);

	for(int i = 0; i < result->row; i++)
	{
		for(int j = 0; j< result->column; j++)
		{
			for(int k = 0; k < result->column; k++)
			{
				result->matrix[i][j] += matrix1->matrix[i][k] * matrix2->matrix[k][j];
			}
		}
	}

	return result;
}

/**
 * @fn       t_Matrix *number_multiplyMatrix(int number, t_Matrix * matrix)
 * @brief    数与矩阵的乘法
 * 
 * @param[in]          int number         
 * @param[in]        t_Matrix * matrix  
 * @return         t_Matrix
 */
t_Matrix *number_multiplyMatrix(int number, t_Matrix * matrix)
{
	t_Matrix *result = createMatrix(matrix->row, matrix->column);

	for(int i = 0; i < result->row; i++)
	{
		for(int j = 0; j < result->column; j++)
		{
			result->matrix[i][j] = number * matrix->matrix[i][j];
		}
	}

	return result;
}

/**
 * @fn       t_Matrix *inverseMatrix(t_Matrix * matrix)
 * @brief    求矩阵的逆(伴随矩阵除以行列式值)
 * 
 * @param[in]          t_Matrix * matrix  
 * @return         t_Matrix
 */
t_Matrix *inverseMatrix(t_Matrix * matrix)
{
	if(determinant_caculation(matrix) == 0)
	{
		printf("invers matrix doesn't exist.\n");
		return NULL;
	}

	int determinant_result = determinant_caculation(matrix);
	t_Matrix *result = matrix;
	t_Matrix *temp = createMatrix(matrix->row, matrix->row - 1);

	for(int i = 0; i < matrix->row; i++)
	{
		for(int j = 0; j < matrix->row - 1; j++)
		{
			for(int m = 0; m < matrix->row - 1; m++)
			{
				for(int n = 0; n < matrix->row - 1; n++)
				{
					int flag1 = 0, flag2 = 0;
					
					if(m < i)
						flag1 = 0;
					else
						flag1 = 1;
					if(n < j)
						flag2 = 0;
					else
						flag2 = 1;

					temp->matrix[m][n] = result->matrix[m + flag1][n + flag2];
				}
			}
			int sign = -1;
			if((i + j) % 2 == 0)
				sign = 1;
			result->matrix[j][i] = sign * determinant_caculation(temp) / determinant_result;
		}
	}

	return result;
}





int main(void)
{
	l_matrix[1] = createMatrix(2, 2);
	l_matrix[2] = createMatrix(2, 2);

	
	inputMatrix(l_matrix[1]);
	inputMatrix(l_matrix[2]);
	outputMatrix(l_matrix[1]);
	outputMatrix(l_matrix[2]);

	t_Matrix *result1;
	result1 = transposeMatrix(l_matrix[1]);
	outputMatrix(result1);
	freeMatrix(result1);
	t_Matrix *result2;
	result2 = add_subMatrix(l_matrix[1], l_matrix[2]);
	outputMatrix(result2);
	freeMatrix(result2);
	t_Matrix *result3;
	result3 = multiplyMatrix(l_matrix[1], l_matrix[2]);
	outputMatrix(result3);
	freeMatrix(result3);
	t_Matrix *result4;
	result4 = number_multiplyMatrix(2, l_matrix[1]);
	outputMatrix(result4);
	freeMatrix(result4);
#if 0	
	int result5;
	result5 = determinant_caculation(l_matrix[1]);
	t_Matrix *result6;
	result6 = inverseMatrix(l_matrix[1]);
	outputMatrix(result6);
	freeMatrix(result6);
#endif	
	freeMatrix(l_matrix[1]);
	freeMatrix(l_matrix[2]);
	
	return 0;
}



