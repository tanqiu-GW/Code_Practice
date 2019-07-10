/* 利用栈数据结构做括号匹配（平衡符号）*/
//简单起见，仅对()、[]、{}进行匹配


/* 头文件 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/stack/stack.h"


/* 定义最大长度可读入字符串1024字节 */
#define MAX_STRING_LENGTH	1024
#define MAX_STACK_LENGTH	1024



int main(void)
{
	Stack *stack_string;
	char *pchar;
	char buffer[MAX_STRING_LENGTH];
	/* 若读取的字符数大于定义的最大值-1，那么再次调用fgets函数
	将继续从截断处读取！若要重新重头读取一个文本行，则需调用
	fflush函数，清除缓冲区，从而在缓冲区满的情况下立即写入字符。 */
	fgets(buffer, MAX_STRING_LENGTH, stdin);//最多读取MAX_STRING_LENGTH - 1个字节，stdin表示从键盘输入数据

	if(buffer[strlen(buffer) - 1] == '\n')//替换换行符
	{
		buffer[strlen(buffer) - 1] = '\0';
	}

	stack_string = createStack(strlen(buffer));

	pchar = buffer;
	while(*pchar != '\0')
	{
		switch(*pchar)
		{
			case '(':
				pushStack(stack_string, pchar);	//开放符号时入栈
				break;
			case '[':
				pushStack(stack_string, pchar);
				break;
			case '{':
				pushStack(stack_string, pchar);
				break;
			case ')':
				if(isEmptyStack(stack_string))	//封闭符号时，若栈空，则报错
				{
					printf("小括号不匹配！\n");
				}
				else	//若栈非空，弹栈，并判断出栈元素是否为对应的开放符号

				{
					if((char)popAndReturnStack(stack_string) != '(')
					{
						printf("小括号不匹配！\n");
					}
					else
					{
						printf("小括号成功匹配！\n");
					}
				}
				break;
			case ']':
				if(isEmptyStack(stack_string))
				{
					printf("中括号不匹配！\n");
				}
				else
				{
					if(popAndReturnStack(stack_string) != '[')
					{
						printf("中括号不匹配！\n");
					}
					else
					{
						printf("中括号成功匹配！\n");
					}
				}
				break;
			case '}':
				if(isEmptyStack(stack_string))
				{
					printf("大括号不匹配！\n");
				}
				else
				{
					if(popAndReturnStack(stack_string) != '{')
					{
						printf("大括号不匹配！\n");
					}
					else
					{
						printf("大括号成功匹配！\n");
					}
				}
				break;
			default:
				break;
		}
				
		pchar++;
		if(*pchar == '\0')
		{
			if(!isEmptyStack(stack_string))
			{
				printf("括号不匹配！\n");
			}
		}
	}

	distroyStack(stack_string);
	
	return 0;
}
