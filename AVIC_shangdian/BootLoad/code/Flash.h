#ifndef _InDrvFlashH
#define _InDrvFlashH

#include "appTypes.h"

#define ADDR_BOOT_RUN        0x0000					//boot������ʼ��ַ
#define ADD_ISR_SOR          0x0003					//�ж��������

#define ADDR_APP_LEN         0x4000					//app���򳤶�
#define ADDR_APP_CHK         0x4002					//app����У��
#define ADDR_APP_FLAG        0x4003					//app������ر�־���Ƿ��Ѿ��ɹ�����
#define ADDR_ISR_PIE         0x4004					//�ж�����
#define ADDR_APP_RUN         0x4200					//app������ʼ��ַ
#define ADDR_FLASH_MAX       0xFFFF					//flash���յ�ַ

#define SIZE_FLASH_PAGE      512						//flashҳ��С

//����һ������
#define Flash_Erase(addr)    {								 \
																FLSCL = 0x01;  \
																PSCTL |= 0x03; \
																*(addr) = 0x00;\
																PSCTL &= ~0x03;\
																FLSCL = 0x00;  \
														 }
//д��һ���ֽ�
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