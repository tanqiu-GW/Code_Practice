/* 头文件 */
#include <stdio.h>
#include "stack.h"



int main(void)
{
	ElementType array_test[10] = {'0','1','2','3','4','5','6','7','8','9'};

	Stack_array *stack_test = createStackArray(10);

	pushStackArray(stack_test, &array_test[0]);
	pushStackArray(stack_test, &array_test[9]);
	pushStackArray(stack_test, &array_test[8]);
	pushStackArray(stack_test, &array_test[4]);
	pushStackArray(stack_test, &array_test[2]);
	ElementType data = returnTopStackArray(stack_test);
	popStackArray(stack_test);
	data = popAndreturnTOPstackArray(stack_test);

	distroyStackArray(stack_test);
	
	return 0;
}



