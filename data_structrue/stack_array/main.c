/* 头文件 */
#include <stdio.h>
#include "../common/stack/stack.h"


int main(void)
{
	int array_test[10] = {0,1,2,3,4,5,6,7,8,9};
	int *data_test;
	Stack *stack_test = createStack(10);

	pushStack(stack_test, &array_test[0]);
	pushStack(stack_test, &array_test[1]);
	pushStack(stack_test, &array_test[2]);
	pushStack(stack_test, &array_test[3]);
	pushStack(stack_test, &array_test[4]);
	pushStack(stack_test, &array_test[5]);

	data_test = (int *)returnTopStack(stack_test);

	popStack(stack_test);
	popStack(stack_test);
	popStack(stack_test);
	data_test = (int *)returnTopStack(stack_test);

	distroyStack(stack_test);

	return 0;
}

