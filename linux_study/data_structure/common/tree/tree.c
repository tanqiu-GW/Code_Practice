/* 头文件 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "tree.h"


/* 二叉查找树----------start */

/* 局部变量(仅作用于本文件) */



BST_Node *BST_create(void *element, int element_size)
{
	BST_Node *search_tree = (BST_Node *)malloc(sizeof(BST_Node));
	if(search_tree == NULL)
	{
		printf("apply room error!");
		return NULL;
	}

	search_tree->left = NULL;
	search_tree->right = NULL;
	search_tree->element = element;
	search_tree->element_size = element_size;

	return search_tree;
}

BST_Node *BST_find(BST_Node * tree, void * element)
{
	if(tree == NULL)
	{
		//printf("binary tree node is not exist!\n");
		return NULL;
	}

	if(*(ElementType *)element < *((ElementType *)(tree->element)))
	{
		if(tree->left == NULL)
		{
			return tree;	//返回插入节点的父节点指针
		}
		else
		{
			return BST_find(tree->left, element);
		}
	}
	else if(*(ElementType *)element > *((ElementType *)(tree->element)))
	{
		/*tree->right = BST_find(tree->right, element);
		if(tree->right == NULL)
		{
			return tree;	//返回插入节点的父节点指针
		}
		return NULL;*/
		if(tree->right == NULL)
		{
			return tree;	//返回插入节点的父节点指针
		}
		else
		{
			return BST_find(tree->right, element);
		}
	}
	else//if(*(ElementType *)element == *((ElementType *)(tree->element)))
	{
		return tree;	//返回删除节点位置的指针
	}
}

void *BST_find_min(BST_Node * tree)
{
	pBST_Node temp = tree;
	
	if(tree == NULL)
	{
		return NULL;
	}

	while(temp->left != NULL)
	{
		temp = temp->left;
	}

	return temp;
}

void *BST_find_max(BST_Node * tree)
{
	pBST_Node temp = tree;
	
	if(tree == NULL)
	{
		return NULL;
	}

	while(temp->right != NULL)
	{
		temp = temp->right;
	}

	return temp;
}

status BST_insert(BST_Node * tree, void * element, int element_size)
{
	status st = failed;
	BST_Node *pNode = BST_find(tree, element);
	if(*((ElementType *)(pNode->element)) == *(ElementType *)element)
	{
		printf("find same element in tree,no insert!");
		st = success;
	}
	else if(*((ElementType *)(pNode->element)) > *(ElementType *)element)
	{
		if(pNode->left == NULL)
		{
			pNode->left = (BST_Node *)malloc(sizeof(BST_Node));
			if(pNode->left == NULL)
			{
				printf("apply room error!\n");
				st = failed;
			}
			pNode->left->element = element;
			pNode->left->element_size = element_size;
			pNode->left->left = NULL;
			pNode->left->right = NULL;

			st = success;
		}
		else
		{
			printf("insert position is error!\n");
			st = failed;
		}
		
	}
	else
	{
		if(pNode->right == NULL)
		{
			pNode->right = (BST_Node *)malloc(sizeof(BST_Node));
			if(pNode->right == NULL)
			{
				printf("apply room error!\n");
			}
			pNode->right->element = element;
			pNode->right->element_size = element_size;
			pNode->right->left = NULL;
			pNode->right->right = NULL;

			st = success;
		}
		else
		{
			printf("insert position error!\n");
			st = failed;
		}
	}

	return st;
}

status BST_delete(BST_Node * tree, void *element)
{
	status st = failed;
	BST_Node *temp;
	BST_Node *pNode = BST_find(tree, element);

	if(*((ElementType *)(pNode->element)) == *(ElementType *)element)
	{
		if((pNode->left != NULL) && (pNode->right != NULL))	//有两个子树
		{
			/* 替换右子树最小的元素值 */
			temp = (BST_Node *)BST_find_min(pNode->right);
			pNode->element = temp->element;
			BST_delete(pNode->right, pNode->element);//递归的替换
		}
		else
		{
			temp = pNode;
			if(pNode->left == NULL)
			{
				pNode = pNode->right;
			}
			else if(pNode->right == NULL)
			{
				pNode = pNode->left;
			}
			else
			{
				;
			}

			free(temp);
			st = success;
		}
	}
	else
	{
		st = failed;
	}

	return st;
}


/* 二叉查找树----------end */


