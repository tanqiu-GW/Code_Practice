/********************************************************************************

 *************************Copyright (C), 2018, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : drvHC595.c
 * @brief   		  : .C file function description
 * @author       : gw
 * @version        : 1.0
 * @date          : 2018-12-18
 * 
 * 
 * @note History:
 * @note        : 595串转并芯片驱动 2018-12-18
 * @note        : 595控制引脚OE接地，SCLR数据清零引脚接高电平；若多个595芯片级联
 *				  那么多个芯片的SCLK和RCLK接在一起
 *   Modification: Created file

********************************************************************************/
/* 头文件 */
#include "drvHC595.h"


/* 宏定义 */
//这里未指定595三个输入端口对应的CPU控制引脚，可以用GPIO或者其他SPI等控制
#define PIN_SCLK_HC595		//GPIOA0		//595数据输入时钟，即移位时钟，上升沿时数据移位
#define PIN_RCLK_HC595		//GPIOA1		//595存储器锁存时钟，即上升沿时数据存储器锁存
#define PIN_DATA_HC595		//GPIOA2		//数据输入端
//利用GPIO控制595
#define SCLK_LOW_HC595()	//gpioa0 = 0
#define SCLK_HIGH_HC595()	//gpioa0 = 1
#define RCLK_LOW_HC595()	//gpioa1 = 0
#define RCLK_HIGH_HC595()	//gpioa1 = 1
#define DATA_LOW_HC595()	//gpioa2 = 0
#define DATA_HIGH_HC595()	//gpioa2 = 1



/* 局部函数声明 */
static void gpioconfig_HC595(void);//595控制引脚GPIO口配置
static void send_byte_HC595(unsigned char data);//单个字节数据送入595后并行输出
static void send_enable_HC595(void);



/**
 * @fn       void gpioconfig_HC595(void)
 * @brief    控制595的GPIO口配置
 * 
 * @param[in]          void  
 * @return         
 */
void gpioconfig_HC595(void)
{
	/* gpio配置为输出，初始化为高电平 */
	;
}

/**
 * @fn       void send_byte_HC595(unsigned char data)
 * @brief    将一个字节的数据输入到595中
 * 
 * @param[in]          unsigned char data  
 * @return         
 */
void send_byte_HC595(unsigned char data)
{
	unsigned char idx,temp;

	for(idx = 0; idx < 8; idx++)
	{
		temp = data & 0x80;	//取最高位，送入595

		if(temp){DATA_HIGH_HC595();}
		else{DATA_LOW_HC595();}

		SCLK_LOW_HC595();	//产生SCLK上升沿，进行移位操作
		nop;nop;nop;
		SCLK_HIGH_HC595();
		nop;nop;nop;

		data <<= 1;
	}
}

/**
 * @fn       void send_enable_HC595(void)
 * @brief    595使能输出，上升沿将数据锁存
 * 
 * @param[in]          void  
 * @return         
 */
void send_enable_HC595(void)
{
	RCLK_LOW_HC595();
	nop;nop;nop;
	RCLK_HIGH_HC595();
	nop;nop;nop;
}

/**
 * @fn       void init_HC595(void)
 * @brief    初始化595
 * 
 * @param[in]          void  
 * @return         
 */
void init_HC595(void)
{
	gpioconfig_HC595();
}

/**
 * @fn       void send_multbyte_HC595(unsigned char * data, unsigned int len)
 * @brief    将多个字节输入到多片级联的595芯片中
 * 
 * @param[in]          unsigned char * data  
 * @param[in]        unsigned int len      
 * @return         
 */
void send_multbyte_HC595(unsigned char * data, unsigned int len)
{
	unsigned int idx;

	for(idx = 0; idx < len; idx++)
	{
		send_byte_HC595(data[idx]);	//多个字节按顺序输入到595
	}

	send_enable_HC595();
}

