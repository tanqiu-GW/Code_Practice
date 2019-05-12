
#ifndef __STACK_H__
#define __STACK_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/* 栈——数组实现 	---------------------Start */
/******************************************************************************
 *    头     文     件
 ******************************************************************************/

/******************************************************************************
 *   常   量   定   义
 ******************************************************************************/
#define EMPTYTOP	-1

/******************************************************************************
 *   类   型   定   义
 ******************************************************************************/
typedef int elementType;

 //数组实现栈
typedef struct tagStack
{
	int *data_array;	//指向栈元素
	int capacity;		//栈容量大小
	int top;			//top指针
}Stack;

/******************************************************************************
 *   全 局 变 量 声 明
 ******************************************************************************/

/******************************************************************************
 *   全 局 函 数 声 明
 ******************************************************************************/
extern Stack *createStack(int capacity);	//创建一个已知大小的栈
extern void distroyStack(Stack *stack);	//释放栈内存
extern int isEmptyStack(Stack *stack);	//是否为空栈
extern int isFullStack(Stack *stack);	//栈是否满
extern int pushStack(Stack *stack, void *data);	//入栈
extern int popStack(Stack *stack);			//弹栈
extern void *returnTopStack(Stack *stack);	//返回栈顶元素
extern elementType popAndReturnStack(Stack *stack);//元素出栈并返回出栈值

/* 栈——数组实现 	---------------------End */





/* 栈——链表实现 	---------------------Start */

/* 类型声明 */
typedef struct tagStack_Node
{
	struct tagStack_Node *next;		//单链表实现栈
	int data;
}Stack_Node;


/* 全局函数 */
extern Stack_Node *createStackList(void);
extern int pushStackList(Stack_Node *stack_list, int *data);
extern int popStackList(Stack_Node *stack_list);
extern void returnTopStackList(Stack_Node *stack_list, int *data);
extern int isEmptyStackList(Stack_Node *stack_list);
extern int isFullStackList(Stack_Node *stack_list);


/* 栈——链表实现	 ---------------------End */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STACK_H__ */


