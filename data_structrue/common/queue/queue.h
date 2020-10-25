/*
 * @Author: gw
 * @Date: 2020-10-25 00:45:43
 * @LastEditors: gw
 * @LastEditTime: 2020-10-25 09:39:40
 * @Description: 循环队列接口
 * @FilePath: /Code_Practice/data_structrue/common/queue/queue.h
 */

#ifndef __QUEUE_H__
#define __QUEUE_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/* 头文件 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


/* 队列结构类型 */
typedef struct tag_loop_queue
{
    int count; //队列当前元素个数
    int lenQueue; //队列可存储元素长度
    int lenElement; //队列中每个元素的长度
    int rear; //队尾下标,指向数组里的第一个元素的位置,每次添加一个元素时rear向后移动一个单位
    int front; //队头下标,只想数组里的最后一个元素的下一个元素,每次删除一个元素时front向后移动一个单位
    void *elementBuf; //队列元素数组指针
}ts_LoopQueue;


/* 静态循环队列接口-----start */
extern int initLoopQueueStatic(ts_LoopQueue *queue, int lenQueue, int lenElement, void *queueDataBuf); //初始化静态循环队列
extern int isFullLoopQueueStatic(ts_LoopQueue *queue); //0-未满, 1-已满
extern int isEmptyLoopQueueStatic(ts_LoopQueue *queue); //0-非空, 1-为空
extern int enLoopQueueStatic(ts_LoopQueue *queue, void *element); //入队列. 0-入队成功,-1-入队失败
extern int deLoopQueueStatic(ts_LoopQueue *queue, void *element); //出队列. 0-出队成功,-1-出队失败
/* 静态循环队列接口-----end */



/* 动态循环队列接口-----start */
extern int initLoopQueueDynamic(ts_LoopQueue *queue, int lenQueue, int lenElement, void *queueDataBuf); //初始化静态循环队列
extern int isFullLoopQueueDynamic(ts_LoopQueue *queue); //0-未满, 1-已满
extern int isEmptyLoopQueueDynamic(ts_LoopQueue *queue); //0-非空, 1-为空
extern int enLoopQueueDynamic(ts_LoopQueue *queue, void *element); //入队列. 0-入队成功,-1-入队失败
extern int deLoopQueueDynamic(ts_LoopQueue *queue, void *element); //出队列. 0-出队成功,-1-出队失败
/* 动态循环队列接口-----end */



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __QUEUE_H__ */