/********************************************************************************

 *************************Copyright (C), 2019, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : main.c
 * @brief   		  : .C file function description
 * @author       : gw
 * @version        : 1.0
 * @date          : 2019-02-17
 * 
 * 
 * @note History:
 * @note        : 括号匹配，利用栈数据结构实现 2019-02-17
 * @note        : 简单起见，只进行了()、[]、{}括号匹配
 *   Modification: Created file

********************************************************************************/
/* 头文件 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\..\stack_array\source\stack.h"

/* 常量定义 */
#define MAX_STRING_LENGTH	1024
#define MAX_STACK_LENGTH	1024


/* 存储匹配结果的结构体 */
typedef struct tagMatchResult
{
	U32 failed;
	U32 successful;
}MatchResult;

/* 链接属性仅在本源文件的函数 */
static void parenthesesMatch(char *string);





/* 括号匹配函数，栈结构实现，类似于编译器中在线的括号检测 */
void parenthesesMatch(char * string)
{
	MatchResult small = {0, 0}, middle = {0, 0}, large = {0, 0};
	char *pchar;
	
	Stack_array *stack = createStackArray(strlen(string));
	pchar = string;

	while(*pchar != '\0')
	{
		switch(*pchar)
		{
			case '(':
				pushStackArray(stack, pchar);//开放符合入栈
				break;
			case '[':
				pushStackArray(stack, pchar);
				break;
			case '{':
				pushStackArray(stack, pchar);
				break;
			case ')':
				if(isEmptyStackArray(stack))	//封闭符号判断是否匹配
				{
					small.failed += 1;	//如果空栈，则括号不匹配
				}
				else
				{
					if(popAndreturnTOPstackArray(stack) == '(')//若出栈符号与封闭符号对应，则匹配成功
					{
						small.successful += 1;
					}
					else
					{
						small.failed += 1;
					}
				}
				break;
			case ']':
				if(isEmptyStackArray(stack))
				{
					middle.failed += 1;
				}
				else
				{
					if(popAndreturnTOPstackArray(stack) == '[')
					{
						middle.successful += 1;
					}
					else
					{
						middle.failed += 1;
					}
				}
				break;
			case '}':
				if(isEmptyStackArray(stack))
				{
					large.failed += 1;
				}
				else
				{
					if(popAndreturnTOPstackArray(stack) == '{')
					{
						large.successful += 1;
					}
					else
					{
						large.failed += 1;
					}
				}
				break;
			default:
				break;
		}

		pchar++;		
	}

	if(*pchar == '\0')	//考虑到读完字符时，栈中若还有括号，则匹配失败
	{
		if(small.successful != 0)
		{
			printf("%d pairs of small parentheses match successful!\n", small.successful);
		}
		if(small.failed != 0)
		{
			printf("%d pairs of small parentheses match failed!\n", small.failed);
		}

		if(middle.successful != 0)
		{
			printf("%d pairs of middle parentheses match successful!\n", middle.successful);
		}
		if(middle.failed != 0)
		{
			printf("%d pairs of middle parentheses match failed!\n", middle.failed);
		}

		if(large.successful != 0)
		{
			printf("%d pairs of large parentheses match successful!\n", large.successful);
		}
		if(large.failed != 0)
		{
			printf("%d pairs of large parentheses match failed!\n", large.failed);
		}
			
		if(!isEmptyStackArray(stack))
		{
			printf("%d separate parentheses match failed!\n", stack->top + 1);
		}
	}

	if((small.failed != 0) || (middle.failed != 0) || (large.failed != 0) || (!isEmptyStackArray(stack)))
	{
		printf("The final parentheses match result is failure!\n");
	}
	else
	{
		printf("The final parentheses match result is successful!\n");
	}
	
}





int main(void)
{
	char buffer[MAX_STRING_LENGTH];

	/* 若读取的字符数大于定义的最大值1024，那么再次调用fgets函数
	将继续从截断出读取！若要重新从头读取一个文本行，则需调用fflush
	函数，清除缓冲区，从而立即写入字符 */
	fgets(buffer, MAX_STRING_LENGTH, stdin);//最多读取MAX_STRING_LENGTH - 1个字符，stdin表示从键盘输入数据
	if(buffer[strlen(buffer) - 1] == '\n')//替换换行符
	{
		buffer[strlen(buffer) - 1] = '\0';
	}

	parenthesesMatch(buffer);
	
	return 0;
}

