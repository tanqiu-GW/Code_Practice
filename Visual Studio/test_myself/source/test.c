/********************************************************************************

 *************************Copyright (C), 2018, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : test.c
 * @brief   		  : .C file function description
 * @author       : gw
 * @version        : 1.0
 * @date          : 2018-11-24
 * 
 * 
 * @note History:
 * @note        : 用于测试一些逻辑及功能
 * @note        : 
 *   Modification: Created file

********************************************************************************/
#if 0
/* 头文件 */
#include <stdio.h>
#include <string.h>


/* 宏定义 */
#define N	10


/* 局部变量 */



/* 局部函数 */
static void fun(char *w, int n);
static void swap(int *data1, int *daba2);



void fun(char *w, int n)
{
	char t, *s1, *s2;

	s1 = w;
	s2 = w + n -1;
	while(s1 <s2)
	{
		t = *s1++;
		*s1 = *s2--;
		*s2 = t;
	}
}



void swap(int *data1, int *data2)//此函数无法交换两个数据的位置，data1,data2还是指向原来的数据
{
	int *temp;

	temp = data1;
	data1 = data2;
	data2 = temp;
}



int main(void)
{
#if 0
	{
		char str[N][81], *sp;
		int i;

		for(i = 0; i < N; i++)
		{
			gets(str[i]);
		}

		sp = str[0];
		for(i = 1; i < N; i++)
		{
			if(strlen(sp) < strlen(str[i]))
			{
				sp = str[i];
			}
		}
		printf("length = %d,sp is %s\n", strlen(sp), sp);
	}
//#else
	{
		char p[] = "1234567";

		fun(p, strlen(p));
		puts(p);
	}


	{
		int x = 3, y = 5, *p = &x, *q = &y;

		swap(p, q);
		printf("%d,%d\n", *p, *q);
		swap(&x, &y);
		printf("%d,%d\n", *p, *q);
	}
#endif

	return 0;
}
#endif

# include<stdio.h>
#include<string.h>
# include<malloc.h>

struct Student
{
	char name[100];

};

int main(void)
{
	int len, i;
	struct Student * pst;
	char temp[100] = { 0 };

	printf("number of students:\n");
	scanf_s("%d", &len);
	//pst = (struct Student *)malloc(len * sizeof(struct Student));

	for (i = 0; i < len; i++)
	{
		printf("input the name of NO.%d\n", i + 1);
		printf("name:");
		pst = (struct Student *)malloc(sizeof(struct Student));
		//scanf_s("%c", temp);
		//fgets(temp, 100, stdin);
		gets_s(temp, 100);
		strcpy_s(pst->name,strlen(temp),temp);
	}

	return 0;

}


/*********************************文件尾********************************
***********************************************************************/
