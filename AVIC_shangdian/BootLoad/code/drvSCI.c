#include "appTypes.h"
#include "drvSCI.h"

#define NUM_TRY_MAX     10


//SCI初始化
void SciInit(void)//UART0工作方式3
{
    SCON0 = 0x00;
}
//波特率设置，定时器1，自动重载8位
void Timer_Init(void)
{
    SCKON = 0x10;
    TCON  = 0x40;
    TMOD  = 0x20;
    TH1   = 0xF3;
}
//通过SCI发送数据
void SciWriteBuf(U8 *pBuf,U16 len)
{
    while(len != 0)
        {
            SUBUF0 = *pBuf++;
            while(!TI0);
            TI0 = 0;
            len--;
        }
}
//通过SCI接收数据
U8 SciReadBuf(U8 *pBuf,U8 len)
{
    U16 cntDly;
    U8 cntTry = 0;

    while(len !=0)
        {
            cntDly = 0;
            while((RI0 == 0) && (cntDly < 2500)){cntDly++;}
            if(RI0 ==1)
                {
                    *pBuf++ = SBUF0;
                    RI0 = 0;
                    len--;
                    cntTry = 0;
                }
            else
                {
                    cntTry++;
                    if(cntTry >= NUM_TRY_MAX){break;}
                }
        }
    return len;
}

