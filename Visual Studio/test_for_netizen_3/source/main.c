/********************************************************************************

 *************************Copyright (C), 2018, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : main.c
 * @brief   		  : .C file function description
 * @author       : 找出两个数组不共有元素主函数
 * @version        : 1.0
 * @date          : 2018-11-20
 * 
 * 
 * @note History:
 * @note        : 2018-11-20
 * @note        : 
 *   Modification: Created file

********************************************************************************/
#include <stdio.h>

int same_flag = 0;

int compare_data(int data, int arr[])
{
	int same,diff;
	
	for(int i = 0; i < 12; i++)
	{
		if(!(data ^ arr[i]))
		{
			same = data;
			same_flag = 1;
			return same;
		}
		else
		{
			diff = data;
			continue;
		}
	}

	return diff;
}

int main(void)
{
#if 0
	int size1,size2;
	int arr1[size1],arr2[size2];

	printf("请输入两个数组的元素个数\n");
	scanf("%d %d", &size1, &size2);
#else
	int arr1[11],arr2[11];
	int data,diff;
//	int arr1[11] = {10,3,-5,2,8,0,3,5,-15,9,100},arr2[12] = {11,6,4,8,2,6,-5,9,0,100,8,1};
	printf("Please enter data into first array.\n");
	for(int i = 0; i < 11; i++)
	{
		scanf_s("%d", &arr1[i]);
	}
	printf("Please enter data into second array.\n");
	for(int j = 0; j < 11; j++)
	{
		scanf_s("%d", &arr2[j]);
	}
#endif
	//找出不是两数组共有元素
	printf("arr1 different data\n");
	for(int j = 0; j < 11; j++)
	{
		data = compare_data(arr1[j], arr2);
		if(!same_flag)
		{
			diff = data;
			printf("%d ", diff);
		}
		same_flag = 0;
	}
	printf("\n");
	printf("arr2 different data\n");
	for(int k = 0; k < 11; k++)
	{
		data = compare_data(arr2[k], arr1);
		if(!same_flag)
		{
			diff = data;
			printf("%d ", diff);
		}
		same_flag = 0;
	}

	return 0;
}


