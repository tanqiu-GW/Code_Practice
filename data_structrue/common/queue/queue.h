/*
 * @Description: queue.h
 * @Author: gw
 * @Date: 2019-05-29 20:39:38
 * @LastEditors: gw
 * @LastEditTime: 2019-07-10 22:13:43
 */
#ifndef __QUEUE_H__
#define __QUEUE_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


/* 头文件 */
#include "../common_type.h"

/* 类型定义 */
typedef char ElemType;  //默认基本元素类型

/* 队列结构(头进尾出) */
typedef struct tagQueue
{
    U32 len_queue;  //长度队列可存储多少个元素
    U32 len_element;//每个元素长度
    U32 count;      //队列内当前元素个数
    U32 get;        //尾指针
    U32 put;        //头指针
    void *data_buf; //数据存储指针
}sQueue;

/* 静态队列 ----------start */
extern Status queue_static_create(U32 len_queue, U32 len_element, void *buf, sQueue *queue); //静态内存存储队列元素
extern Status queue_static_put();
extern Status queue_static_get();
/* 静态队列 ----------end */



/* 静态队列 ----------start */
extern Status queue_dynamic_create(U32 len_queue, U32 len_element, sQueue *queue);//动态内存存储队列元素
extern Status queue_dynamic_put();
extern Status queue_dynamic_get();
/* 静态队列 ----------end */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __QUEUE_H__ */
