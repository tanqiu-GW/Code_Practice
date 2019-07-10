/* 有关“树”数据结构的头文件 */

#ifndef __TREE_H__
#define __TREE_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/* 头文件 */
#include "../common_type.h"


//默认基本元素类型
typedef char ElementType;


/* 二叉查找树----------start */

//二叉查找树节点结构
typedef struct tagBinarySearchTree	
{
	void *element;
	int element_size;	//元素长度，字节
	struct tagBinarySearchTree *left;
	struct tagBinarySearchTree *right;
}BST_Node, *pBST_Node;



//创建查找树，入参为二叉树根节点元素和元素长度，返回根节点指针
extern BST_Node *BST_create(void *element, int element_size);
extern BST_Node *BST_find(BST_Node *tree, void *element);//查找二叉树中element值，返回元素指针
extern void *BST_find_min(BST_Node *tree);//二叉查找树返回最小值指针
extern void *BST_find_max(BST_Node *tree);
extern Status BST_insert(BST_Node *tree, void *element, int element_size);
extern Status BST_delete(BST_Node *tree, void *element);

/* 二叉查找树----------end */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TREE_H__ */


