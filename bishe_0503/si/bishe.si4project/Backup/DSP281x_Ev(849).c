// TI File $Revision: /main/2 $
// Checkin $Date: April 29, 2005   11:10:23 $
//###########################################################################
//
// FILE:	DSP281x_Ev.c
//
// TITLE:	DSP281x Event Manager Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP281x C/C++ Header Files V1.20 $
// $Release Date: July 27, 2009 $
//###########################################################################

#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File

//---------------------------------------------------------------------------
// InitEv: 
//---------------------------------------------------------------------------
// This function initializes to a known state.
//
void InitEv(void)
{
    EvaRegs.T1CON.bit.TMODE = 2;        //计数模式为连续增计数
    EvaRegs.T1CON.bit.TPS = 1;          //T1CLK=HSPCLK/2=37.5MHz
    EvaRegs.T1CON.bit.TENABLE = 0;      //暂时禁止T1计数
    EvaRegs.T1CON.bit.TCLKS10 = 0;      //使用内部时钟
    EvaRegs.GPTCONA.bit.T1TOADC = 2;    //周期中断启动ADC
    EvaRegs.EVAIMRA.bit.T1PINT = 1;     //使能定时器T1的周期中断
    EvaRegs.EVAIFRA.bit.T1PINT = 1;     //清除定时器T1的周期中断标志位
    EvaRegs.T1PR = 0x0EA5;              //周期为0.1ms
    EvaRegs.T1CNT = 0;                  //初始化计数器寄存器
}	
	
//===========================================================================
// No more.
//===========================================================================
