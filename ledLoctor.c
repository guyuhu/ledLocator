/**************************(C) COPYRIGHT emouse 2011***************************
名称：main.c
功能：模拟SPI程序测试
作者：emouse
时间：2011.1.11
版本：1.0
注意：无
*******************************************************************************/
//#include <iot13v.h>
#include <iom16v.h>
#include <macros.h>

/***************模拟SPI的相关宏定义********************/
#define SPI1_Port PORTB     //设置使用的端口         
#define SPI1_MOSI 0			//设置每个信号对应的引脚
#define SPI1_MOSI_H (SPI1_Port|=(1<<SPI1_MOSI))
#define SPI1_MOSI_L (SPI1_Port&=~(1<<SPI1_MOSI))

unsigned char guideMessage[8]={0,1,0,1,0,1,0,1};
unsigned char idMessage[8]   ={0,0,0,0,0,0,0,1};
unsigned char coordMessage[8]={0,0,0,0,0,0,0,1};
unsigned char checkMessage[8]={0,0,0,0,0,0,0,0};
/*
unsigned char guideMessage=0x01010101;
unsigned char idMessage=1;
unsigned int coordXMessage=300;
unsigned int coordYMessage=300;
*/

unsigned char i;
unsigned int addTime=0;
unsigned char endlineFlag=0;

void _delay_us(unsigned int delay)
{
 	 for(i=0;i<10;i++)
	 {
	   while(delay!=0)
	   {
	   		delay--;		
	   }
	 }
}

/*******************************************************************************
名称：checkOut
功能：校验3个数组，得到校验值。
*******************************************************************************/
void checkOut()
{
	for(i=0;i<=7;i++)
	{
		checkMessage[i]=guideMessage[i]|idMessage[i]|coordMessage[i];
	}
}

/*******************************************************************************
名称：SPI1_Send(unsigned char data)
功能：发送SPI数据
参数：unsigned char data
*******************************************************************************/
void SPI1_Send(unsigned char data[8])
{
    unsigned char i;
    SPI1_MOSI_L;
    for(i=0;i<8;i++)
    {
	
	  	if(data[i]==0) 
		{
		 	 SPI1_MOSI_H;
			_delay_us(2);
			SPI1_MOSI_L;
			_delay_us(1);											   
		}   
        else
		{
		 	SPI1_MOSI_H;
			_delay_us(2);
			SPI1_MOSI_L;
			_delay_us(10);
		}
    }
}

/*******************************************************************************
名称：setMessage()
功能：发送所有的数组信息
*******************************************************************************/
void setMessage()
{

 	 SPI1_MOSI_H;		//	5单位高电平	标示数据帧开始，便于解析													
	_delay_us(10);
	SPI1_MOSI_L;
	_delay_us(1);
	
	SPI1_Send(guideMessage);
	SPI1_Send(idMessage);
	SPI1_Send(coordMessage);
	SPI1_Send(checkMessage);
	
	SPI1_MOSI_H;			//	10单位高电平	标示数据帧结束，便于解析
	_delay_us(20);
	SPI1_MOSI_L;
	_delay_us(1);
}

// Target : M16
// Crystal: 12.000Mhz
//TIMER0 initialize - prescale:1024
// WGM: Normal
// desired value: 100Hz
// actual value: 100.160Hz (0.2%)
void timer0_init(void)
{
 TCCR0 = 0x00; //stop
 TCNT0 = 0x8B; //set count
 //OCR0  = 0x75;  //set compare
 TCCR0 = 0x05; //start timer
}

//call this routine to initialize all peripherals
void init_devices(void)
{
 //stop errant interrupts until set up
 CLI(); //disable all interrupts
 
 DDRA=0xff;                 //用于打开LED锁存
 PORTA=0xfb;//打开LED灯总线 PA2脚输出底电平，打开LED锁存
 
 DDRB=0XFF;
 PORTB=0X04;

 timer0_init();

 MCUCR = 0x00;
 GICR  = 0x00;
 TIMSK = 0x01; //timer interrupt sources
 SEI(); //re-enable interrupts
}

void main(void)
{   
    init_devices();
	checkOut();
    while(1)
    {
		  if(endlineFlag==1)
		 {
		  	setMessage();
			endlineFlag=0;	
			PORTB|=0x04;				
		  }
    }
}

#pragma interrupt_handler timer0_ovf_isr:iv_TIM0_OVF
void timer0_ovf_isr(void)
{
 	 TCNT0 = 0x8B; //reload counter value
	 addTime++;
	 if(addTime==100)
	 {
	  	endlineFlag=1;
		addTime=0;
		PORTB&=0xfb;  //用个小灯来显示，如果出现闪说明进入了中断。
	 }
}