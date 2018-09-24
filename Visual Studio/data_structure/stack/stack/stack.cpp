// stack.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "malloc.h"


#define SIZE_MAX	50

typedef struct _Stack
{
	int buf[SIZE_MAX];
	int top;
}Stack;


Stack *temp;


void initStack(Stack *a)
{
	temp = (Stack *)malloc(sizeof(Stack));
	memset(temp, 0, sizeof(Stack));
}

Stack *pushStack(Stack *a, int elem)
{
	a->buf[a->top++] = elem;
	return a;
}

int popStack(Stack *a)
{
	int temp;

	if (a->top > 0)
	{
		temp = a->buf[a->top];
		a->top--;
	}
	return temp;
}

int main()
{
	int vaule;

	initStack(temp);
	temp = pushStack(temp, 1);
	temp = pushStack(temp, 2);
	temp = pushStack(temp, 3);
	temp = pushStack(temp, 4);

	vaule = popStack(temp);
	vaule = popStack(temp);
	vaule = popStack(temp);

    return 0;
}

