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
 * @param[in]        void * pBuf     - buffer to get data from
 * @param[in]        U16 num         - number of element to put
 * @return         
 */
void RngQue_Put(tRngQue * pQue, void * pBuf, U16 num)
{
}

