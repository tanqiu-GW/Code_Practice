// TI File $Revision: /main/2 $
// Checkin $Date: April 29, 2005   11:11:45 $
//###########################################################################
//
// FILE:	DSP281x_Adc.c
//
// TITLE:	DSP281x ADC Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP281x C/C++ Header Files V1.20 $
// $Release Date: July 27, 2009 $
//###########################################################################

#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File

#define ADC_usDELAY  8000L
#define ADC_usDELAY2 20L

//---------------------------------------------------------------------------
// InitAdc: 
//---------------------------------------------------------------------------
// This function initializes ADC to a known state.
//
void InitAdc(void)
{
	extern void DSP28x_usDelay(Uint32 Count);
	
    // To powerup the ADC the ADCENCLK bit should be set first to enable
    // clocks, followed by powering up the bandgap and reference circuitry.
    // After a 5ms delay the rest of the ADC can be powered up. After ADC
    // powerup, another 20us delay is required before performing the first
    // ADC conversion. Please note that for the delay function below to
    // operate correctly the CPU_CLOCK_SPEED define statement in the
    // DSP28_Examples.h file must contain the correct CPU clock period in
    // nanoseconds. For example:
    AdcRegs.ADCTRL1.bit.RESET = 1;
    AdcRegs.ADCTRL1.bit.RESET = 0;
    //仿真暂停时，序列发生器和其他数字电路逻辑立即停止
    AdcRegs.ADCTRL1.bit.SUSMOD = 3;
    AdcRegs.ADCTRL1.bit.ACQ_PS = 0;         //采样窗口大小，soc脉冲宽度为1个ADCLK
    AdcRegs.ADCTRL1.bit.CPS = 0;            //核时钟预定标器，等于0，未将时钟进行2分频
    AdcRegs.ADCTRL1.bit.CONT_RUN = 0;       //运行于启动/停止模式
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 0;       //级联方式
    
	AdcRegs.ADCTRL3.bit.ADCBGRFDN = 0x3;	// Power up bandgap/reference circuitry
	DELAY_US(ADC_usDELAY);                  // Delay before powering up rest of ADC
	AdcRegs.ADCTRL3.bit.ADCPWDN = 1;		// Power up rest of ADC
	DELAY_US(ADC_usDELAY2);                 // Delay after powering up ADC

    AdcRegs.ADCTRL3.bit.ADCCLKPS = 15;      //ADCLK=HSPCLK/30
    AdcRegs.ADCTRL3.bit.SMODE_SEL = 0;      //采用顺序采样模式
    AdcRegs.ADCMAXCONV.all = 15;            //总共采样16路
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0;    //参考通道1，inputl = 0.420V
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 1;    //对ADCINA1通道进行采样
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 2;
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 3;
    AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 4;
    AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 5;
    AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 6;
    AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 7;
    AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 8;    //参考通道2，inputh = 1.653V
    AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 9;
    AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 10;
    AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 11;
    AdcRegs.ADCCHSELSEQ4.bit.CONV12 = 12;
    AdcRegs.ADCCHSELSEQ4.bit.CONV13 = 13;
    AdcRegs.ADCCHSELSEQ4.bit.CONV14 = 14;
    AdcRegs.ADCCHSELSEQ4.bit.CONV15 = 15;
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;     //清除SEQ1中的中断标志位INT_SEQ1
    AdcRegs.ADCST.bit.INT_SEQ2_CLR = 1;
    AdcRegs.ADCTRL2.bit.EVB_SOC_SEQ = 0;
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0;
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;   //SEQ1的中断使能
    AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1 = 0;
    AdcRegs.ADCTRL2.bit.EVA_SOC_SEQ1 = 1;   //EVA事件启动AD转换
    AdcRegs.ADCTRL2.bit.EXT_SOC_SEQ1 = 0;
    AdcRegs.ADCTRL2.bit.RST_SEQ2 = 0;
    AdcRegs.ADCTRL2.bit.SOC_SEQ2 = 0;
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ2 = 0;
    AdcRegs.ADCTRL2.bit.INT_MOD_SEQ2 = 0;
    AdcRegs.ADCTRL2.bit.EVB_SOC_SEQ2 = 0;
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 0;
}	

//===========================================================================
// No more.
//===========================================================================
