#ifndef InDrvSCIH
#define InDrvSCIH



#define SciMayRecv()			(RI0 == 1)
#define SciReadDat()			RI0 = 0;out = SBUF0


extern void SciInit(void);
extern void SciWriteBuf(U8 *pBuf,U16 len);
extern U8 SciReadBuf(U8 *pBuf,U8 len);
extern void Timer_Init(void);


#endif