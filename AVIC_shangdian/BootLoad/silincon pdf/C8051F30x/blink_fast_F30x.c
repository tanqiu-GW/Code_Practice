//-----------------------------------------------------------------------------
// blink_fast_F30x.c
//-----------------------------------------------------------------------------
// Copyright 2002 Cygnal Integrated Products, Inc.
//
// AUTH: FB
// DATE: 28 JUN 02
//
// This program shows an example function that can be used with the 
// 'selective code loader example' for the 'F30x family.  
// 
// 
//
// Target: C8051F30x
// Tool chain: KEIL C51 6.03 / KEIL EVAL C51
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <c8051f300.h>                 // SFR declarations

//-----------------------------------------------------------------------------
// 16-bit SFR Definitions for 'F30x
//-----------------------------------------------------------------------------

sfr16 DP       = 0x82;                 // data pointer
sfr16 TMR2RL   = 0xca;                 // Timer2 reload value
sfr16 TMR2     = 0xcc;                 // Timer2 counter
sfr16 PCA0CP1  = 0xe9;                 // PCA0 Module 1 Capture/Compare
sfr16 PCA0CP2  = 0xeb;                 // PCA0 Module 2 Capture/Compare
sfr16 PCA0     = 0xf9;                 // PCA0 counter
sfr16 PCA0CP0  = 0xfb;                 // PCA0 Module 0 Capture/Compare

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------
#define TRUE         1
#define FALSE        0

#define SYSCLK       24500000          // SYSCLK frequency in Hz

sbit LED = P0^2;                       // LED='1' means ON
sbit SW2 = P0^3;                       // SW2='0' means switch pressed
sbit TX0 = P0^4;                       // UART0 TX pin
sbit RX0 = P0^5;                       // UART0 RX pin

//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------

// Subroutines that will be loaded at address 0x1000 
void blink_fast();
void wait_ms(int ms);
void Timer2_Init (int counts);

//-----------------------------------------------------------------------------
// blink_fast
//-----------------------------------------------------------------------------
//
// This routine uses blinks the LED twice every second for five seconds.
//
void blink_fast(void) 
{  
   static int i;
   
   Timer2_Init(SYSCLK/12/1000);        // Initialize timer 2 to overflow every
                                       // millisecond
   for( i = 0; i < 10; i++){
      LED = 0;                         // turn LED off
      wait_ms(150);                    // execute delay loop 
      LED = 1;                         // turn LED on
      wait_ms(150);                    // execute delay loop
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
   TF2H = 0;                           // clear Timer 2 overflow flag
   TR2 = 1;                            // turn Timer 2 on

   while (ms != 0){
      if(TF2H){
         TF2H = 0;
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
   
   TMR2CN = 0x00;                      // Clear TF2H, TF2L; disable TF2L
                                       // interrupts; T2 in 16-bit mode;
                                       // Timer2 stopped; Timer2 prescaler
                                       // is set to EXTCLK/12
   CKCON &= ~0x60;                     // Timer 2 uses T2 prescaler as clock
                                       // source
   TMR2RL = -(counts);                 // set the reload value
   TMR2 = TMR2RL;                      // init Timer2
   ET2 = 0;                            // disable Timer2 interrupts
   
}

