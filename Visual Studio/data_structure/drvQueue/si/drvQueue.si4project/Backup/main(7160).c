/********************************************************************************

 *************************Copyright (C), 2018, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : main.c
 * @brief   		  : .C file function description
 * @author       : gw
 * @version        : 1.0
 * @date          : 2018-09-11
 * 
 * 
 * @note History:
 * @note        : gw 2018-09-11
 * @note        : 
 *   Modification: Created file

********************************************************************************/


#include"drvType.h"
#include"drvRngQue.h"

/**
 * @fn       void main(void)
 * @brief     调用队列函数的主函数
 * 
 * @param[in]          void  
 * @return         
 */
void main(void)
{
    LOCAL U16 testtemp[10] = {0,1,2,3,4,5,6,7,8,9};
    U16 testbuf[10],putbuf[10],getbuf[10],one_element;
    U16 szput,szget;
    tRngQue testqueue;

    memcpy(putbuf, testtemp, sizeof(testtemp));

    RngQue_Init(&testqueue, testbuf, sizeof(testtemp), sizeof(U16));
    szput = RngQue_NumFree(&testqueue);
    RngQue_Put(&testqueue, putbuf, szput);
    szget= RngQue_NumElems(&testqueue);
    RngQue_Get(&testqueue, getbuf, szget);
}



