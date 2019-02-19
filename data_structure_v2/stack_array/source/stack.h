/********************************************************************************

 *************************Copyright (C), 2019, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : stack_array.h
 * @brief   		  : stack_array.c header file
 * @author       : gw
 * @version        : 1.0
 * @date          : 2019-02-16
 * 
 * 
 * @note History:
 * @note        : 栈数据结构头文件 2019-02-16
 * @note        : 
 *   Modification: Created file

********************************************************************************/

#ifndef __STACK_ARRAY_H__
#define __STACK_ARRAY_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/* 头文件 */
#include "..\..\common\type.h"


/* 常量定义 */
#define EMPTYTOP	-1
//用于括号匹配函数字符类型
#define ElementType	char

/* 类型声明 */
#ifndef ElementType
typedef int ElementType;
#endif



/* 栈结构数组实现 -----start */
typedef struct tagStack_array
{
	ElementType *data_array;//指向栈元素数组
	int capacity;		//栈空间大小
	int top;			//top指针
}Stack_array;

/* 全局函数声明 */
extern Stack_array *createStackArray(int capacity);	//创建一个capacity大小的栈
extern void distroyStackArray(Stack_array *stack_array);//释放栈内存
extern bool isEmptyStackArray(Stack_array *stack_array);//是否为空栈
extern bool isFUllStackArray(Stack_array *stack_array);	//栈是否已满
extern status pushStackArray(Stack_array *stack_array, ElementType *data);	//入栈
extern status popStackArray(Stack_array *stack_array);	//弹栈
extern ElementType returnTopStackArray(Stack_array *stack_array);//返回栈顶元素
extern ElementType popAndreturnTOPstackArray(Stack_array *stack_array);//出栈并返回栈顶元素

/* 栈结构数组实现 -----end */



/* 栈结构单向链表实现 -----start */
typedef struct tagStack_list
{
	struct tagStack_list *next;
	ElementType data;
}Stack_list;

extern Stack_list *createStackList(void);
extern isEmptyStackList(Stack_list *stack_list);
extern isFullStackList(Stack_list *stack_list);
extern status pushStackList(Stack_list *stack_list, ElementType *data);
extern status popStackList(Stack_list *stack_list);
extern ElementType returnTopStackList(Stack_list *stack_list);

/* 栈结构单向链表实现 -----end */



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __STACK_ARRAY_H__ */
