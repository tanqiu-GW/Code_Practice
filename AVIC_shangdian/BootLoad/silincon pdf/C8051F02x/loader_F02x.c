//-----------------------------------------------------------------------------
// loader_F02x.c
//-----------------------------------------------------------------------------
// Copyright 2002 Cygnal Integrated Products, Inc.
//
// AUTH: FB
// DATE: 28 JUN 02
//
// This program shows an example 'selective code loader' using the 'F02x. It 
// designates the FLASH page at 0x1000 for the code loaded through the UART. 
// 
// Control Function:
//
// The system is controlled via the hardware UART, operating at a baud rate
// determined by the constant <BAUDRATE>, using Timer1 overflows as the baud
// rate source.
//
// Received File Type:
//
// This example receives Intel HEX files which are OMF51 (linker output files)
// passed through the OH51 utility in the 'CYGNAL\IDEfiles\C51\Bin' folder. 
// 
// Note: Because this program writes to FLASH, the MONEN pin should be tied 
//       high.
//
// Target: C8051F02x
// Tool chain: KEIL C51 6.03 / KEIL EVAL C51
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <c8051f020.h>                 // SFR declarations
#include <stdio.h>                     // printf() and getchar()
#include <ctype.h>                     // tolower() and toint()

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
#define BAUDRATE     115200            // Baud rate of UART in bps

sbit LED = P1^6;                       // LED='1' means ON
sbit SW2 = P3^7;                       // SW2='0' means switch pressed

//-----------------------------------------------------------------------------
// Reserved Memory Space
//-----------------------------------------------------------------------------

char reserved_memory_bank[2] _at_ 0x08;// This memory bank is used by the
                                       // functions that will be loaded 
                                       // through the UART.
                                       // The memory bank location and size
                                       // are based on values from the M51 map
                                       // file generated when the loaded code
                                       // is linked.

//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------

void main (void);

// Support Subroutines
void print_menu(void);
void erase_flash_page(void);
void receive_code(void);
unsigned char hex2char();

// Initialization Subroutines
void SYSCLK_Init (void);
void PORT_Init (void);
void UART0_Init (void);

//-----------------------------------------------------------------------------
// Global VARIABLES
//-----------------------------------------------------------------------------

#define input_str_len 4                // buffer to hold characters entered               
char input_str[input_str_len];         // at the command prompt

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

   WDTCN = 0xde;                       // disable watchdog timer
   WDTCN = 0xad;

   PORT_Init ();                       // initialize crossbar and GPIO
   SYSCLK_Init ();                     // initialize oscillator
   UART0_Init ();                      // initialize UART0
   
   print_menu();                       // print the command menu

   while (1){
         
      printf("\nEnter a command > ");
      gets(input_str, input_str_len);
      
      switch ( input_str[0] ){
      
         case '1': erase_flash_page();   
                   printf("\nFlash page 0x1000 has been erased.\n");
                   break;

         case '2': printf("\nReady to receive HEX file...\n");
                   receive_code();
                   break;

         case '3': if(f_valid){
                     f = (void code *) 0x1000;
                     f();
                     printf("\nFinished\n");
                   } else {
                     printf("\n*** No function exists at 0x1000.\n");
                   }
                   break; 

         case '?': print_menu(); 
                   break;    

         default:  printf("\n*** Unknown Command.\n");
                   break;
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
// This routine uses prints the command menu to the UART.
//
void print_menu(void)
{
  
   printf("\n\nC8051F02x Selective Code Loader Example\n");
   printf("------------------------------------------\n");
   printf("1. Erase the flash page at 0x1000\n");
   printf("2. Receive HEX file\n");
   printf("3. Execute the function at 0x1000\n");
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
// erase_flash_page
//-----------------------------------------------------------------------------
//
// This routine erases the FLASH page located at 0x1000
//
void erase_flash_page(void)
{  
   bit EA_state;
   char xdata* data pagePointer = 0x1000; // pointer to xdata space located 
                                          // in data space
   
   EA_state = EA;                   // holds interrupt state

   EA = 0;                          // disable interrupts
   FLSCL |= 0x01;                   // enable FLASH write/erase
   PSCTL  = 0x03;                   // MOVX erases FLASH
   
   // Erase the FLASH page at 0x1000
   *pagePointer = 0;                // initiate the erase
   
   PSCTL = 0x00;                    // MOVX writes target XRAM
   FLSCL &= ~0x01;                  // disable FLASH write/erase
   
   EA =  EA_state;                  // restore interrupt state

   f_valid = FALSE;                 // indicate that code is no longer valid
   code_erased = TRUE;              // indicate that FLASH has been erased
}

//-----------------------------------------------------------------------------
// receive_code
//-----------------------------------------------------------------------------
//
// This routine receives HEX records through the UART and writes the 
// function located at 0x1000.
//
// Hex Record Format:
//
// +--------+--------+------+-------+--------+------(n bytes)------+----------+
// | RECORD | RECLEN |    OFFSET    | RECORD |                     | CHECKSUM |
// |  MARK  |  (n)   |   (2 BYTES)  |  TYPE  |        DATA         |          |
// |  ':'   |        |              |        |                     |          |
// +--------+--------+------+-------+--------+------(n bytes)------+----------+
//
void receive_code(void)
{

   char xdata* data pwrite;               // pointer used for writing FLASH
   char code* data pread;                 // pointer used for reading FLASH
   unsigned int  len;                     // holds the HEX record length field
   char record_type;                      // holds the HEX record type field
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
   
   // make sure the FLASH page has been erased
   if(!code_erased){
      printf("\n*** At least one FLASH page must be erased prior");
      printf(" to this operation.\n");
      return;
   }
   
   // wait for the user to send HEX file

   do{
      
      while( c = _getkey() != ':' );      // ignore all characters until  
                                          // reaching the record mark field
      
      // get the record length
      len = hex2char();
      
      // get the starting address (offset field in HEX record)
      offset = hex2char();
      offset <<= 8;
      offset |= hex2char();

      // get the record type
      record_type = hex2char();
      if( record_type != 0 && record_type != 1 ){
         printf("\n*** Cannot decode HEX file.\n"); 
         return;
      }      
      
      EA_state = EA;                      // save the interrupt enable bit state
      
      EA = 0;                             // disable interrupts (precautionary)   
      FLSCL |= 0x01;                      // enable FLASH write/erase
      PSCTL  = 0x01;                      // MOVX writes FLASH
   
      pwrite = (char xdata*) offset;      // initialize the write pointer
            
      code_erased = FALSE;                // clear the code_erased flag
           
      // write the record into FLASH
      for( i = 0; i < len; i++){
         *pwrite = hex2char();            // write one byte to FLASH
         pwrite++;                        // increment FLASH write pointer
         
      }
      
      PSCTL = 0x00;                       // MOVX writes target XRAM
      FLSCL &= ~0x01;                     // disable FLASH write/erase
      EA = EA_state;                      // restore interrupts to previous state
      
      // verify the checksum
      pread =  (char code*) offset;       // initialize the read pointer
      checksum = hex2char();              // get the HEX record checksum field
      flash_checksum = 0;                 // set the flash_checksum to zero
      
      // add the data field stored in FLASH to the checksum
      for( i = 0; i < len; i++){
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
         printf("*** Checksum failed, try again.");
         return;
      }
      
   } while(record_type != 1); 
  
   f_valid = TRUE;                     // flag that the "f()" function is valid
   
   _getkey();                          // remove carriage return from input
                                       // stream   

   printf("\nReceived OK\n");  
}

//-----------------------------------------------------------------------------
// Initialization Subroutines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// SYSCLK_Init
//-----------------------------------------------------------------------------
//
// This routine initializes the system clock to use an 22.1184MHz crystal
// as its clock source.
//
void SYSCLK_Init (void)
{
   int i;                              // delay counter

   OSCXCN = 0x67;                      // start external oscillator with
                                       // 22.1184MHz crystal

   for (i=0; i < 256; i++) ;           // wait for osc to start

   while (!(OSCXCN & 0x80)) ;          // Wait for crystal osc. to settle

   OSCICN = 0x88;                      // select external oscillator as SYSCLK
                                       // source and enable missing clock
                                       // detector
}

//-----------------------------------------------------------------------------
// PORT_Init
//-----------------------------------------------------------------------------
//
// Configure the Crossbar and GPIO ports
//
void PORT_Init (void)
{
   XBR0    = 0x04;                     // Enable UART0
   XBR1    = 0x00;
   XBR2    = 0x40;                     // Enable crossbar and weak pull-ups
   P0MDOUT |= 0x01;                    // enable TX0 as a push-pull output
   P1MDOUT |= 0x40;                    // enable P1.6 (LED) as push-pull output
}

//-----------------------------------------------------------------------------
// UART0_Init
//-----------------------------------------------------------------------------
//
// Configure the UART0 using Timer1, for <baudrate> and 8-N-1.
//
void UART0_Init (void)
{
   SCON0   = 0x50;                     // SCON0: mode 1, 8-bit UART, enable RX
   TMOD    = 0x20;                     // TMOD: timer 1, mode 2, 8-bit reload
   TH1    = -(SYSCLK/BAUDRATE/16);     // set Timer1 reload value for baudrate
   TR1    = 1;                         // start Timer1
   CKCON |= 0x10;                      // Timer1 uses SYSCLK as time base
   PCON  |= 0x80;                      // SMOD00 = 1
   TI0    = 1;                         // Indicate TX0 ready
}