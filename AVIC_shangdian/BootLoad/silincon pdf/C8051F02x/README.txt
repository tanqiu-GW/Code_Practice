The files in this folder accompany the UART In-Application
Code Loading Examples Application note. 

//-------------------------------------------------------------------------
// Utilities
//-------------------------------------------------------------------------

1. Oh51.exe -- a copy of the OMF-51 to HEX file converter utility found
               in the 'bin' directory of the IDE.

//-------------------------------------------------------------------------
// Description of files for the "C8051F02x Selective Code Loading Example"
//-------------------------------------------------------------------------

1. loader_F02x.c       -- Source file that contains the code loading
                          application.

2. blink_fast_F02x.c   -- Source file that contains code that will be
                          selectively loaded.

3. blink_slow_F02x.c   -- Source file that contains code that will be 
                          selectively loaded.

4. blink_fast_F02x.hex -- Selectively loaded code in HEX record format.

5. blink_slow_F02x.hex -- Selectively loaded code in HEX record format.

6. blink_fast_F02x.wsp -- Example project file that shows how to locate
                          functions at a specific address.

7. blink_slow_F02x.wsp -- Example project file that shows how to locate
                          functions at a specific address.

//-------------------------------------------------------------------------
// Description of files for the "C8051F02x Firmware Updating Example"
//-------------------------------------------------------------------------

1. updater_F02x.c      -- Source file that contains the firmware updater.

2. blink_F02x.c        -- source file that contains a sample firmware update.

3. blink_F02x.hex      -- a sample firmware update in HEX record format.

4. updater_F02x.wsp    -- Example project file that shows how to locate 
                          the firmware updater at a specific address.