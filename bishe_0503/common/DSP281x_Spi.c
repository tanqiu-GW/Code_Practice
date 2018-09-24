// TI File $Revision: /main/2 $
// Checkin $Date: April 29, 2005   11:08:24 $
//###########################################################################
//
// FILE:   DSP281x_Spi.c
//
// TITLE:  DSP281x SPI Initialization & Support Functions.
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
void InitSpi(void)
{
   // Initialize SPI-A:
    SpiaRegs.SPICCR.bit.SPISWRESET = 0;         //重新设置SPI
    SpiaRegs.SPICCR.all = 0x001F;               //16位数据模式，回送模式
    SpiaRegs.SPICTL.all = 0x0017;               //中断使能，溢出中断使能，主机，发送使能
    SpiaRegs.SPISTS.all = 0x0000;
    SpiaRegs.SPIBRR = 0x0063;                   //波特率设置
    SpiaRegs.SPIFFTX.all = 0xC028;              //使能FIFO，发送等级为8
    SpiaRegs.SPIFFRX.all = 0x0028;              //接收等级为8
    SpiaRegs.SPIFFCT.all = 0x00;
    SpiaRegs.SPIPRI.all = 0x0010;
    SpiaRegs.SPICCR.bit.SPISWRESET = 1;         //使能SPI
    SpiaRegs.SPIFFTX.bit.TXFIFO = 1;
    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 1;
   //tbd...
 
}

//===========================================================================
// No more.
//===========================================================================
