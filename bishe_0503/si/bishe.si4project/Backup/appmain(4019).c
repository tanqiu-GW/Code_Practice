#include"DSP281x_Device.h"
#include"DSP281x_Examples.h"


float32 adc[16];                            //用于存储ADC转换结果
float32 Input[16],Output[16];               //用于保存16个通道实际的输入电压，以及滤波处理后的采样结果
float CalGain,CalOffset;                    //校正算法用于计算的增益和偏移

void sequence (float a[],int n);
void ecantx(Uint64 pBuf);
interrupt void adc_isr(void);
interrupt void sciatxfifo_isr(Uint16 pBuf);
interrupt void sciarxfifo_isr(Uint16 pBuf);
interrupt void scibtxfifo_isr(Uint16 pBuf);
interrupt void scibrxfifo_isr(Uint16 pBuf);
interrupt void spitxfifo_isr(Uint16 pBuf);
interrupt void spirxfifo_isr(Uint16 pBuf);
interrupt void ecanrx_isr(Uint64 pBuf);


void main(void)
{
    Uint16 i;
    

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

    PieVectTable.ECAN0INTA = &ecanrx_isr;
    EDIS;
    
    for(i=0;i<16;i++)
        {
            Input[i] = 0;
            Output[i] = 0;
        }
    Input[0] = 0.420;               //参考电压1
    Input[8] = 1.653;

    PieCtrlRegs.PIEIER1.bit.INTx6 = 1;      //使能PIE模块中的ADC采样中断
    IER |= M_INT1;

    PieCtrlRegs.PIECRTL.bit.ENPIE = 1;
    PieCtrlRegs.PIEIER9.bit.INTx1 = 1;      //使能PIE模块中的SCI中断
    PieCtrlRegs.PIEIER9.bit.INTx2 = 1;
    PieCtrlRegs.PIEIER9.bit.INTx3 = 1;
    PieCtrlRegs.PIEIER9.bit.INTx4 = 1;
    IER |= M_INT9;

    PieCtrlRegs.PIECRTL.bit.ENPIE = 1;      //使能PIE模块中的SPI中断
    PieCtrlRegs.PIEIER6.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER6.bit.INTx2 = 1;
    IER |= M_INT6;

    PieCtrlRegs.PIEIER9.bit.INTx5 = 1;      //使能PIE模块中的ECAN中断
    IER |= M_INT9;
    
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

void ecantx(Uint64 pBuf)
{
    ECanaRegs.CANTRS.all = 0x01000001;      //发送请求置位，邮箱开始发送数据
    while(ECanaRegs.CANTA.all == 0);        //等待邮箱发送完成
    ECanaRegs.CANTA.all = 0x00000001;       //复位发送成功标志位
    ECanaMboxes.MBOX0.MDL.all = pBuf;
    ECanaMboxes.MBOX0.MDH.all = pBuf >> 32;
}

interrupt void adc_isr(void)                //ADC中断函数
{
    Uint16 m,n;
    
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
            for(m=3;m<7;m++)         //中值滤波法
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
            for(n = 0;n<16;n++)      
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

interrupt void sciatxfifo_isr(Uint16 pBuf)
{
    SciaRegs.SCITXBUF = pBuf;
    SciaRegs.SCIFFTX.bit.TXINTCLR = 1;           //清除中断标志
    PieCtrlRegs.PIEACK.all |= 0x0100;            //响应同组其他中断
}
interrupt void sciarxfifo_isr(Uint16 pBuf)
{
    pBuf = SciaRegs.SCIRXBUF.all;
    SciaRegs.SCIFFRX.bit.RXFFOVRCLR = 1;
    SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;
    PieCtrlRegs.PIEACK.all |= 0x1000;
}
interrupt void scibtxfifo_isr(Uint16 pBuf)
{
    ScibRegs.SCITXBUF = pBuf;
    ScibRegs.SCIFFTX.bit.TXINTCLR = 1;           //清除中断标志
    PieCtrlRegs.PIEACK.all |= 0x0100;            //响应同组其他中断
}
interrupt void scibrxfifo_isr(Uint16 pBuf)
{
    pBuf = ScibRegs.SCIRXBUF.all;
    ScibRegs.SCIFFRX.bit.RXFFOVRCLR = 1;
    ScibRegs.SCIFFRX.bit.RXFFINTCLR = 1;
    PieCtrlRegs.PIEACK.all |= 0x1000;
}

interrupt void spitxfifo_isr(Uint16 pBuf)
{
    SpiaRegs.SPITXBUF = pBuf;
    SpiaRegs.SPIFFTX.bit.TXFFINTCLR = 1;        //清除中断标志
    PieCtrlRegs.PIEACK.all |= 0x0020;           //响应同组其他中断
}
interrupt void spirxfifo_isr(Uint16 pBuf)
{
    pBuf = SpiaRegs.SPIRXBUF;
    SpiaRegs.SPIFFRX.bit.RXFFOVFCLR = 1;
    SpiaRegs.SPIFFRX.bit.RXFFINTCLR = 1;
    PieCtrlRegs.PIEACK.all |= 0x0020;
}

interrupt void ecanrx_isr(Uint64 pBuf)
{
    while(ECanaRegs.CANRMP.all != 0x00010000);
    ECanaRegs.CANRMP.all = 0x00010000;
    pBuf = ECanaMboxes.MBOX16.MDL.all;
    pBuf>>32 = ECanaMboxes.MBOX16.MDH.all;
    PieCtrlRegs.PIEACK.bit.ACK9 |= 1;
}