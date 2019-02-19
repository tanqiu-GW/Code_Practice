/********************************************************************************

 *************************Copyright (C), 2019, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : stack_array.c
 * @brief   		  : .C file function description
 * @author       : gw
 * @version        : 1.0
 * @date          : 2019-02-16
 * 
 * 
 * @note History:
 * @note        : 栈的数组实现 2019-02-16
 * @note        : 
 *   Modification: Created file

********************************************************************************/

/* 头文件 */
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "..\..\common\type.h"
#include "stack.h"


/* 应用于当前源文件的变量 */
static Stack_array *stack_array;




/* 创建栈，栈大小由capacity决定 */
Stack_array *createStackArray(int capacity)
{
	stack_array = (Stack_array *)malloc(sizeof(Stack_array));
	if(stack_array == NULL)
	{
		printf("apply room error!\n");
	}

	stack_array->capacity = capacity;
	stack_array->top = EMPTYTOP;
	stack_array->data_array = (ElementType *)malloc(sizeof(ElementType) * capacity);
	memset(stack_array->data_array, 0, sizeof(ElementType) * capacity);

	return stack_array;
}

/* 释放栈内存 */
void distroyStackArray(Stack_array * stack_array)
{
	if(stack_array != NULL)
	{
		free(stack_array->data_array);
		free(stack_array);
	}
}

/* 判断栈是否为空 */
bool isEmptyStackArray(Stack_array * stack_array)
{
	return (stack_array->top <= EMPTYTOP);
}

/* 判断栈是否已满 */
bool isFUllStackArray(Stack_array * stack_array)
{
	return (stack_array->top > stack_array->capacity);
}

/* 元素入栈 */
status pushStackArray(Stack_array * stack_array, ElementType * data)
{

	if(!isFUllStackArray(stack_array))
	{
		stack_array->data_array[++stack_array->top] = *data;
		return success;
	}

	return failed;
}

/* 元素弹栈 */
status popStackArray(Stack_array * stack_array)
{
	if(!isEmptyStackArray(stack_array))
	{
		stack_array->top--;
		return success;
	}

	return failed;
}

/* 返回栈顶元素 */
ElementType returnTopStackArray(Stack_array * stack_array)
{
	if(!isEmptyStackArray(stack_array))
	{
		return stack_array->data_array[stack_array->top];
	}
	else
	{
		printf("stack is empty!\n");
		return 0;
	}
}

/* 出栈并返回栈顶元素 */
ElementType popAndreturnTOPstackArray(Stack_array * stack_array)
{
	if(!isEmptyStackArray(stack_array))
	{
		return stack_array->data_array[stack_array->top--];
	}
	else
	{
		printf("stack is empty!\n");
		return 0;
	}
}




