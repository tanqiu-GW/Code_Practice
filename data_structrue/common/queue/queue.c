/*
 * @Description: queue.c
 * @Author: gw
 * @Date: 2019-05-29 20:39:31
 * @LastEditors: gw
 * @LastEditTime: 2019-06-01 19:25:21
 */
/* 头文件 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"


/* 静态队列 ----------start */

/*  创建静态队列
    输入:len_queue,队列的最大总长度;
    len_elemen,每个队列元素的长度;
    *buf,存放队列元素的buf区指针;
    *queue,创建完成后的队列指针;
    输出:是否创建成功
*/
Status queue_static_create(U32 len_queue, U32 len_element, void *buf, sQueue *queue)
{
    U32 num_byte = 0;

    queue->len_queue = len_queue;
    queue->len_element = len_element;
    queue->count = 0;
    queue->put = queue->get = 0;    //初始化头指针和尾指针都为0,队列为空
    num_byte = len_element*len_queue;   //队列元素数据空间共有num_byte个字节
    
    if(buf == NULL)
    {
        printf("the specified buffer is error!");
        return FAILED;
    }
    if(num_byte > sizeof(buf))
    {
        printf("queue length exceeds buffer length!\n");
        return FAILED;
    }
    else
    {
        printf("create circular queue successful.\n");
    }

    memset(l_data_buf, 0, sizeof(char)*num_byte);
    queue->data_buf = buf;
    
    return SUCCESS;
}
/* 静态队列 ----------end */




/* 动态队列 ----------start */

/*  创建动态队列
    输入:len_queue,队列总长度;
    len_elemen,每个队列元素的长度;
    *queue,创建完成后的队列指针;
    输出:是否创建成功
*/
Status queue_dynamic_create(U32 len_queue, U32 len_element, sQueue *queue)
{
    return SUCCESS;
}
/* 动态队列 ----------end */

