/********************************************************************************

 *************************Copyright (C), 2018, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : main.c
 * @brief   		  : .C file function description
 * @author       : gw
 * @version        : 1.0
 * @date          : 2018-11-26
 * 
 * 
 * @note History:
 * @note        : gw 2018-11-26
 * @note        : 
 *   Modification: Created file

********************************************************************************/

#include <stdio.h>



/* 类型定义 */
typedef struct tagRecord
{
    int day;
    int *topic;
}Record;


/* 局部函数声明 */
static int SumThreeDay(Record test);


/**
 * @fn       int SumThreeDay(int * topic)
 * @brief    连续3天题目数求和，返回连续3天的最大值
 * 
 * @param[in]          int * topic  
 * @return         
 */
int SumThreeDay(Record test)
{
    int count = 0;
    static int sum = 0, sumtemp = 0, sumresult = 0;
    int *temp = test.topic;
    
    if(test.day < 3)
    {
        if(test.day = 0)
        {
            sumresult = 0;
        }
        else
        {
            while(test.day--)
            {
                sumresult += *test.topic++;
            }
        }
    }
    else
    {
        while(count++ < (test.day - 2))
        {     
            for(int i = 0; i < 3; i++)
            {
                sum += *test.topic++;
            }

            sumtemp = sum;
            
            if(sumresult <= sumtemp)
            {
                sumresult = sumtemp;
            }
            
            test.topic = temp + 1;
            sum = 0;
        }
    }

    return sumresult;
}



int main(void)
{
    //初始化天数和题目数量
    Record test;
    test.day = 5;
    int topic[5] = {10,6,9,12,5};
    test.topic = topic;

    int sum = SumThreeDay(test);    
    printf("最大连续3天刷题和为 %d .\n", sum);
    return 0;
}
