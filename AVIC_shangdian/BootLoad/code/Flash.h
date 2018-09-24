#ifndef _InDrvFlashH
#define _InDrvFlashH

#include "appTypes.h"

#define ADDR_BOOT_RUN        0x0000					//boot程序起始地址
#define ADD_ISR_SOR          0x0003					//中断向量入口

#define ADDR_APP_LEN         0x4000					//app程序长度
#define ADDR_APP_CHK         0x4002					//app程序校验
#define ADDR_APP_FLAG        0x4003					//app程序加载标志：是否已经成功加载
#define ADDR_ISR_PIE         0x4004					//中断向量
#define ADDR_APP_RUN         0x4200					//app程序起始地址
#define ADDR_FLASH_MAX       0xFFFF					//flash最终地址

#define SIZE_FLASH_PAGE      512						//flash页大小

//擦除一个分区
#define Flash_Erase(addr)    {								 \
																FLSCL = 0x01;  \
																PSCTL |= 0x03; \
																*(addr) = 0x00;\
																PSCTL &= ~0x03;\
																FLSCL = 0x00;  \
														 }
//写入一个字节
#define Flash_Write(addr,dat)  *(addr) = (dat);

#define Flash_Write_Bng()    {                 \
																FLSCL = 0x01;  \
																PSCTL = 0x01;  \
														 }

#define Flash_Write_End()    {                 \
																PSCTL = 0x00;  \
																FLSCL = 0x00;  \
                             }
#endif