//-----------------------------------------------------------------------------
// Errors.c
//-----------------------------------------------------------------------------
// Copyright 2015 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// This file contains error list information.
//
//
//-----------------------------------------------------------------------------

#include "Common.h"
#include "Errors.h"

//-----------------------------------------------------------------------------
// Exported Global VARIABLES
//-----------------------------------------------------------------------------

SEGMENT_VARIABLE (ERROR_List[], ERROR_RECORD, SEG_CODE) =
{
   { NO_ERROR,                   "NO_ERROR" },
   { INVALID_COMMAND,            "INVALID_COMMAND" },
   { COMMAND_FAILED,             "COMMAND_FAILED" },
   { INVALID_PARAMS,             "INVALID_PARAMS" },
   { C2DR_WRITE_TIMEOUT,         "C2DR_WRITE_TIMEOUT" },
   { C2DR_READ_TIMEOUT,          "C2DR_READ_TIMEOUT" },
   { C2_POLL_INBUSY_TIMEOUT,     "C2_POLL_INBUSY_TIMEOUT" },
   { C2_POLL_OUTREADY_TIMEOUT,   "C2_POLL_OUTREADY_TIMEOUT" },
   { C2_POLL_OTPBUSY_TIMEOUT,    "C2_POLL_OTPBUSY_TIMEOUT" },
   { DEVICE_READ_PROTECTED,      "DEVICE_READ_PROTECTED" },
   { DEVICE_NOT_BLANK,           "DEVICE_NOT_BLANK" },
   { NOT_A_HEX_RECORD,           "NOT_A_HEX_RECORD" },
   { UNSUPPORTED_HEX_RECORD,     "UNSUPPORTED_HEX_RECORD" },
   { COMMAND_OK,                 "COMMAND_OK" },
   { BAD_CHECKSUM,               "BAD_CHECKSUM" },
   { FAMILY_NOT_SUPPORTED,       "FAMILY_NOT_SUPPORTED" },
   { BAD_DEBUG_COMMAND,          "BAD_DEBUG_COMMAND" },
   { DERIVATIVE_NOT_SUPPORTED,   "DERIVATIVE_NOT_SUPPORTED" },
   { READ_ERROR,                 "READ_ERROR" },
   { OTP_READ_TIMEOUT,           "OTP_READ_TIMEOUT" },
   { OTP_WRITE_TIMEOUT,          "OTP_WRITE_TIMEOUT" },
   { WRITE_ERROR,                "WRITE_ERROR" },
   { SFR_WRITE_TIMEOUT,          "SFR_WRITE_TIMEOUT" },
   { SFR_READ_TIMEOUT,           "SFR_READ_TIMEOUT" },
   { ADDRESS_OUT_OF_RANGE,       "ADDRESS_OUT_OF_RANGE" },
   { PAGE_ERASE_TIMEOUT,         "PAGE_ERASE_TIMEOUT" },
   { DEVICE_ERASE_TIMEOUT,       "DEVICE_ERASE_TIMEOUT" },
   { DEVICE_ERASE_FAILURE,       "DEVICE_ERASE_FAILURE" },
   { DEVICE_IS_BLANK,            "DEVICE_IS_BLANK" },
   { IMAGE_OUT_OF_RANGE,         "IMAGE_OUT_OF_RANGE" },
   { EOF_HEX_RECORD,             "EOF_HEX_RECORD" },
   { VERIFY_FAILURE,             "VERIFY_FAILURE" },
   { IMAGE_NOT_FORMATTED,        "IMAGE_NOT_FORMATTED" },
   { JTAG_POLLBUSY_TIMEOUT,      "JTAG_POLLBUSY_TIMEOUT" },
   { JTAG_IREAD_TIMEOUT,         "JTAG_IREAD_TIMEOUT" },
   { JTAG_IWRITE_TIMEOUT,        "JTAG_IWRITE_TIMEOUT" },
   { JTAG_WRITE_COMMAND_TIMEOUT, "JTAG_WRITE_COMMAND_TIMEOUT" },
   { JTAG_READ_COMMAND_TIMEOUT,  "JTAG_READ_COMMAND_TIMEOUT" }
};


//-----------------------------------------------------------------------------
// End of File
//-----------------------------------------------------------------------------

