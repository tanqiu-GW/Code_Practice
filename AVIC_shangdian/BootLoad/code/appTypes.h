#ifndef _InAppTyesH
#define _InAppTyesH

#include "drvC8051F02xCore.h"

#ifndef NULL
#define NULL            0
#endif

#define FALSE           0
#define TRUE            1

#define ENABLE          1
#define DISABLE         0

#define OK              0
#define ERROE           (-1)

#define HICH(X)         (((X) >> 8) & 0xFF)
#define LOCH(x)         ((x) & 0xFF)

#define FOREVER         for(;;)

#define max(x,y)        ((x) < (y)) ? (y) : (x))
#define min(x,y)        ((x) < (y)) ? (x) : (y))

#define OFFSET(s,m)         ((int)&(((s*)0)-> m))
#define MEMBER_SIZE(s,m)    (sizeof(((s*)0)-> m))
#define NELEMENTS(a)        (sizeof(a)/sizeof((a)[0]))

#define FAST            register
#define IMORT           extern
#define EXPORT          extern
#define LOCAL           static

#define DATA            data
#define IDATA           idata
#define BDATA           bdata
#define XDATA           xdata
#define PDATA           pdata
#define CODE            code

#define U8              unsigned char
#define U16             unsigned int
#define U32             unsigned long
#define WORD            U8

#define S8              char
#define S16             int
#define S32             long

#define VU8             volatile U8
#define VU16            volatile U16
#define VU32            volatile U32

#define PVU8            VU8*
#define PVU16           VU16*
#define PVU32           VU32*

#define STATUS          char
#define BOOL            bit

#define BIT             bit

#define DINT()          EA = 0
#define EINT()          EA = 1

typedef U8      (*pFunU8)(void);
typedef U16     (*pFunU16)(void);
typedef STATUS  (*pFunSt)(void);
typedef BOOL    (*pFunBl)(void);

typedef S16     (*pFunS16)(void);
typedef void    (*pFunVoid)(void);

#endif