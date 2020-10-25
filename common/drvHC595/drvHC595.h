/********************************************************************************

 *************************Copyright (C), 2018, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : drvHC595.h
 * @brief   		  : drvHC595.c header file
 * @author       : gw
 * @version        : 1.0
 * @date          : 2018-12-18
 * 
 * 
 * @note History:
 * @note        : 
 * @note        : 
 *   Modification: Created file

********************************************************************************/

#ifndef __DRVHC595_H__
#define __DRVHC595_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */



/* 全局函数声明 */
extern void init_HC595(void);//初始化595芯片
extern void send_multbyte_HC595(unsigned char *data, unsigned int len);//多个595芯片级联时，发送多个字节数据


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __DRVHC595_H__ */
