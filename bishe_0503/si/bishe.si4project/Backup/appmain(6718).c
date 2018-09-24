#include"DSP281x_Device.h"
#include"DSP281x_Examples.h"
#include"PI.h"


#define T0          0.0002                  //离散化采样周期0.0002s
#define VolKp       2                       //电压调节Kp系数值
#define VolKi       1                       //Ki系数值
#define VolRef      380                     //基准电压
#define VolLimit    400                     //电压限制值
#define EleKp       2                       //电流调节Kp系数值
#define EleKi       1                       //Ki系数值
#define EleRef      20                      //基准电流
#define EleLimit    25                      //电流限制值


float32 VolOutput[3],EleOutput[3];          //用于存储PI调节后的输出值
float32 adc[16];                            //用于存储ADC转换结果
float32 Input[16],Output[16];               //用于保存16个通道实际的输入电压，以及滤波处理后的采样结果
float CalGain,CalOffset;                    //校正算法用于计算的增益和偏移
Uint16 sciatxbuf[8],sciarxbuf[8],scibtxbuf[8],scibrxbuf[8];
Uint16 spitxbuf[8],spirxbuf[8];             //用于储存通信数据
Uint32 ecantxbuf[2],ecanrxbuf[2];

PI VOL = PI_DEFAULTS;                       //电压调节,电压跟踪基准380V，T2中断
PI ELE = PI_DEFAULTS;                       //电流调节


void sequence (float a[],int n);
void ecantx(void);
interrupt void eva_t1_isr(void);
interrupt void eva_t2_isr(void);
interrupt void evb_t3_isr(void);
interrupt void evb_t4_isr(void);
interrupt void adc_isr(void);
interrupt void sciatxfifo_isr(void);
interrupt void sciarxfifo_isr(void);
interrupt void scibtxfifo_isr(void);
interrupt void scibrxfifo_isr(void);
interrupt void spitxfifo_isr(void);
interrupt void spirxfifo_isr(void);
interrupt void ecanrx_isr(void);


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
    PieVectTable.T1PINT = &eva_t1_isr;
    PieVectTable.T2PINT = &eva_t2_isr;
    PieVectTable.T3PINT = &evb_t3_isr;
    PieVectTable.T4PINT = &evb_t4_isr;
    
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

    PieCtrlRegs.PIEIER2.bit.INTx4 = 1;      //使能周期中断T1，T2，T3，T4
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER4.bit.INTx4 = 1;
    PieCtrlRegs.PIEIER5.bit.INTx1 = 1;
    IER |= (M_INT2 | M_INT3 | M_INT4 | M_INT5);

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

void ecantx(void)
{
    ECanaRegs.CANTRS.all = 0x01000001;      //发送请求置位，邮箱开始发送数据
    while(ECanaRegs.CANTA.all == 0);        //等待邮箱发送完成
    ECanaRegs.CANTA.all = 0x00000001;       //复位发送成功标志位
    ECanaMboxes.MBOX0.MDL.all = ecantxbuf[0];
    ECanaMboxes.MBOX0.MDH.all = ecantxbuf[1];
}

interrupt void eva_t1_isr(void)
{
    VOL.Kp = VolKp;                         //初始化PI控制器
    VOL.Ki = VolKi;
    VOL.T = T0;
    VOL.OutMax = VolLimit;
    //调节电压值
    VOL.Ref = VolRef;                       //电压给定值
    VOL.Fdb = Input[1];                     //电压反馈值
    VOL.Err = VOL.Ref - VOL.Fdb             //偏差
    pi_calc(&VOL);                          //函数调用，启动PI计算
    VolOutput[0] = VOL.Out                  //读取PI控制器的输出
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
            Input[1] = Output[1] * CalGain - CalOffset;     //直流电压采样值
            Input[2] = Output[2] * CalGain - CalOffset;     //逆变电压采样值
            Input[3] = Output[3] * CalGain - CalOffset;     //电网电压采样值
            Input[9] = Output[9] * CalGain - CalOffset;     //并网电流采样值
            Input[10] = Output[10] * CalGain - CalOffset;   //直流电流采样值
            Input[11] = Output[11] * CalGain - CalOffset;   //交流负载电流采样值
        }
    PieCtrlRegs.PIEACK.all = 0x0001;            //响应PIE同组中断
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;         //清除ADC中断标志位
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;           //立即启动下一次转换
    EINT;
}

interrupt void sciatxfifo_isr(void)
{
    Uint16 i;
    for(i=0;i<8;i++)
        SciaRegs.SCITXBUF = sciatxbuf[i];
    SciaRegs.SCIFFTX.bit.TXINTCLR = 1;           //清除中断标志
    PieCtrlRegs.PIEACK.all |= 0x0100;            //响应同组其他中断
}
interrupt void sciarxfifo_isr(void)
{
    Uint16 i;
    for(i=0;i<8;i++)
        sciarxbuf[i] = SciaRegs.SCIRXBUF.all;
    SciaRegs.SCIFFRX.bit.RXFFOVRCLR = 1;
    SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;
    PieCtrlRegs.PIEACK.all |= 0x1000;
}
interrupt void scibtxfifo_isr(void)
{
    Uint16 i;
    for(i=0;i<8;i++)
        ScibRegs.SCITXBUF = scibtxbuf[i];
    ScibRegs.SCIFFTX.bit.TXINTCLR = 1;           //清除中断标志
    PieCtrlRegs.PIEACK.all |= 0x0100;            //响应同组其他中断
}
interrupt void scibrxfifo_isr(void)
{
    Uint16 i;
    for(i=0;i<8;i++)
        scibrxbuf[i] = ScibRegs.SCIRXBUF.all;
    ScibRegs.SCIFFRX.bit.RXFFOVRCLR = 1;
    ScibRegs.SCIFFRX.bit.RXFFINTCLR = 1;
    PieCtrlRegs.PIEACK.all |= 0x1000;
}

interrupt void spitxfifo_isr(void)
{
    Uint16 i;
    for(i=0;i<8;i++)
        SpiaRegs.SPITXBUF = spitxbuf[i];
    SpiaRegs.SPIFFTX.bit.TXFFINTCLR = 1;        //清除中断标志
    PieCtrlRegs.PIEACK.all |= 0x0020;           //响应同组其他中断
}
interrupt void spirxfifo_isr(void)
{
    Uint16 i;
    for(i=0;i<8;i++)
        spirxbuf[i] = SpiaRegs.SPIRXBUF;
    SpiaRegs.SPIFFRX.bit.RXFFOVFCLR = 1;
    SpiaRegs.SPIFFRX.bit.RXFFINTCLR = 1;
    PieCtrlRegs.PIEACK.all |= 0x0020;
}

interrupt void ecanrx_isr(void)
{
    while(ECanaRegs.CANRMP.all != 0x00010000);
    ECanaRegs.CANRMP.all = 0x00010000;
    ecanrxbuf[0] = ECanaMboxes.MBOX16.MDL.all;
    ecanrxbuf[1] = ECanaMboxes.MBOX16.MDH.all;
    PieCtrlRegs.PIEACK.bit.ACK9 |= 1;
}
