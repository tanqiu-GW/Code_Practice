#include "appTypes.h"
#include "drvC8051F02xCore.h"
#include "drvSCI.h"
#include "drvFlash.h"


/*********************************************************************************/
/***                    常量定义                                                   ***/
/*********************************************************************************/
#define FLAG_HAD_LOAD           0x51            //APP程序加载正常值

#define LEN_FRM_MAX             80              
#define LEN_FRM_MIN             9

#define HEAD_CMD_1              0xAA            //指令帧头1
#define HEAD_CMD_2              0x55            //指令帧头2
#define HEAD_ACK_1              0xAA            //应答帧头1
#define HEAD_ACK_2              0x55            //应答帧头2

//数据帧各个数据位置
typedef enum _eIdxFrm
{
    eIdxF_Head1 = 0,
    eIdxF_Head2 = 1,
    eIdxF_Len   = 2,
    eIdxF_Cmd   = 7,
    eIdxF_Pars0 = 8,
    eIdxF_Pars1 = 9,
    eIdxF_Pars2 = 10,
    eIdxF_Pars3 = 11
}eIdxFrm;

typedef enum _eCmdUpper
{
    eCmdU_Shake = 0xFA,         //握手
    eCmdU_AppInfo = 0xFB,       //app长度，校验，收到该帧正确时进行擦除
    eCmdU_Update = 0xFC,        //程序加载
    eCmdU_Success = 0xFd        //验证并回复
}eCmdU;

/*********************************************************************************/
/***                    结构体定义                                                  ***/
/*********************************************************************************/
typedef struct _sParsFrame
{
    U8 buf[LEN_FRM_MAX];
    U16 cnt;
}sParsFrm;

/*********************************************************************************/
/***                    全局变量定义                                                 ***/
/*********************************************************************************/

/*********************************************************************************/
/***                    局部变量定义                                                 ***/
/*********************************************************************************/
LOCAL U16 XDATA *l_pWriter;

LOCAL U16 l_LenApp = 0;
LOCAL U8 l_ChkSum = 0;

LOCAL sParsFrm l_Frm;

LOCAL BOOL flag_had_Load = FALSE;
LOCAL BOOL flag_to_Load = TRUE;

LOCAL XDATA U8 frameCnt = 0;            //应答帧计数字

/********************************************************************************/
/***                    局部函数声明                                                ***/
/********************************************************************************/
LOCAL void CommPC(void);
LOCAL void ClearAppDat(void);
LOCAL void UpAppDat(void);
LOCAL void CheckAppDat(void);
LOCAL void GotFrame(void);
LOCAL void msgAck(eCmdU cmd, BOOL rst);

/********************************************************************************/
/***                主程序                                                       ***/
/********************************************************************************/
void main(void)
{
    pFunVoid funApp;
    DINT();

    CoreInit();             //单片机内核初始化
    SciInit();              //串口初始化
    Timer_Init();           //定时器1初始化

    if((*((U16 CODE *)(ADDR_APP_FLAG)) & 0xFF) == FLAG_HAD_LOAD)//是否加载app程序
        {
            flag_had_Load = TRUE;
            flag_to_Load = FALSE;
            l_LenApp = *((U16 CODE *)(ADDR_APP_LEN));           //获取原程序长度
        }
    else
        {
            flag_had_Load = FALSE;
            flag_to_Load = TRUE;
        }

    while(TRUE)
        {
            if(flag_to_Load)//需要更新app程序
                {
                    CommPC();
                    flag_to_Load = FALSE;
                }
            else//不需要更新app程序
                {
                    if((*((U16 CODE *)(ADDR_APP_FLAG)) & 0xFF) == FLAG_HAD_LOAD)
                        {
                            funApp = (pFunVoid)(ADDR_APP_RUN);
                            (*funApp)();
                        }
                    else//未加载app程序，需加载
                        {
                            flag_to_Load = TRUE;
                        }
                }
        }
}
/********************************************************************************/
/***                握手后交互操作                                                   ***/
/********************************************************************************/
void CommPC(void)
{
    BOOL rslt;
    BOOL isOver = FALSE;
    U8 shackCnt = 0;

    pFunVoid funAPP;

    DINT();
    CoreInit();
    SciInit();
    Timer_Init();

    while(!isOver)
        {
            while(0 == SciReadBuf(&l_Frm.buf[l_Frm.cnt],1))
                {
                    rslt = GotFrame();
                    if(rslt)
                        {
                            switch(l_Frm.buf[eIdxF_Cmd])
                                {
                                    case eCmdU_Shake:
                                        msgAck(eCmdU_Shake,TRUE);
                                        shackCnt ++;
                                        break;
                                    case eCmdU_AppInfo:
                                        if(shackCnt >= 5)
                                            {
                                                l_ChkSum = 0;
                                                ClearAppDat();
                                            }
                                        else
                                            {
                                                msgAck(eCmdU_AppInfo, FALSE);
                                            }
                                        break;
                                    case eCmdU_Update:
                                        UpAppDat();
                                        break;
                                    case eCmdU_Success:
                                        