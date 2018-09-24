// TI File $Revision: /main/2 $
// Checkin $Date: April 29, 2005   11:10:14 $
//###########################################################################
//
// FILE:	DSP281x_Gpio.c
//
// TITLE:	DSP281x General Purpose I/O Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP281x C/C++ Header Files V1.20 $
// $Release Date: July 27, 2009 $
//###########################################################################

#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File

//---------------------------------------------------------------------------
// InitGpio: 
//---------------------------------------------------------------------------
// This function initializes the Gpio to a known state.
//
void InitGpio(void)
{

// Set GPIO A port pins,AL(Bits 7:0)(input)-AH(Bits 15:8) (output) 8bits
// Input Qualifier =0, none
     EALLOW;
     GpioMuxRegs.GPAMUX.all=0x0000;     
     GpioMuxRegs.GPADIR.all=0xFF00;    	// upper byte as output/low byte as input
     GpioMuxRegs.GPAQUAL.all=0x0000;	// Input qualifier disabled

// Set GPIO B port pins, configured as EVB signals
// Input Qualifier =0, none
// Set bits to 1 to configure peripherals signals on the pins
     GpioMuxRegs.GPBMUX.all=0xFFFF;   
     GpioMuxRegs.GPBQUAL.all=0x0000;	// Input qualifier disabled


     GpioMuxRegs.GPBMUX.all = 0x0000;
     GpioMuxRegs.GPBDIR.bit.GPIOB14 = 1;            //蜂鸣器引脚设置

     GpioMuxRegs.GPBDIR.bit.GPIOB0 = 1;             //LCD引脚设置
     GpioMuxRegs.GPBDIR.bit.GPIOB1 = 1;
     GpioMuxRegs.GPBDIR.bit.GPIOB2 = 1;
     GpioMuxRegs.GPBDIR.bit.GPIOB3 = 1;
     GpioMuxRegs.GPBDIR.bit.GPIOB4 = 1;
     GpioMuxRegs.GPBDIR.bit.GPIOB5 = 1;
     GpioMuxRegs.GPBDIR.bit.GPIOB6 = 1;
     GpioMuxRegs.GPBDIR.bit.GPIOB7 = 1;
     GpioMuxRegs.GPBDIR.bit.GPIOB8 = 1;
     GpioMuxRegs.GPBDIR.bit.GPIOB9 = 1;
     GpioMuxRegs.GPBDIR.bit.GPIOB10 = 1;
     GpioMuxRegs.GPBDIR.bit.GPIOB11 = 1;
     GpioMuxRegs.GPBDIR.bit.GPIOB12 = 1;
     GpioMuxRegs.GPBDIR.bit.GPIOB13 = 1;

     GpioMuxRegs.GPAMUX.bit.TCLKINA_GPIOA12 = 0;    //按键引脚设置
     GpioMuxRegs.GPAMUX.bit.C1TRIP_GPIOA13 = 0;
     GpioMuxRegs.GPAMUX.bit.C2TRIP_GPIOA14 = 0;
     GpioMuxRegs.GPADIR.bit.GPIOA12 = 0;
     GpioMuxRegs.GPADIR.bit.GPIOA13 = 0;
     GpioMuxRegs.GPADIR.bit.GPIOA14 = 0;

     GpioMuxRegs.GPAMUX.bit.PWM1_GPIOA0 = 1;        //功能设置为PWM
     GpioMuxRegs.GPAMUX.bit.PWM2_GPIOA1 = 1;
     GpioMuxRegs.GPAMUX.bit.PWM3_GPIOA2 = 1;
     GpioMuxRegs.GPAMUX.bit.PWM4_GPIOA3 = 1;

     GpioMuxRegs.GPFMUX.bit.SCITXDA_GPIOF4 = 1;     //功能设置为SCI
     GpioMuxRegs.GPFMUX.bit.SCIRXDA_GPIOF5 = 1;
     GpioMuxRegs.GPGMUX.bit.SCITXDB_GPIOG4 = 1;
     GpioMuxRegs.GPGMUX.bit.SCIRXDB_GPIOG5 = 1;

     GpioMuxRegs.GPFMUX.bit.SPISIMOA_GPIOF0 = 1;    //功能设置为SPI
     GpioMuxRegs.GPFMUX.bit.SPISOMIA_GPIOF1 = 1;
     GpioMuxRegs.GPFMUX.bit.SPICLKA_GPIOF2 = 1;
     GpioMuxRegs.GPFMUX.bit.SPISTEA_GPIOF3 = 1;

     GpioMuxRegs.GPFMUX.bit.CANTXA_GPIOF6 = 1;      //功能设置为CAN
     GpioMuxRegs.GPFMUX.bit.CANRXA_GPIOF7 = 1;
     
     EDIS;

}	
	
//===========================================================================
// No more.
//===========================================================================
