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
    //EVA模块T1定时器设置
    EvaRegs.T1CON.bit.TMODE = 2;        //计数模式为连续增计数
    EvaRegs.T1CON.bit.TPS = 0;          //T1CLK=75MHz
    EvaRegs.T1CON.bit.TENABLE = 0;      //暂时禁止T1计数
    EvaRegs.T1CON.bit.TCLKS10 = 0;      //使用内部时钟
    EvaRegs.T1CON.bit.TECMPR = 1;       //使能定时器比较操作
    EvaRegs.GPTCONA.bit.T1TOADC = 2;    //周期中断启动ADC
    EvaRegs.T1PR = 0x0EA5;              //周期为50us
    EvaRegs.T1CNT = 0;                  //初始化计数器寄存器
    EvaRegs.COMCONA.bit.CENABLE = 1;    //使能比较单元的比较操作
    EvaRegs.COMCONA.bit.FCOMPOE = 1;    //全比较输出，PWM1~PWM4引脚均由相应的比较
    EvaRegs.COMCONA.bit.CLD = 0;        //当T1CNT = 0时装载

    //死区时间为4.27us
    EvaRegs.DBTCONA.bit.DBT = 10;       //死区定时器周期，m=10
    EvaRegs.DBTCONA.bit.EDBT1 = 1;      //死区定时器1使能位
    EvaRegs.DBTCONA.bit.DBTPS = 5;      //死区定时器预定标因子T=75M/32=2.34MHz
    EvaRegs.ACTRA.all = 0x0666;         //设定引脚PWM1~PWM4的动作属性
    EvaRegs.CMPR1 = 0x0C35;             //初始化占空比为25%
    EvaRegs.CMPR2 = 0x14AA;             //初始化占空比为42.3%

    EvaRegs.EVAIMRA.bit.T1PINT = 1;     //使能定时器T1的周期中断
    EvaRegs.EVAIFRA.bit.T1PINT = 1;     //清除定时器T1的周期中断标志位


    //EVA模块T2定时器设置
    EvaRegs.T2CON.bit.TMODE = 1;        //计数模式为连续增/减计数
    EvaRegs.T2CON.bit.TPS = 1;          //37.5MHz
    EvaRegs.T2CON.bit.TENABLE = 0;      //暂时禁止T2计数
    EvaRegs.T2CON.bit.TCLKS10 = 0;
    EvaRegs.GPTCONA.bit.T2TOADC = 1;    //周期中断启动ADC
    EvaRegs.T2PR = 0x493E;              //周期为1ms
    EvaRegs.T2CNT = 0;
    EvaRegs.EVAIMRB.bit.T2PINT = 1;
    EvaRegs.EVAIFRB.bit.T2PINT = 1;

    //EVB模块T3定时器设置
    EvbRegs.T3CON.bit.TMODE = 2;        //计数模式为连续增计数
    EvbRegs.T3CON.bit.TPS = 4;          //75/16MHz
    EvbRegs.T3CON.bit.TENABLE = 0;
    EvbRegs.T3CON.bit.TCLKS10 = 0;
    EvbRegs.GPTCONB.bit.T3TOADC = 1;    //周期中断启动ADC转换
    EvbRegs.T3PR = 0xB71A;              //定时器周期为10ms
    EvbRegs.T3CNT = 0;
    EvbRegs.EVBIMRA.bit.T3PINT = 1;
    EvbRegs.EVBIFRA.bit.T3PINT = 1;

    //EVB模块T4定时器设置
    EvbRegs.T4CON.bit.TMODE = 2;
    EvbRegs.T4CON.bit.TPS = 1;
    EvbRegs.T4CON.bit.TENABLE = 0;
    EvbRegs.T4CON.bit.TCLKS10 = 0;
    EvbRegs.GPTCONB.bit.T4TOADC = 1;
    EvbRegs.T4PR = 0x0EA5;
    EvbRegs.T4CNT = 0;
    EvbRegs.EVBIMRB.bit.T4PINT = 1;
    EvbRegs.EVBIFRB.bit.T4PINT = 1;


    //EVB模块CAP4捕获单元设置
    EvbRegs.CAPFIFOB.bit.CAP4FIFO = 0;  //状态为空
    EvbRegs.CAPCONB.bit.CAP45TSEL = 1;  //选择定时器3
    EvbRegs.CAPCONB.bit.CAP4EDGE = 2;   //捕获单元4下降沿检测
    EvbRegs.CAPCONB.bit.CAPRES = 1;     //捕获单元不复位
    EvbRegs.CAPCONB.bit.CAP45EN = 1;    //使能捕获单元4,5
    EvbRegs.EVBIFRC.bit.CAP4INT = 1;    //复位捕获单元4中断标志位
    EvbRegs.EVBIMRC.bit.CAP4INT = 1;    //捕获单元4中断使能
}	
	
//===========================================================================
// No more.
//===========================================================================
