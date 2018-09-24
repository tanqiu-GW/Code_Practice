/********************************************************************************

 *************************Copyright (C), 2018, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : drvRngQue.h
 * @brief   		  : drvQueue.c header file
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

#ifndef __DRVQUEUE_H__
#define __DRVQUEUE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */





typedef struct _tagRngQue
{
    U16 max;
    U16 size;
    U16 count;
    U16 put;
    U16 get;
    void *buf;
}tRngQue;





extern void RngQue_Init(tRngQue *pQue, void *pBuf, U16 lenElem, U16 szElem);
extern void RngQue_Flush(tRngQue *pQue);
extern U16  RngQue_NumElems(tRngQue *pQue);
extern U16  RngQue_NumFree(tRngQue *pQue);
extern void RngQue_Put(tRngQue *pQue, void *buf, U16 num);
extern U16  RngQue_Get(tRngQue *pQue, void *buf, U16 num);
extern void RngQue_EnterINT(void);
extern void RngQue_ExitINT(void);





#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __DRVQUEUE_H__ */
