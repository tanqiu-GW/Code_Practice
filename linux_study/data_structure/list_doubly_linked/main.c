/******************************************************************************
 *    文     件     头
 ******************************************************************************/

#include "../common/list/list.h"


int main(void)
{
	int arr1[] = {11,22,33,44,55,66,77,88,99};
	int i = 0;

	char arr2[] = "gw is the best!";
	int j = 0;
	
#if 1
	List *list1 = createList();
	for(; i < sizeof(arr1) / sizeof(int); i++)
		insertTailList(&arr1[i]);
	printfList(INT);
	
	deleteList(5);
	printfList(INT);

	cut_exchangeList(4);
	printfList(INT);
#else

	List *list2 = createList();
	for(; j < sizeof(arr2) / sizeof(char); j++)
		insertTailList(&arr2[j]);
	printfList(CHAR);
#endif

	destroyList();

	return 0;
}

/******************************************************************************
 *    文     件     尾
 ******************************************************************************/


