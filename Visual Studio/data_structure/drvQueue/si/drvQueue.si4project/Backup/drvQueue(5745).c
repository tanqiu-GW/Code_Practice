/********************************************************************************

 *************************Copyright (C), 2018, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : drvQueue.c
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


#include "type.h"



#define queue_size      256

typedef struct _queue
{
    U16 pBuf[queue_size];
    U16 cnt;
    
}Queue;

