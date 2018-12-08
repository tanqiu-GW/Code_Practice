/********************************************************************************

 *************************Copyright (C), 2018, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : drvRngQue.c
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

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>


#include "drvType.h"
#include "drvRngQue.h"






#define QUE_TYPE_BASE       U16

#define rngQueEnter()       "DINT"
#define rngQueExit()        "EINT"





LOCAL volatile BOOL l_InINT = FALSE;





/**
 * @fn       void RngQue_Init(tRngQue * pQue, void * pBuf, U16 lenElem, U16 szElem)
 * @brief    Initialize ring-queue
 * 
 * @param[in]        tRngQue * pQue  - pointer to ring-queue to initialize
 * @param[in]        void * pBuf     - pointer to buffer to store data
 * @param[in]        U16 lenElem     - length of elements can be stored
 * @param[in]        U16 szElem      - size of each element
 * @return         
 */
void RngQue_Init(tRngQue * pQue, void * pBuf, U16 lenElem, U16 szElem)
{
    pQue->max   = lenElem * szElem;
    pQue->size  = szElem;
    pQue->count = 0;
    pQue->put   = 0;
    pQue->get   = 0;
    pQue->buf   = pBuf;

    memset(pQue->buf, 0, (size_t)pQue->max);
}


/**
 * @fn       void RngQue_Flush(tRngQue * pQue)
 * @brief    Flush the given ring-queue
 * 
 * @param[in]        tRngQue * pQue  - pointer to ring-queue to flush
 * @return         
 */
void RngQue_Flush(tRngQue * pQue)
{
    if(!l_InINT){rngQueEnter();}

    pQue->count = 0;
    pQue->put   = 0;
    pQue->get   = 0;

    if(!l_InINT){rngQueExit();}
}


/**
 * @fn       U16 RngQue_NumElems(tRngQue * pQue)
 * @brief    Get number of elements in the given ring-queue
 * 
 * @param[in]        tRngQue * pQue  - pointer to ring-queue to check
 * @return           U16             - number of elements in the queue
 */
U16 RngQue_NumElems(tRngQue * pQue)
{
    U16 countTmp;

    if(!l_InINT){rngQueEnter();}

    countTmp = pQue->count;

    if(!l_InINT){rngQueExit();}

    countTmp /= pQue->size;
    return countTmp;
}


/**
 * @fn       U16 RngQue_NumFree(tRngQue * pQue)
 * @brief    Get number free in the given ring-queue
 * 
 * @param[in]        tRngQue * pQue  - pointer to ring-queue to check
 * @return           U16             - number of elements in the queue
 */
U16 RngQue_NumFree(tRngQue * pQue)
{
    U16 countTmp;

    if(!l_InINT){rngQueEnter();}

    countTmp = pQue->max - pQue->count;

    if(!l_InINT){rngQueExit();}

    countTmp /= pQue->size;
    
    return countTmp;
}


/**
 * @fn       void RngQue_Put(tRngQue * pQue, void * pBuf, U16 num)
 * @brief    Put n element to the given ring-queue
 * 
 * @param[in]        tRngQue * pQue  - pointer to ring-queue to put element
 * @param[in]        void * buf      - buffer to get data from
 * @param[in]        U16 num         - number of element to put
 * @return         
 */
void RngQue_Put(tRngQue * pQue, void * buf, U16 num)
{
    U16 nTail = 0;      //number to put at tail
    U16 nHead = 0;      //number to put at head

    num = num * pQue->size;

    if(!l_InINT){rngQueEnter();}

    if(num < pQue->max)
    {
        //calculate number to put to tail and head
        nTail = pQue->max - pQue->put;
        if(num < nTail){nTail = num;}
        else
        {
            nHead = num - nTail;
            memcpy(pQue->buf, (QUE_TYPE_BASE *)buf + nTail, (size_t)nHead);
        }

        if(nTail > 0){memcpy((QUE_TYPE_BASE *)pQue->buf + pQue->put, buf, (size_t)nTail);}

        //check tatol after put,correct get pointer when greater than maximum
        if((pQue->count + num) <= pQue->max){pQue->count += num;}
        else
        {
            pQue->get += (pQue->count + num - pQue->max);
            if(pQue->get >= pQue->max){pQue->get -= pQue->max;}

            pQue->count = pQue->max;
        }

        //correct put pointer
        pQue->put += num;
        if(pQue->put >= pQue->max){pQue->put -= pQue->max;}
    }
    else
    {
        pQue->get = 0;
        pQue->put = 0;
        pQue->count = pQue->max;
        memcpy(pQue->buf, (QUE_TYPE_BASE *)buf + num - pQue->max, pQue->max);
    }

    if(!l_InINT){rngQueExit();}
}


/**
 * @fn       U16 RngQue_Get(tRngQue * pQue, void * buf, U16 num)
 * @brief    Get n element from the given ring-queue
 * 
 * @param[in]        tRngQue * pQue  - pointer to ring-queue to get element
 * @param[in]        void * buf      - pointer to buffer to recieve data
 * @param[in]        U16 num         - maximum number of element to get
 * @return           U16             - number get actual
 */
U16 RngQue_Get(tRngQue * pQue, void * buf, U16 num)
{
    U16 nActual = 0;
    U16 nTail   = 0;
    U16 nHead   = 0;
    
    num = num * pQue->size;
    
    if(!l_InINT){rngQueEnter();}

    if(pQue->count > 0)
    {
        //correct number can get
        if(num > pQue->count){nActual = pQue->count;}
        else{nActual = num;}

        //calculate nuber to put from tail and head
        nTail = pQue->max - pQue->get;
        if(nActual <= nTail){nTail = nActual;}
        else
        {
            nHead = nActual - nTail;
            memcpy((QUE_TYPE_BASE *)buf + nTail, pQue->buf, (size_t)nHead);
        }

        if(nTail > 0){memcpy(buf, (QUE_TYPE_BASE *)pQue->buf + pQue->get, (size_t)nTail);}

        //correct get pointer
        pQue->get += nActual;
        if(pQue->get >= pQue->max){pQue->get -= pQue->max;}

        //correct number remain
        pQue->count -= nActual;
    }

    if(!l_InINT){rngQueExit();}

    nActual = nActual / pQue->size;

    return nActual;
}


/**
 * @fn       void RngQue_EnterINT(void)
 * @brief    Indicate process in ISR
 * 
 * @param[in]          void  
 * @return         
 */
void RngQue_EnterINT(void)
{
    l_InINT = TRUE;
}


/**
 * @fn       void RngQue_ExitINT(void)
 * @brief    Indicate process out ISR
 * 
 * @param[in]          void  
 * @return         
 */
void RngQue_ExitINT(void)
{
    l_InINT = FALSE;
}


