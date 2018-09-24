//-----------------------------------------------------------------------------
// blink_F30x.c
//-----------------------------------------------------------------------------
// Copyright 2002 Cygnal Integrated Products, Inc.
//
// AUTH: BW, FB
// DATE: 28 JUN 02
//
// This program flashes the green LED on the C8051F30x target board about 
// five times a second using the interrupt handler for Timer2.
//
// Target: C8051F30x
//
// Tool chain: KEIL Eval 'c'
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <c8051f300.h>                    // SFR declarations

//-----------------------------------------------------------------------------
// 16-bit SFR Definitions for 'F30x
//-----------------------------------------------------------------------------

sfr16 DP       = 0x82;                    // data pointer
sfr16 TMR2RL   = 0xca;                    // Timer2 reload value
sfr16 TMR2     = 0xcc;                    // Timer2 counter
sfr16 PCA0CP1  = 0xe9;                    // PCA0 Module 1 Capture/Compare
sfr16 PCA0CP2  = 0xeb;                    // PCA0 Module 2 Capture/Compare
sfr16 PCA0     = 0xf9;                    // PCA0 counter
sfr16 PCA0CP0  = 0xfb;                    // PCA0 Module 0 Capture/Compare

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------

#define SYSCLK       24500000 / 8         // SYSCLK frequency in Hz

sbit LED = P0^2;                          // LED='1' means ON
sbit SW2 = P0^3;                          // SW2='0' means switch pressed

//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
void SYSCLK_Init (void);
void PORT_Init (void);
void Timer2_Init (int counts);
void Timer2_ISR (void);

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------
void main (void) {
   
   void (*update_firmware)();             // function pointer to firmware 
                                          // updating code that is located 
                                          // at 0x1000;

   // disable watchdog timer
   PCA0MD &= ~0x40;                       // WDTE = 0 (clear watchdog timer 
                                          // enable)
	
   SYSCLK_Init ();                        // Initialize system clock to 
                                          // 24.5MHz internal oscillator

   PORT_Init ();                          // Initialize crossbar and GPIO
   Timer2_Init (SYSCLK / 12 / 10);        // Init Timer2 to generate 
                                          // interrupts at a 10Hz rate.

   EA = 1;                                // enable global interrupts

   update_firmware = (void code*) 0x1000; // assign the function pointer

   while (1) {                            // spin forever
   
      if (!SW2){
         update_firmware();
         
      }
   }
}

//-----------------------------------------------------------------------------
// SYSCLK_Init
//-----------------------------------------------------------------------------
//
// This routine initializes the system clock to use the internal 24.5MHz / 8 
// oscillator as its clock source.  Also enables missing clock detector reset
// and the VDD Monitor. 
//
// NOTE: This program must not disable the VDD monitor since it is enabled by
// Firmware Updater.  If this program disables the VDD monitor, there is 
// potential for going into an infinite loop turning the VDD monitor on 
// and off.  
//
void SYSCLK_Init (void)
{
   OSCICN = 0x04;                         // configure internal oscillator for
                                          // its lowest frequency
   RSTSRC = 0x06;                         // enable missing clock detector
                                          // and VDD Monitor.
}

//-----------------------------------------------------------------------------
// PORT_Init
//-----------------------------------------------------------------------------
//
// Configure the Crossbar and GPIO ports.
// P0.0 - 
// P0.1 -
// P0.2 - LED (push-pull)
// P0.3 - SW2
// P0.4 - 
// P0.5 - 
// P0.6 - 
// P0.7 - C2D
//
void PORT_Init (void)
{
   XBR0     = 0x04;                       // skip P0.2 (LED) in crossbar pin
                                          // assignments
   XBR1     = 0x00;                       // no digital peripherals selected
   XBR2     = 0x40;                       // Enable crossbar and weak pull-ups
   P0MDOUT |= 0x04;                       // enable LED as a push-pull output
}

//-----------------------------------------------------------------------------
// Timer2_Init
//-----------------------------------------------------------------------------
//
// Configure Timer2 to 16-bit auto-reload and generate an interrupt at 
// interval specified by <counts> using SYSCLK/12 as its time base.
//
void Timer2_Init (int counts)
{
   TMR2CN  = 0x00;                        // Stop Timer2; Clear TF2;
                                          // use SYSCLK/12 as timebase
   CKCON  &= ~0x60;                       // Timer2 clocked based on T2XCLK;

   TMR2RL  = -counts;                     // Init reload values
   TMR2    = 0xffff;                      // set to reload immediately
   ET2     = 1;                           // enable Timer2 interrupts
   TR2     = 1;                           // start Timer2
}

//-----------------------------------------------------------------------------
// Interrupt Service Routines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Timer2_ISR
//-----------------------------------------------------------------------------
// This routine changes the state of the LED whenever Timer2 overflows.
//
void Timer2_ISR (void) interrupt 5
{
   TF2H = 0;                              // clear Timer2 interrupt flag
   LED = ~LED;                            // change state of LED
}