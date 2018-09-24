// TI File $Revision: /main/2 $
// Checkin $Date: April 29, 2005   11:08:40 $
//###########################################################################
//
// FILE:	DSP281x_Sci.c
//
// TITLE:	DSP281x SCI Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP281x C/C++ Header Files V1.20 $
// $Release Date: July 27, 2009 $
//###########################################################################

#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File

//---------------------------------------------------------------------------
// InitSPI: 
//---------------------------------------------------------------------------
// This function initializes the SPI(s) to a known state.
//
void InitSci(void)
{
	// Initialize SCI-A:
    SciaRegs.SCICCR.bit.STOPBITS = 0;           //1位停止位
    SciaRegs.SCICCR.bit.PARITYENA = 0;          //禁止即兴功能
    SciaRegs.SCICCR.bit.LOOPBKENA = 0;          //禁止会送测试模式功能
    SciaRegs.SCICCR.bit.ADDRIDLE_MODE = 0;      //空闲线模式
    SciaRegs.SCICCR.bit.SCICHAR = 7;            //8位数据位
    SciaRegs.SCICTL1.bit.TXENA = 1;             //SCI模块的发送使能
    SciaRegs.SCICTL1.bit.RXENA = 1;             //SCI模块的接收使能
    SciaRegs.SCIHBAUD = 0;
    SciaRegs.SCILBAUD = 0xF3;                   //波特率为19200
    SciaRegs.SCIFFTX.bit.TXFIFOXRESET = 1;      //重新使能发送FIFO的操作
    SciaRegs.SCIFFTX.bit.SCIFFENA = 1;          //使能SCI FIFO的功能
    SciaRegs.SCIFFTX.bit.TXFFST = 0;            //发送FIFO队列为空
    SciaRegs.SCIFFTX.bit.TXFFINT = 0;           //没有产生发送FIFO中断
    SciaRegs.SCIFFTX.bit.TXINTCLR = 0;          //没有清除TXFFINT的标志位
    SciaRegs.SCIFFTX.bit.TXFFIENA = 1;          //使能发送FIFO中断
    SciaRegs.SCIFFTX.bit.TXFFILIL = 0;          //发送中断级别为0
    SciaRegs.SCIFFRX.bit.RXFFOVF = 0;           //接收FIFO没有溢出
    SciaRegs.SCIFFRX.bit.RXFFOVRCLR = 1;        //对FXFFOVF标志位没有影响
    SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;       //重新使能接收FIFO的操作
    SciaRegs.SCIFFRX.bit.RXFIFST = 0;           //接收FIFO队列为空
    SciaRegs.SCIFFRX.bit.RXFFINT = 0;           //没有产生接收中断
    SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;        //清除接收中断标志位
    SciaRegs.SCIFFRX.bit.RXFFIENA = 1;          //使能FIFO接收中断
    SciaRegs.SCIFFRX.bit.RXFFIL = 8;            //FIFO接收中断级别为8
    SciaRegs.SCICTL1.bit.SWRESET = 1;           //重启SCI
	//tbd...
 	

	// Initialize SCI-B:
    ScibRegs.SCICCR.bit.STOPBITS = 0;           //1位停止位
    ScibRegs.SCICCR.bit.PARITYENA = 0;          //禁止即兴功能
    ScibRegs.SCICCR.bit.LOOPBKENA = 0;          //禁止会送测试模式功能
    ScibRegs.SCICCR.bit.ADDRIDLE_MODE = 0;      //空闲线模式
    ScibRegs.SCICCR.bit.SCICHAR = 7;            //8位数据位
    ScibRegs.SCICTL1.bit.TXENA = 1;             //SCI模块的发送使能
    ScibRegs.SCICTL1.bit.RXENA = 1;             //SCI模块的接收使能
    ScibRegs.SCIHBAUD = 0;
    ScibRegs.SCILBAUD = 0xF3;                   //波特率为19200
    ScibRegs.SCIFFTX.bit.TXFIFOXRESET = 1;      //重新使能发送FIFO的操作
    ScibRegs.SCIFFTX.bit.SCIFFENA = 1;          //使能SCI FIFO的功能
    ScibRegs.SCIFFTX.bit.TXFFST = 0;            //发送FIFO队列为空
    ScibRegs.SCIFFTX.bit.TXFFINT = 0;           //没有产生发送FIFO中断
    ScibRegs.SCIFFTX.bit.TXINTCLR = 0;          //没有清除TXFFINT的标志位
    ScibRegs.SCIFFTX.bit.TXFFIENA = 1;          //使能发送FIFO中断
    ScibRegs.SCIFFTX.bit.TXFFILIL = 0;          //发送中断级别为0
    ScibRegs.SCIFFRX.bit.RXFFOVF = 0;           //接收FIFO没有溢出
    ScibRegs.SCIFFRX.bit.RXFFOVRCLR = 1;        //对FXFFOVF标志位没有影响
    ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;       //重新使能接收FIFO的操作
    ScibRegs.SCIFFRX.bit.RXFIFST = 0;           //接收FIFO队列为空
    ScibRegs.SCIFFRX.bit.RXFFINT = 0;           //没有产生接收中断
    ScibRegs.SCIFFRX.bit.RXFFINTCLR = 1;        //清除接收中断标志位
    ScibRegs.SCIFFRX.bit.RXFFIENA = 1;          //使能FIFO接收中断
    ScibRegs.SCIFFRX.bit.RXFFIL = 8;            //FIFO接收中断级别为8
    ScibRegs.SCICTL1.bit.SWRESET = 1;           //重启SCI
	//tbd...
}	
	
//===========================================================================
// No more.
//===========================================================================
