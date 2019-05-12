/* 头文件 */
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "stack.h"



/* 栈——数组实现 	---------------------Start */

/* 局部变量 */
static Stack *stack;


/* 创建栈，栈大小由capacity决定 */
Stack *createStack(int capacity)
{
	stack = (Stack *)malloc(sizeof(Stack));
	if(stack == NULL)
	{
		printf("apply room error\n");
	}

	stack->capacity = capacity;
	stack->top = -1;	//空栈，top为-1
	//简单起见，栈元素类型为int
	stack->data_array = (int *)malloc(sizeof(int) * capacity);
	memset(stack->data_array, 0, sizeof(int) * capacity);

	return stack;
}

/* 释放栈内存 */
void distroyStack(Stack * stack)
{
	if(stack != NULL)
	{
		free(stack->data_array);
		free(stack);
	}
}

/* 判断栈是否为空 */
int isEmptyStack(Stack * stack)
{
	return (stack->top <= EMPTYTOP);
}

/* 判断栈是否以满 */
int isFullStack(Stack * stack)
{
	return (stack->top >= stack->capacity);
}

/* 元素入栈 */
int pushStack(Stack * stack, void * data)
{
	int rsl = -1;	//默认入栈失败
	
	if(!isFullStack(stack))
	{
		//stack->data_array[++stack->top] = *((int *)data);
		((char *)(stack->data_array))[++stack->top] = *((char *)data);
		rsl = 1;
	}
	
	return rsl;
}

/* 元素弹栈 */
int popStack(Stack * stack)
{
	int rsl = -1;

	if(!isEmptyStack(stack))
	{
		stack->top--;
		rsl = 1;
	}

	return rsl;
}

/* 返回栈顶元素 */
void *returnTopStack(Stack * stack)
{
	void *data = NULL;	//默认空指针
	
	if(!isEmptyStack(stack))
	{
		data = &(stack->data_array[stack->top]);
	}

	return data;
}

/* 返回栈顶元素值并出栈 */
elementType popAndReturnStack(Stack * stack)
{
	if(!isEmptyStack(stack))
	{
		return (char)(((char *)(stack->data_array))[stack->top--]);
	}
	else
	{
		printf("stack is empty!\n");
		return 0;
	}
}

/* 栈——数组实现 	---------------------End */





/* 栈——链表实现 	---------------------Start */

/* 静态变量 */
static Stack_Node *stack_list;


/* 创建由链表实现的栈 */
Stack_Node *createStackList(void)
{
	stack_list = (Stack_Node *)malloc(sizeof(Stack_Node));
	if(stack_list == NULL)	
	{
		printf("apply room error\n");
	}

	stack_list->next = NULL;
	stack_list->data = 0;

	return stack_list;
}

/* 压栈 */
int pushStackList(Stack_Node * stack_list, int *data)
{
	int rsl = -1;	//默认入栈失败

	Stack_Node *pNode = (Stack_Node *)malloc(sizeof(Stack_Node));
	if(pNode == NULL)
	{
		printf("apply room error\n");
	}
	else
	{
		pNode->data = *data;
		pNode->next = stack_list->next;
		stack_list->next = pNode;
		rsl = 1;
	}

	return rsl;
}

/* 弹栈 */
int popStackList(Stack_Node * stack_list)
{
	int rsl = -1;	//默认入栈失败
	Stack_Node *firstNode;

	if(!isEmptyStackList(stack_list))
	{
		firstNode = stack_list->next;
		stack_list->next = stack_list->next->next;
		free(firstNode);
		rsl = 1;
	}

	return rsl;
}

/* 返回栈顶元素 */
void returnTopStackList(Stack_Node * stack_list, int *data)
{
	if(!isEmptyStackList(stack_list))
	{
		*data =  stack_list->next->data;
	}
	else
	{
		data = NULL;
		printf("stack is empty!\n");
	}

}

int isEmptyStackList(Stack_Node * stack_list)
{
	return (stack_list->next == NULL);
}

/* 栈——链表实现 	---------------------End */


