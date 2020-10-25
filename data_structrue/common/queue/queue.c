/*
 * @Author: gw
 * @Date: 2020-10-25 00:45:43
 * @LastEditors: gw
 * @LastEditTime: 2020-10-25 09:45:28
 * @Description: 循环队列接口实现
 * @FilePath: /Code_Practice/data_structrue/common/queue/queue.c
 */

/* 头文件 */
#include "queue.h"


/* 静态循环队列接口-----start */
/**
 * @description:静态循环队列初始化
 * @param:*queue,队列指针;
 *        lenQueue,队列最大长度;
 *        lenElement,队列中每个元素的长度
 *        *queueDataBuf,存放队列元素的buf区指针
 * @return:0-队列初始化成功, 1-队列初始化失败
 */
int initLoopQueue(ts_LoopQueue *queue, int lenQueue, int lenElement, void *queueDataBuf)
{
    int num_byte = 0;

    if((lenQueue == 0) || (lenElement == 0) || (queueDataBuf == NULL))
    {
        printf("queue init failed.\n");
        return -1;
    }

    queue->lenQueue = lenQueue;
    queue->lenElement = lenElement;
    queue->count = 0;
    queue->front = 0;
    queue->rear = 0;

    num_byte = lenElement*lenQueue;
    memset(queueDataBuf, 0, sizeof(char)*num_byte);
    queue->elementBuf = queueDataBuf;

    return 0;
}

/**
 * @description:判断静态循环队列是否已满
 * @param:*queue,队列指针;
 * @return:0-未满, 1-已满
 */
int isFullLoopQueue(ts_LoopQueue *queue)
{
    if((queue->rear+1) % queue->lenQueue == queue->front)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @description:判断静态循环队列是否为空
 * @param:*queue,队列指针;
 * @return:0-非空, 1-为空
 */
int isEmptyLoopQueue(ts_LoopQueue *queue)
{
    if(queue->front == queue->rear)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @description:静态循环队列,入队
 * @param:*queue,队列指针;
 *        *element,入队元素指针;
 * @return:0-入队成功,-1-入队失败
 */
int enLoopQueue(ts_LoopQueue *queue, void *element)
{
    if(isFullLoopQueue(queue))
    {
        printf("queue is full, can't enQueue.\n");
        return -1;
    }
    else
    {
        //queue->elementBuf[queue->rear] = *element;
        memcpy(((char *)queue->elementBuf)+(queue->lenElement*queue->rear), element, queue->lenElement);
        queue->rear = (queue->rear+1) % queue->lenQueue;
        queue->count++;

        return 0;
    }
}

/**
 * @description:静态循环队列,出队
 * @param:*queue,队列指针;
 *        *element,出队元素指针;
 * @return:0-出队成功,-1-出队失败
 */
int deLoopQueue(ts_LoopQueue *queue, void *element)
{
    if(isEmptyLoopQueue(queue))
    {
        printf("queue is empty, can't deQueue.\n");
        return -1;
    }
    else
    {
        //*element = queue->elementBuf[queue->front];
        memcpy(element, ((char *)queue->elementBuf)+(queue->lenElement*queue->front), queue->lenElement);
        queue->front = (queue->front+1) % queue->lenQueue;
        queue->count--;

        return 0;
    }
}

/* 静态循环队列接口-----end */





/* 动态循环队列接口-----start */

/* 动态循环队列接口-----end */