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
/* 头文件 */
#include <stdio.h>
#include <string.h>


/* 宏定义 */
#define N	10


/* 局部变量 */



/* 局部函数 */
static void fun(char *w, int n);




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
#else
	{
		char p[] = "1234567";

		fun(p, strlen(p));
		puts(p);
	}
#endif
	return 0;
}

/*********************************文件尾********************************
***********************************************************************/
