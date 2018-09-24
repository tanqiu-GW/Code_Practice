//-----------------------------------------------------------------------------
// blink_slow_F02x.c
//-----------------------------------------------------------------------------
// Copyright 2002 Cygnal Integrated Products, Inc.
//
// AUTH: FB
// DATE: 21 JUN 02
//
// This program shows an example function that can be used with the 
// 'selective code loader example' for the 'F02x family.  
// 
// 
//
// Target: C8051F02x
// Tool chain: KEIL C51 6.03 / KEIL EVAL C51
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <c8051f020.h>                 // SFR declarations

//-----------------------------------------------------------------------------
// 16-bit SFR Definitions for 'F02x
//-----------------------------------------------------------------------------

sfr16 DP       = 0x82;                 // data pointer
sfr16 TMR3RL   = 0x92;                 // Timer3 reload value
sfr16 TMR3     = 0x94;                 // Timer3 counter
sfr16 ADC0     = 0xbe;                 // ADC0 data
sfr16 ADC0GT   = 0xc4;                 // ADC0 greater than window
sfr16 ADC0LT   = 0xc6;                 // ADC0 less than window
sfr16 RCAP2    = 0xca;                 // Timer2 capture/reload
sfr16 T2       = 0xcc;                 // Timer2
sfr16 RCAP4    = 0xe4;                 // Timer4 capture/reload
sfr16 T4       = 0xf4;                 // Timer4
sfr16 DAC0     = 0xd2;                 // DAC0 data
sfr16 DAC1     = 0xd5;                 // DAC1 data

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------
#define TRUE         1
#define FALSE        0

#define SYSCLK       22118400          // SYSCLK frequency in Hz

sbit LED = P1^6;                       // LED='1' means ON
sbit SW2 = P3^7;                       // SW1='0' means switch pressed

//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------

// Subroutines that will be loaded at address 0x1000 
void blink_slow();
void wait_ms(int ms);
void Timer2_Init (int counts);

//-----------------------------------------------------------------------------
// blink_slow
//-----------------------------------------------------------------------------
//
// This routine uses blinks the LED once every second for five seconds.
//
void blink_slow(void) 
{
   static int i; 
   
   Timer2_Init (SYSCLK/12/1000);       // initialize Timer2 to overflow 
                                       // every millisecond     
   for( i = 0; i < 10; i++){
      LED = 0;                         // turn LED off
      wait_ms(500);                    // execute delay loop 
      LED = 1;                         // turn LED on
      wait_ms(500);                    // execute delay loop
   }  
}

//-----------------------------------------------------------------------------
// wait_ms
//-----------------------------------------------------------------------------
//
// This routine uses Timer 2 to insert a delay of <ms> milliseconds.
// Timer 2 overflows once every millisecond
//
void wait_ms(int ms)
{
   TF2 = 0;                            // clear Timer 2 overflow flag
   TR2 = 1;                            // turn Timer 2 On
   

   while (ms != 0){
      if(TF2){
         TF2 = 0;
         ms--;
      }
   }
   
   TR2 = 0;                            // turn Timer 2 Off
   
}

//-----------------------------------------------------------------------------
// Timer2_Init
//-----------------------------------------------------------------------------
//
// This routine initializes Timer2 to 16 bit auto reload mode
//
void Timer2_Init (int counts)
{
   
   CKCON &= ~0x20;                     // Timer 2 counts SYSCLK/12
   RCAP2 = -(counts);                  // set the reload value
   T2 = RCAP2;                         // init Timer2
   ET2 = 0;                            // disable Timer2 interrupts
   TR2 = 0;                            // Timer 2 OFF
}