#include"DSP281x_Device.h"
#include"DSP281x_Examples.h"


float32 adc[16];                            //用于存储ADC转换结果
float32 Input[16],Output[16];               //用于保存16个通道实际的输入电压，以及滤波处理后的采样结果
float CalGain,CalOffset;                    //校正算法用于计算的增益和偏移

void sequence (float a[],int n);
void ecantx(Uint32 *pBuf);
interrupt void adc_isr(void);
interrupt void sciatxfifo_isr(Uint16 pBuf[],Uint16 len);
interrupt void sciarxfifo_isr(Uint16 *pBuf,Uint16 len);
interrupt void scibtxfifo_isr(Uint16 *pBuf,Uint16 len);
interrupt void scibrxfifo_isr(Uint16 *pBuf,Uint16 len);
interrupt void spitxfifo_isr(Uint16 *pBuf,Uint16 len);
interrupt void spirxfifo_isr(Uint16 *pBuf,Uint16 len);
interrupt void ecanrx_isr(void);


void main(void)
{

    InitSysCtrl();
    DINT;
    IER = 0x0000;
    IFR = 0x0000;
    InitPieCtrl();
    InitPieVectTable();
    InitEv();
    InitGpio();
    InitAdc();
    InitSci();
    InitSpi();
    InitECan();
    EALLOW;
    PieVectTable.ADCINT = &adc_isr;
    
    PieVectTable.RXAINT = &sciarxfifo_isr;
    PieVectTable.TXAINT = &sciatxfifo_isr;
    PieVectTable.RXBINT = &scibrxfifo_isr;
    PieVectTable.TXBINT = &scibtxfifo_isr;
    
    PieVectTable.SPIRXINTA = &spirxfifo_isr;
    PieVectTable.SPITXINTA = &spitxfifo_isr;
    EDIS;
    
    for(Uint16 i=0;i<16;i++)
        {
            Input[i] = 0;
            Output[i] = 0;
        }
    Input[0] = 0.420;               //参考电压1
    Input[8] = 1.653;

    PieCtrlRegs.PIEIER1.bit.INTx6 = 1;      //使能PIE模块中的ADC采样中断
    IER |= M_INT1;
    EINT;
    ERTM;
    EvaRegs.T1CON.bit.TENABLE = 1;          //启动T1计数

    while(1)
        {
        }
}

void sequence(float a [ ], int n)           //冒泡排序，将数组元素有小到大排列
{
    Uint16 i = 0,j = 0;
    float32 temp = 0;
    for(i = 0;i < n;i++)
        {
            for(j = j+1;j <= n;j++)
                {
                    if(a[i]>a[j])
                        {
                            temp = a[i];
                            a[i] = a[j];
                            a[j] = temp;
                        }
                }
        }
}



interrupt void adc_isr(void)                //ADC中断函数
{
    Uint16 SampleCount = 0;
    float32 adca0[10];
    float32 adca1[10];
    float32 adca2[10];
    float32 adca3[10];
    float32 adcb0[10];                      //用于保存ADCB通道的10次采样结果
    float32 adcb1[10];
    float32 adcb2[10];
    float32 adcb3[10];
    SampleCount ++;                         //采样计数器计数
    //读取转换结果
    adc[0] = ((float)AdcRegs.ADCRESULT0)*3.0/65520;
    adc[1] = ((float)AdcRegs.ADCRESULT1)*3.0/65520;
    adc[2] = ((float)AdcRegs.ADCRESULT2)*3.0/65520;
    adc[3] = ((float)AdcRegs.ADCRESULT3)*3.0/65520;
    adc[8] = ((float)AdcRegs.ADCRESULT8)*3.0/65520;
    adc[9] = ((float)AdcRegs.ADCRESULT9)*3.0/65520;
    adc[10] = ((float)AdcRegs.ADCRESULT10)*3.0/65520;
    adc[11] = ((float)AdcRegs.ADCRESULT11)*3.0/65520;
    //将每个通道采样得到的数据存入数组中，等待数据处理
    adca0[SampleCount - 1] = adc[0];
    adca1[SampleCount - 1] = adc[1];
    adca2[SampleCount - 1] = adc[2];
    adca3[SampleCount - 1] = adc[3];
    adcb0[SampleCount - 1] = adc[8];
    adcb1[SampleCount - 1] = adc[9];
    adcb2[SampleCount - 1] = adc[10];
    adcb3[SampleCount - 1] = adc[11];
    if(SampleCount == 10)
        {
            sequence(adca0,10);
            sequence(adca1,10);
            sequence(adca2,10);
            sequence(adca3,10);
            sequence(adcb0,10);
            sequence(adcb1,10);
            sequence(adcb2,10);
            sequence(adcb3,10);
            for(Uint16 m=3;m<7;m++)         //中值滤波法
                {
                    Output[0] = Output[0] + adca0[m];
                    Output[1] = Output[1] + adca1[m];
                    Output[2] = Output[2] + adca2[m];
                    Output[3] = Output[3] + adca3[m];
                    Output[8] = Output[8] + adcb0[m];
                    Output[9] = Output[9] + adcb1[m];
                    Output[10] = Output[10] + adcb2[m];
                    Output[11] = Output[11] + adcb3[m];
                }
            SampleCount = 0;                //清采样计数器，进入新的连续10次的采样
            for(Uint16 n = 0;n<16;n++)      
                Output[n] = Output[n]/4;    //计算4个数据的平均值
            CalGain = (Input[8] - Input[0])/(Output[8] - Output[0]);
            CalOffset = (Input[8] * Output[0] - Input[0] * Output[8])/(Output[8] - Output[0]);
            //通过采样数据来计算实际的输入
            Input[1] = Output[1] * CalGain - CalOffset;
            Input[2] = Output[2] * CalGain - CalOffset;
            Input[3] = Output[3] * CalGain - CalOffset;
            Input[9] = Output[9] * CalGain - CalOffset;
            Input[10] = Output[10] * CalGain - CalOffset;
            Input[11] = Output[11] * CalGain - CalOffset;
        }
    PieCtrlRegs.PIEACK.all = 0x0001;            //响应PIE同组中断
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;         //清除ADC中断标志位
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;           //立即启动下一次转换
    EINT;
}

interrupt void sciatxfifo_isr(Uint16 pBuf[], Uint16 len)
{
    while(len != 0)
        {
            SciaRegs.SCITXBUF = pBuf[0];
            len--;
        }
    SciaRegs.SCIFFTX.bit.TXINTCLR = 1;          //清除中断标志
    PieCtrlRegs.PIEACK.all |= 0x0100;            //响应同组其他中断
}
interrupt void sciarxfifo_isr(Uint16 *pBuf,Uint16 len)
{
    while(len != 0)
        {
            *pBuf++ = SciaRegs.SCIRXBUF.all;
            len--;
        }
    SciaRegs.SCIFFRX.bit.RXFFOVRCLR = 1;
    SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;
    PieCtrlRegs.PIEACK.all |= 0x1000;
}
interrupt void scibtxfifo_isr(Uint16 * pBuf, Uint16 len)
{
    while(len != 0)
        {
            ScibRegs.SCITXBUF = *pBuf++;
            len--;
        }
    ScibRegs.SCIFFTX.bit.TXINTCLR = 1;          //清除中断标志
    PieCtrlRegs.PIEACK.all |= 0x0100;            //响应同组其他中断
}
interrupt void scibrxfifo_isr(Uint16 *pBuf,Uint16 len)
{
    while(len != 0)
        {
            *pBuf++ = ScibRegs.SCIRXBUF.all;
            len--;
        }
    ScibRegs.SCIFFRX.bit.RXFFOVRCLR = 1;
    ScibRegs.SCIFFRX.bit.RXFFINTCLR = 1;
    PieCtrlRegs.PIEACK.all |= 0x1000;
}

interrupt void spitxfifo_isr(Uint16 * pBuf, Uint16 len)
{
    while(len != 0)
        {
            SpiaRegs.SPITXBUF = *pBuf++;
            len--;
        }
    SpiaRegs.SPIFFTX.bit.TXFFINTCLR = 1;        //清除中断标志
    PieCtrlRegs.PIEACK.all |= 0x0020;           //响应同组其他中断
}
interrupt void spirxfifo_isr(Uint16 * pBuf, Uint16 len)
{
    while(len != 0)
        {
            *pBuf++ = SpiaRegs.SPIRXBUF;
            len--;
        }
    SpiaRegs.SPIFFRX.bit.RXFFOVFCLR = 1;
    SpiaRegs.SPIFFRX.bit.RXFFINTCLR = 1;
    PieCtrlRegs.PIEACK.all |= 0x0020;
}
