/* 头文件 */
#include <stdio.h>
#include <stdlib.h>
#include "../common/tree/tree.h"





int main(void)
{
	int idx1, idx2;
	BST_Node *test_tree;
	int test_element[] = {5,8,7,6,9,4,3,2,1,0};
	int test_delete_data;

	test_tree = BST_create(&test_element[0], sizeof(test_element[0]));

	for(idx1 = 1; idx1 < 10; idx1++)
	{
		BST_insert(test_tree, &test_element[idx1], sizeof(test_element[0]));
	}
	for(idx2 = 0; idx2 < 10; idx2++)
	{
		test_delete_data = test_element[idx2];
		BST_delete(test_tree, &test_delete_data);
	}
	
	return 0;
}




