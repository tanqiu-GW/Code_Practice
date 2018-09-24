//-----------------------------------------------------------------------------
// updater_F30x.c
//-----------------------------------------------------------------------------
// Copyright 2002 Cygnal Integrated Products, Inc.
//
// AUTH: FB
// DATE: 28 JUN 02
//
// This program shows an example Firmware Updater using the 'F300. It resides
// in FLASH at addresses above 0x1000 and is accessed through a function
// pointer casted as (void code*) 0x1000.   
// 
// Once the firmware update has taken place, the a software reset is issued 
// and the updated firmware takes control of the system. 
// 
// Control Function:
//
// The system is controlled via the hardware UART, operating at a baud rate
// determined by the constant <BAUDRATE>, using Timer1 overflows as the baud
// rate source.
//
// Note: Because this program writes to FLASH, the VDD monitor is enabled in
// in the initialization routine.
//
//
// Target: C8051F30x
// Tool chain: KEIL C51 6.03 / KEIL EVAL C51
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <c8051f300.h>                 // SFR declarations
#include <stdio.h>                     // printf() and getchar()
#include <stdlib.h>
#include <ctype.h>                     // tolower() and toint()

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
#define BAUDRATE     115200            // Baud rate of UART in bps

sbit LED = P0^2;                       // LED='1' means ON
sbit SW2 = P0^3;                       // SW2='0' means switch pressed
sbit TX0 = P0^4;                       // UART0 TX pin
sbit RX0 = P0^5;                       // UART0 RX pin


//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------

void main (void);

// Support Subroutines in Bootloader.c
void print_menu(void);
void erase_flash(void);
void receive_code(void);
unsigned char hex2char();

// Initialization Subroutines
void SYSCLK_Init (void);
void PORT_Init (void);
void UART0_Init (void);


//-----------------------------------------------------------------------------
// Global VARIABLES
//-----------------------------------------------------------------------------

void (*f)();                           // function pointer declaration

bit code_erased = FALSE;               // flag used to indicate that the FLASH
                                       // erase operation is complete
bit f_valid = FALSE;                   // flag to indicate that the FLASH 
                                       // programming operation is complete

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------

void main (void)
{
   
   char input;   

   
   EA = 0;                             // Disable interrupts (precautionary)
   
   PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer 
                                       // enable)

   PORT_Init ();                       // initialize crossbar and GPIO
   SYSCLK_Init ();                     // initialize oscillator
   UART0_Init ();                      // initialize UART0
   
   print_menu();                       // print the command menu

   while (1){
         
      printf("Enter a command > ");
      input = getchar();
      
      switch ( input ){
         
         case '1': erase_flash();   
                   printf("\n*** Flash pages erased\n");
                   receive_code(); 
                   printf("\n** Firmware Update Complete **\n");
                            
         case '2': printf("\n** RESETTING **\n\n");
                   RSTSRC = 0x10;      // reset the device                   
         
         case '?': print_menu(); 
                   break;
                       
         default: print_menu(); 
                  printf("\n*** Unknown Command\n");
      }   

   } // end while

} // end main


//-----------------------------------------------------------------------------
// Support Subroutines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// print_menu
//-----------------------------------------------------------------------------
//
// This routine prints the command menu to the UART.
//
void print_menu(void)
{
  
   printf("\n\nC8051F30x Firmware Updater\n");
   printf("---------------------------------\n");
   printf("1. Erase FLASH and Update Firmware\n");
   printf("2. Cancel Firmware Update\n");
   printf("?. Print Command List\n");
   
}

//-----------------------------------------------------------------------------
// hex2char
//-----------------------------------------------------------------------------
//
// This routine converts a two byte ascii representation of a char to an
// 8-bit variable;
//
unsigned char hex2char()
{
   
   unsigned char retval;
   char byteH, byteL;
   
   // get a two-byte ASCII representation of a char from the UART
   byteH = _getkey();
   byteL = _getkey();
   
   // convert to a single 8 bit result
   retval = (char) toint(byteH) * 16;
   retval += (char) toint(byteL);
   return retval;
}

//-----------------------------------------------------------------------------
// erase_flash
//-----------------------------------------------------------------------------
//
// This routine erases the first 8 pages of FLASH (0x0000 to 0x0FFF).
//
void erase_flash(void)
{
   char xdata* data pagePointer = 0;// a pointer to xdata located in data space
                                    // points to the first FLASH page that 
                                    // will be erased

   int i;                           // temporary int
   bit EA_state;                    // holds interrupt state

   printf("\n*** Erasing flash from 0x0000 to 0x0FFF");
   
   EA_state = EA;                   // save interrupt state
   
   PSCTL = 3;                       // MOVX erases FLASH
   
   // Erase the first 8 FLASH pages
   for (i = 0; i < 8; i++){
      FLKEY = 0xA5;                 // FLASH lock and key sequence 1
      FLKEY = 0xF1;                 // FLASH lock and key sequence 2

      *pagePointer = 0;             // initiate the erase
      
      pagePointer += 512;
   }   

   PSCTL = 0;                       // MOVX writes target XRAM

   EA =  EA_state;                  // restore interrupt state
  
   f_valid = FALSE;                 // indicate that code is no longer valid
   code_erased = TRUE;              // indicate that FLASH has been erased
}

//-----------------------------------------------------------------------------
// receive_code
//-----------------------------------------------------------------------------
// This routine receives the new firmware through the UART in HEX record 
// format.
//
// Hex Record Format:
//
// +--------+--------+------+-------+--------+------(n bytes)------+----------+
// | RECORD | RECLEN |    OFFSET    | RECORD |                     | CHECKSUM |
// |  MARK  |  (n)   |   (2 BYTES)  |  TYPE  |        DATA         |          |
// |  ':'   |        |              |        |                     |          |
// +--------+--------+------+-------+--------+------(n bytes)------+----------+
//
//
void receive_code(void)
{
   char xdata* data pwrite;               // pointer used for writing FLASH
   char code* data pread;                 // pointer used for reading FLASH
   unsigned char len;                     // holds the HEX record length field
   unsigned char record_type;             // holds the HEX record type field
   unsigned int offset;                   // holds the HEX record offset field
                                          // this is the starting address of
                                          // the code image contained in the 
                                          // record

   char checksum;                         // holds the HEX record checksum field
   char flash_checksum;                   // holds the checksum calculated after
                                          // the FLASH has been programmed
   bit EA_state;                          // temporary holder used to restore 
                                          // interrupts to their previous state

   char c;                                // temporary char
   int i;                                 // temporary int
   
   // make sure FLASH has been erased
   if(!code_erased){
      printf("\n*** At least one FLASH page must be erased prior to this operation\n");
      return;
   } else {

      printf("\nReady to receive...\n");
   }

   // wait for the user send HEX file

   do{
      
      while( c = _getkey() != ':' );      // ignore all characters until 
                                          // reaching the record mark field
      
       // get the record length
      len = hex2char();
      
       // get the starting address (offset field in HEX record)
      offset = hex2char();                // get the MSB
      offset <<= 8;                       
      offset |= hex2char();               // get the LSB
      
      
      // get the record type
      record_type = hex2char();
      if( record_type != 0 && record_type != 1 ){
         printf("\n*** Cannot decode HEX file.\n"); 
         return;
      }      


      EA_state = EA;                      // save the interrupt enable bit state
      EA = 0;                             // disable interrupts (precautionary)
         
      PSCTL = 1;                          // MOVX writes to FLASH

      pwrite = (char xdata*) offset;      // initialize the write pointer
      
      
      code_erased = FALSE;                // clear the code_erased flag 
           
      // write the record into FLASH
      for( i = 0; i < len; i++){
         
         // check for valid pointer
         if(pwrite < 0x1000){ 
            FLKEY = 0xA5;                 // FLASH lock and key sequence 1
            FLKEY = 0xF1;                 // FLASH lock and key sequence 2
            *pwrite = hex2char();         // write one byte to FLASH
            pwrite++;                     // increment FLASH write pointer
         } else {
            printf("\n\nExceeded Code Space.\n");  // print error message
         }
     }
      
      PSCTL = 0;                          // MOVX writes target XRAM
      EA = EA_state;                      // restore interrupts to previous state
            
      // verify the checksum
      pread =  (char code*) offset;       // initialize the read pointer
      checksum = hex2char();              // get the HEX record checksum field
      flash_checksum = 0;                 // set the flash_checksum to zero

      // add the data field stored in FLASH to the checksum
      for( i = 0; i < len; i++)
      {
         flash_checksum += *pread++;
      } 
      
      // add the remaining fields
      flash_checksum += len;
      flash_checksum += (char) (offset >> 8);
      flash_checksum += (char) (offset & 0x00FF);
      flash_checksum += record_type;
      flash_checksum += checksum;
      
      // verify the checksum (the flash_checksum should equal zero)
      if(flash_checksum != 0){
         printf("*** checksum failed, try again");
         return;
      }
      
      
   } while(record_type != 1); 

   
   f_valid = TRUE;                        // indicate that download is valid
   
}

//-----------------------------------------------------------------------------
// Initialization Subroutines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// SYSCLK_Init
//-----------------------------------------------------------------------------
//
// This routine initializes the system clock to use the internal 24.5MHz 
// oscillator as its clock source.  Enables missing clock detector reset and 
// VDD monitor. 
//
void SYSCLK_Init (void)
{
   
   OSCICN |= 0x03;                     // configure internal oscillator for
                                       // its maximum frequency
   RSTSRC = 0x06;                      // enable missing clock detector and 
                                       // VDD monitor
 
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
// P0.4 - UART TX (push-pull)
// P0.5 - UART RX
// P0.6 - 
// P0.7 - C2D
//
void PORT_Init (void)
{
   XBR0    = 0x04;                     // P0.2 skipped by the crossbar
   XBR1    = 0x03;                     // UART0 TX and RX pins enabled
   XBR2    = 0x40;                     // Enable crossbar and weak pull-ups
   P0MDIN &= ~0x00;                    // no analog inputs
   P0MDOUT |= 0x14;                    // enable TX0 and P0.2 as 
                                       // push-pull output
}

//-----------------------------------------------------------------------------
// UART0_Init
//-----------------------------------------------------------------------------
//
// Configure the UART0 using Timer1, for <BAUDRATE> and 8-N-1.
//
void UART0_Init (void)
{
   SCON0 = 0x10;                       // SCON0: 8-bit variable bit rate
                                       //        level of STOP bit is ignored
                                       //        RX enabled
                                       //        ninth bits are zeros
                                       //        clear RI0 and TI0 bits
   if (SYSCLK/BAUDRATE/2/256 < 1) {
      TH1 = -(SYSCLK/BAUDRATE/2);
      CKCON |= 0x10;                   // T1M = 1; SCA1:0 = xx
   } else if (SYSCLK/BAUDRATE/2/256 < 4) {
      TH1 = -(SYSCLK/BAUDRATE/2/4);
      CKCON |=  0x01;                  // T1M = 0; SCA1:0 = 01
      CKCON &= ~0x12;
   } else if (SYSCLK/BAUDRATE/2/256 < 12) {
      TH1 = -(SYSCLK/BAUDRATE/2/12);
      CKCON &= ~0x13;                  // T1M = 0; SCA1:0 = 00
   } else {
      TH1 = -(SYSCLK/BAUDRATE/2/48);
      CKCON |=  0x02;                  // T1M = 0; SCA1:0 = 10
      CKCON &= ~0x11;
   }

   TL1 = 0xff;                         // set Timer1 to overflow immediately
   TMOD &= ~0xf0;                      // TMOD: timer 1 in 8-bit autoreload
   TMOD |=  0x20;                       
   TR1 = 1;                            // START Timer1
   TI0 = 1;                            // Indicate TX0 ready
}



