/* 头文件 */
#include <stdio.h>
#include "../common/stack/stack.h"



int main(void)
{
	int test[10] = {9,8,7,6,5,4,3,2,1,0};
	int data_test;
	Stack_Node *stack_test = createStackList();

	returnTopStackList(stack_test, &data_test);
	pushStackList(stack_test, &test[0]);
	pushStackList(stack_test, &test[1]);
	pushStackList(stack_test, &test[2]);
	pushStackList(stack_test, &test[3]);
	pushStackList(stack_test, &test[4]);
	returnTopStackList(stack_test, &data_test);

	popStackList(stack_test);
	popStackList(stack_test);
	popStackList(stack_test);
	popStackList(stack_test);
	popStackList(stack_test);
	returnTopStackList(stack_test, &data_test);
	
	return 0;
}





