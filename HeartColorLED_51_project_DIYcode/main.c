/******************************************************************************************
*说明：将32个LED分成4组LED_P0,LED_P1,LED_P3,LED_P2,每一组代表8个LED灯，也就是讲心形分成4个部分，
*      如下图所示，这样，我们只需操作这些值，然后将这些值对应到相应的IO口上就可以了
*
*							      LED_P0.2					       LED_P2.5					
*						  LED_P0.3	  LED_P0.1		 LED_P2.6		 LED_P2.4				
*				  	LED_P0.4				LED_P0.0 LED_P2.7				 LED_P2.3			
*				  LED_P0.5											               LED_P2.2		
*			  LED_P0.6													               LED_P2.1	
*		  LED_P0.7															               LED_P2.0
*	  	LED_P1.0															               LED_P3.7
*		  	 LED_P1.1													              LED_P3.6	
*				    LED_P1.2											           LED_P3.5		
*					     LED_P1.3									          LED_P3.4			
*						      LED_P1.4							       LED_P3.3				
*							       LED_P1.5					      LED_P3.2					
*								        LED_P1.6		     LED_P3.1						
*								         	  LED_P1.7 LED_P3.0							
*
***********************************************************************************************/

#include <reg52.h>
#define	uint	unsigned int
#define	uchar	unsigned char

#define FOSC 12000000L //晶振设置，使用11.0592M Hz 6T双速倍模式

volatile uchar LED_P0 = 0xff;
volatile uchar LED_P1 = 0xff;
volatile uchar LED_P2 = 0xff;
volatile uchar LED_P3 = 0xff;

#define SCENE_COUNT 20//定义循环播放发的数量

//可自定义场景，按场景顺序播放多种状态
uchar scene[SCENE_COUNT] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};

uchar code table0[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//LED从低位往高位移
uchar code table1[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};//LED从高位往低位移
uchar code table2[]={0xfe,0xfc,0xf8,0xf0,0xe0,0xc0,0x80,0x00};//LED从1个亮到8个都点亮(从低位往高位)
uchar code table3[]={0x7f,0x3f,0x1f,0x0f,0x07,0x03,0x01,0x00};//LED从1个亮到8个都点亮(从高位往低位)
uchar code table4[]={0x00,0x01,0x03,0x07,0x0f,0x1f,0x3f,0x7f,0xff};//LED从8个全亮到一个都不亮(从低位往高位)
uchar code table5[]={0x00,0x80,0xc0,0xe0,0xf0,0xf8,0xfc,0xfe,0xff};//LED从8个全亮到一个都不亮(从高位往低位)
uchar code table6[]={0xfe,0xfc,0xfa,0xf6,0xee,0xde,0xbe,0x7e};//LED从低位往高位移(最低位始终为0)
uchar code table7[]={0x7f,0x3f,0x5f,0x6f,0x77,0x7b,0x7d,0x7e};//LED从高位往低位移(最高位始终为0)
uchar i,j;		//定义循环变量
uint tt=70;		//定义时间指数
	
//延时函数
void Delayms(uint ms)
{
	uint x,y;
	for(x=ms;x>0;x--)
	for(y=125;y>0;y--);
}

//将LED_P0,LED_P1,LED_P3,LED_P2的值的对应到具体IO口上，并延时
void Display(uint time)	
{
	P0 = ((LED_P0 & 0xfe)>>1) + ((LED_P1 & 0x01)<<7);
	
	P1 = ((LED_P1 & 0xfe)>>1) + ((LED_P3 & 0x01)<<7);
	
	P3 = ((LED_P3 & 0xfe)>>1) + ((LED_P2 & 0x01)<<7);
	
	P2 = ((LED_P2 & 0xfe)>>1) + ((LED_P0 & 0x01)<<7);
	
	Delayms(time);
}

//状态0 所有LED闪烁3次
void disp0()			
{
	for(i=0;i<3;i++)
	{
		LED_P0=0x00; LED_P2=0x00; LED_P3=0x00; LED_P1=0x00;
		Display(300);
		LED_P0=0xff; LED_P2=0xff; LED_P3=0xff; LED_P1=0xff;
		Display(300);
	}
}

//状态1 LED顺时针转一圈
void disp1()			
{
	for(i=0;i<8;i++)
	{
		LED_P2=table1[i];
		Display(100);
	}
	LED_P2=0xff;
	for(i=0;i<8;i++)
	{
		LED_P3=table1[i];
		Display(100);
	}
	LED_P3=0xff;
	for(i=0;i<8;i++)
	{
		LED_P1=table1[i];        
		Display(100);
	}
	LED_P1=0xff;
	for(i=0;i<8;i++)
	{
		LED_P0=table1[i];
		Display(100);
	}
	LED_P0=0xff;
}

//状态2 LED逆时针转一圈
void disp2()			
{
	for(i=0;i<8;i++)
	{
		LED_P0=table0[i];
		Display(100);
	}
	LED_P0=0xff;
	for(i=0;i<8;i++)
	{
		LED_P1=table0[i];
		Display(100);
	}
	LED_P1=0xff;
	for(i=0;i<8;i++)
	{
		LED_P3=table0[i];
		Display(100);
	}
	LED_P3=0xff;
	for(i=0;i<8;i++)
	{
		LED_P2=table0[i];
		Display(100);
	}
	LED_P2=0xff;
}

//状态3 4个LED同时顺时、逆时针移动1/4圈
void disp3()			
{
	for(i=0;i<8;i++)
	{
		LED_P0=table0[i];
		LED_P1=table1[i];
		LED_P2=table1[i];
		LED_P3=table0[i];
		Display(100);
	}
	for(i=0;i<8;i++)
	{
		LED_P0=table1[i];
		LED_P1=table0[i];
		LED_P2=table0[i];
		LED_P3=table1[i];
		Display(100);
	}
	LED_P3=0xff; LED_P0=0xff; 
}

//状态4  2个LED同时顺时针移动半圈
void disp4()			
{
	for(i=0;i<8;i++)
	{
		LED_P2=table1[i];
		LED_P1=table1[i];
		Display(100);
	}
	LED_P2=0xff; LED_P1=0xff;
	for(i=0;i<8;i++)
	{
		LED_P3=table1[i];
		LED_P0=table1[i];
		Display(100);
	}
	LED_P3=0xff; LED_P0=0xff;
}

//状态5  2个LED同时逆时针移动半圈
void disp5()			
{
	for(i=0;i<8;i++)
	{
		LED_P0=table0[i];
		LED_P3=table0[i];
		Display(100);
	}
	LED_P0=0xff; LED_P3=0xff;
	for(i=0;i<8;i++)
	{
		LED_P1=table0[i];
		LED_P2=table0[i];
		Display(100);
	}
	LED_P1=0xff; LED_P2=0xff;
}

//状态6 LED自上而下逐渐点亮(一半点亮一半不亮)
void disp6()			
{
	for(i=0;i<8;i++)
	{
		LED_P0=table2[i];
		LED_P2=table3[i];
		Display(100);
	}
	LED_P0=0xff; LED_P2=0xff;
	for(i=0;i<8;i++)
	{
		LED_P1=table2[i];
		LED_P3=table3[i];
		Display(100);
	}
	LED_P1=0xff; LED_P3=0xff;
}

//状态7 LED自下而上逐渐点亮(直到全部点亮)
void disp7()			
{
	for(i=0;i<8;i++)
	{
		LED_P1=table3[i];
		LED_P3=table2[i];
		Display(100);
	}
	for(i=0;i<8;i++)
	{
		LED_P0=table2[i];
		LED_P2=table2[i];
		Display(100);
	}
}

//状态8 间断8格的4个LED亮并逆时针旋转
void disp8()			
{
	for(j=0;j<2;j++)
	{
		for(i=0;i<8;i++)
		{
			LED_P0=table0[i];
			LED_P2=table0[i];
			LED_P1=table0[i];
			LED_P3=table0[i];
			Display(100);
		}
		LED_P0=0xff; LED_P2=0xff; LED_P1=0xff; LED_P3=0xff;
		for(i=0;i<8;i++)
		{
			LED_P0=table0[i];
			LED_P2=table0[i];
			LED_P1=table0[i];
			LED_P3=table0[i];
			Display(100);
		}
		LED_P0=0xff; LED_P2=0xff; LED_P1=0xff; LED_P3=0xff;
	}
}

//状态9 间断8格的4个LED亮，然后逆时针逐渐点亮(直到全部点亮)
void disp9()			
{
	for(i=0;i<8;i++)
	{
		LED_P0=table2[i];
		LED_P2=table2[i];
		LED_P1=table2[i];
		LED_P3=table2[i];
		Display(100);
	}
	Display(500);	
}

//状态10 从LED全部亮到全不亮(间断8格的4个LED开始逆时针熄灭)
void disp10()			
{
	for(i=0;i<9;i++)
	{
		LED_P0=table4[i];
		LED_P2=table4[i];
		LED_P1=table4[i];
		LED_P3=table4[i];
		Display(100);
	}
	Display(300);
}

//状态11 间断8格的4个LED亮并顺时针旋转
void disp11()			
{
	for(j=0;j<2;j++)
	{
		for(i=0;i<8;i++)
		{
			LED_P0=table1[i];
			LED_P2=table1[i];
			LED_P1=table1[i];
			LED_P3=table1[i];
			Display(100);
		}
		LED_P0=0xff; LED_P2=0xff; LED_P1=0xff; LED_P3=0xff;
		for(i=0;i<8;i++)
		{
			LED_P0=table1[i];
			LED_P2=table1[i];
			LED_P1=table1[i];
			LED_P3=table1[i];
			Display(100);
		}
		LED_P0=0xff; LED_P2=0xff; LED_P1=0xff; LED_P3=0xff;
	}
}

//间断8格的4个LED亮，然后顺时针逐渐点亮(直到全部点亮)
void disp12()			
{
	for(i=0;i<8;i++)
	{
		LED_P0=table3[i];
		LED_P2=table3[i];
		LED_P1=table3[i];
		LED_P3=table3[i];
		Display(100);
	}
	Display(1000);
}

//状态13 从LED全部亮到全不亮(间断8格的4个LED开始顺时针熄灭)
void disp13()			
{
	for(i=0;i<9;i++)
	{
		LED_P0=table5[i];
		LED_P2=table5[i];
		LED_P1=table5[i];
		LED_P3=table5[i];
		Display(100);
	}
	Display(300);
}

//状态14 从LED不亮到全亮(从P0.0、P1.0、P2.0、P3.7开始逐步点亮)
void disp14()			
{
	for(i=0;i<8;i++)
	{
		LED_P0=table3[i];
		LED_P1=table2[i];
		LED_P2=table2[i];
		LED_P3=table3[i];
		Display(100);
	}
}

//状态15 从LED全亮到全不亮(从P0.7、P1.7、P2.7、P3.0开始逐步熄灭
void disp15()			
{
	for(i=0;i<9;i++)
	{
		LED_P0=table4[i];
		LED_P1=table5[i];
		LED_P2=table5[i];
		LED_P3=table4[i];
		Display(100);
	}
	Display(300);
}

//状态16 LED灯交替闪烁(频率有慢变快)
void disp16()			
{
	for(i=0;i<5;i++)
	{
		LED_P0=0xaa; LED_P1=0xaa; LED_P2=0xaa; LED_P3=0xaa;
		Display(100);
		LED_P0=~LED_P0; LED_P1=~LED_P1; LED_P2=~LED_P2; LED_P3=~LED_P3;
		Display(100);
	}
	for(i=0;i<5;i++)
	{
		LED_P0=0xaa; LED_P1=0xaa; LED_P2=0xaa; LED_P3=0xaa;
		Display(200);
		LED_P0=~LED_P0; LED_P1=~LED_P1; LED_P2=~LED_P2; LED_P3=~LED_P3;
		Display(200);
	}
	for(i=0;i<5;i++)
	{
		LED_P0=0xaa; LED_P1=0xaa; LED_P2=0xaa; LED_P3=0xaa;
		Display(300);
		LED_P0=~LED_P0; LED_P1=~LED_P1; LED_P2=~LED_P2; LED_P3=~LED_P3;
		Display(300);
	}
	LED_P0=0xff; LED_P2=0xff; LED_P1=0xff; LED_P3=0xff;
	Display(300);
}

//状态17 LED从P0.7开始逆时针逐步点亮,(循环2次)并且速度会逐步提高
void disp17()			
{

	for(i=0;i<8;i++)
	{
		LED_P0=table2[i];
		Display(100);
	}
	for(i=0;i<8;i++)
	{
		LED_P1=table2[i];
		Display(100);
	}	
	for(i=0;i<8;i++)
	{
		LED_P3=table2[i];
		Display(100);
	}	
	for(i=0;i<8;i++)
	{
		LED_P2=table2[i];
		Display(100);
	}
	LED_P0=0xff; LED_P1=0xff; LED_P3=0xff; LED_P2=0xff;
/*******************************/
	for(i=0;i<8;i++)
	{
		LED_P0=table2[i];
		Display(50);
	}
	for(i=0;i<8;i++)
	{
		LED_P1=table2[i];
		Display(50);
	}	
	for(i=0;i<8;i++)
	{
		LED_P3=table2[i];
		Display(50);
	}	
	for(i=0;i<8;i++)
	{
		LED_P2=table2[i];
		Display(50);
	}
	LED_P0=0xff; LED_P1=0xff; LED_P3=0xff; LED_P2=0xff;	
}

//状态18 LED从P0.7开始逆时针逐步点亮(每亮8位后就熄灭)
void disp18()			
{
	for(i=0;i<8;i++)
	{
		LED_P0=table2[i];
		Display(100);
	}
	LED_P0=0xff;
	for(i=0;i<8;i++)
	{
		LED_P1=table2[i];
		Display(100);
	}	
	LED_P1=0xff;
	for(i=0;i<8;i++)
	{
		LED_P3=table2[i];
		Display(100);
	}
	LED_P3=0xff;	
	for(i=0;i<8;i++)
	{
		LED_P2=table2[i];
		Display(100);
	}
	LED_P2=0xff;	
}

//状态19 LED从P2.7开始顺时针逐步点亮,(循环2次)并且速度会逐步提高
void disp19()			
{
	for(i=0;i<8;i++)
	{
		LED_P2=table3[i];
		Display(100);
	}
	for(i=0;i<8;i++)
	{
		LED_P3=table3[i];
		Display(100);
	}	
	for(i=0;i<8;i++)
	{
		LED_P1=table3[i];
		Display(100);
	}	
	for(i=0;i<8;i++)
	{
		LED_P0=table3[i];
		Display(100);
	}
	LED_P0=0xff; LED_P1=0xff; LED_P3=0xff; LED_P2=0xff;
/*******************************/
	for(i=0;i<8;i++)
	{
		LED_P2=table3[i];
		Display(50);
	}
	for(i=0;i<8;i++)
	{
		LED_P3=table3[i];
		Display(50);
	}	
	for(i=0;i<8;i++)
	{
		LED_P1=table3[i];
		Display(50);
	}	
	for(i=0;i<8;i++)
	{
		LED_P0=table3[i];
		Display(50);
	}
	LED_P0=0xff; LED_P1=0xff; LED_P3=0xff; LED_P2=0xff;	
}

//状态20 LED从P2.7开始顺时针逐步点亮(每亮8位后就熄灭)
void disp20()			
{
	for(i=0;i<8;i++)
	{
		LED_P2=table3[i];
		Display(100);
	}
	LED_P2=0xff;
	for(i=0;i<8;i++)
	{
		LED_P3=table3[i];
		Display(100);
	}	
	LED_P3=0xff;
	for(i=0;i<8;i++)
	{
		LED_P1=table3[i];
		Display(100);
	}
	LED_P1=0xff;	
	for(i=0;i<8;i++)
	{
		LED_P0=table3[i];
		Display(100);
	}
	LED_P0=0xff;		
}

//状态21 2个LED开始上下移动半圈
void disp21()			
{
	for(i=0;i<8;i++)
	{
		LED_P0=table0[i];
		LED_P2=table1[i];
		Display(100);
	}
	LED_P0=0xff; LED_P2=0xff;
	for(i=0;i<8;i++)
	{
		LED_P1=table0[i];
		LED_P3=table1[i];
		Display(100);
	}
	
	for(i=0;i<8;i++)
	{
		LED_P1=table1[i];
		LED_P3=table0[i];
		Display(100);
	}
	LED_P1=0xff; LED_P3=0xff;
	for(i=0;i<8;i++)
	{
		LED_P0=table1[i];
		LED_P2=table0[i];
		Display(100);
	}
}

//装态22 2个LED自上而下移动(循环5次,且频率渐快,到最快时持续循环16次,然后循环5次频率再逐渐降低)
void disp22()			
{	
	for(j=0;j<5;j++)
	{
		for(i=0;i<8;i++)
		{
			LED_P0=table0[i];
			LED_P2=table1[i];
			Display(tt);
		}
		LED_P0=0xff; LED_P2=0xff;
		for(i=0;i<8;i++)
		{
			LED_P1=table0[i];
			LED_P3=table1[i];
			Display(tt);
		}
		LED_P1=0xff; LED_P3=0xff;
		tt=tt-10;
	}

	for(j=0;j<16;j++)
	{
		for(i=0;i<8;i++)
		{
			LED_P0=table0[i];
			LED_P2=table1[i];
			Display(20);
		}
		LED_P0=0xff; LED_P2=0xff;
		for(i=0;i<8;i++)
		{
			LED_P1=table0[i];
			LED_P3=table1[i];
			Display(20);
		}
		LED_P1=0xff; LED_P3=0xff;
	}
	tt=20;
	for(j=0;j<5;j++)
	{
		for(i=0;i<8;i++)
		{
			LED_P0=table0[i];
			LED_P2=table1[i];
			Display(tt);
		}
		LED_P0=0xff; LED_P2=0xff;
		for(i=0;i<8;i++)
		{
			LED_P1=table0[i];
			LED_P3=table1[i];
			Display(tt);
		}
		LED_P1=0xff; LED_P3=0xff;
		tt=tt+10;
	}
	tt=70;	
		
}

//状态23 LED上下交替闪烁
void disp23()			
{

	for(i=0;i<2;i++)
	{
		LED_P0=0x00; LED_P2=0x00;
		Display(1000);
		LED_P0=0xff; LED_P2=0xff;
		LED_P1=0x00; LED_P3=0x00;
		Display(1000);
		LED_P1=0xff; LED_P3=0xff;
	}
}

//状态24 LED左右交替闪烁
void disp24()			
{	
	LED_P1=0xff; LED_P3=0xff; LED_P0=0xff; LED_P2=0xff;
	for(i=0;i<2;i++)
	{
		LED_P0=0x00; LED_P1=0x00;
		Display(1000);
		LED_P0=0xff; LED_P1=0xff;
		LED_P2=0x00; LED_P3=0x00; 
		Display(1000);
		LED_P2=0xff; LED_P3=0xff;
	}
}

//状态25 LED交替闪烁
void disp25()			
{
	for(i=0;i<5;i++)
	{
		LED_P0=0xaa; LED_P1=0xaa; LED_P2=0xaa; LED_P3=0xaa;
		Display(1000);
		LED_P0=~LED_P0; LED_P1=~LED_P1; LED_P2=~LED_P2; LED_P3=~LED_P3;
		Display(1000);		
	}
}

//状态26 2个LED开始上下移动半圈(LED不亮流水)
void disp26()			
{
	LED_P0=0x00;LED_P1=0x00;LED_P2=0x00;LED_P3=0x00;
	for(i=0;i<8;i++)
	{
		LED_P0=~table0[i];
		LED_P2=~table1[i];
		Display(200);
	}
	LED_P0=0x00; LED_P2=0x00;
	for(i=0;i<8;i++)
	{
		LED_P1=~table0[i];
		LED_P3=~table1[i];
		Display(200);
	}
	
	for(i=0;i<8;i++)
	{
		LED_P1=~table1[i];
		LED_P3=~table0[i];
		Display(200);
	}
	LED_P1=0x00; LED_P3=0x00;
	for(i=0;i<8;i++)
	{
		LED_P0=~table1[i];
		LED_P2=~table0[i];
		Display(200);
	}
}

//状态27 逐步顺时针点亮P2、P1的LED,熄灭后，再顺时针点亮P0、P3的LED
void disp27()			
{
	LED_P0=0xff; LED_P1=0xff; LED_P2=0xff; LED_P3=0xff;
	for(j=0;j<2;j++)
	{
		for(i=0;i<8;i++)
		{
			LED_P2=table3[i];
			LED_P1=table3[i];
			Display(100);
		}
		LED_P2=0xff; LED_P1=0xff;
		for(i=0;i<8;i++)
		{
			LED_P0=table3[i];
			LED_P3=table3[i];
			Display(100);
		}
		LED_P0=0xff; LED_P3=0xff;
	}
}
		
//状态28 P1、P2和P0、P3交替闪烁		
void disp28()			
{	
	for(i=0;i<2;i++)
	{
		LED_P1=0x00; LED_P2=0x00; LED_P0=0xff; LED_P3=0xff; 
		Display(1000);
		LED_P1=0xff; LED_P2=0xff; LED_P0=0x00; LED_P3=0x00; 
		Display(1000);
	}
	LED_P1=0xff; LED_P2=0xff; LED_P0=0xff; LED_P3=0xff; 
}

//状态29 逐步顺时针点亮P2、P1的LED,再顺时熄灭后，再顺时针点亮P0、P3的LED,再顺时熄灭
void disp29()			
{	

	LED_P0=0xff; LED_P1=0xff; LED_P2=0xff; LED_P3=0xff;
	for(j=0;j<2;j++)
	{
		for(i=0;i<8;i++)
		{
			LED_P2=table3[i];
			LED_P1=table3[i];
			Display(100);
		}
		for(i=0;i<9;i++)
		{
			LED_P2=table5[i];
			LED_P1=table5[i];
			Display(100);
		}
		for(i=0;i<8;i++)
		{
			LED_P0=table3[i];
			LED_P3=table3[i];
			Display(100);
		}
		for(i=0;i<9;i++)
		{
			LED_P0=table5[i];
			LED_P3=table5[i];
			Display(100);
		}
	}
	Display(200);	
}

//状态30 逐步逆时针点亮P2、P1的LED,熄灭后，再逆时针点亮P0、P3的LED
void disp30()		
{
	LED_P0=0xff; LED_P1=0xff; LED_P2=0xff; LED_P3=0xff;
	for(j=0;j<2;j++)
	{
		for(i=0;i<8;i++)
		{
			LED_P2=table2[i];
			LED_P1=table2[i];
			Display(100);
		}
		LED_P2=0xff; LED_P1=0xff;
		for(i=0;i<8;i++)
		{
			LED_P0=table2[i];
			LED_P3=table2[i];
			Display(100);
		}
		LED_P0=0xff; LED_P3=0xff;
	}
}

//状态31 逐步逆时针点亮P2、P1的LED,再逆时熄灭后，再逆时针点亮P0、P3的LED,再逆时熄灭
void disp31()			
{
	LED_P0=0xff; LED_P1=0xff; LED_P2=0xff; LED_P3=0xff;
	for(j=0;j<2;j++)
	{
		for(i=0;i<8;i++)
		{
			LED_P2=table2[i];
			LED_P1=table2[i];
			Display(100);
		}
		for(i=0;i<9;i++)
		{
			LED_P2=table4[i];
			LED_P1=table4[i];
			Display(100);
		}
		for(i=0;i<8;i++)
		{
			LED_P0=table2[i];
			LED_P3=table2[i];
			Display(100);
		}
		for(i=0;i<9;i++)
		{
			LED_P0=table4[i];
			LED_P3=table4[i];
			Display(100);
		}
	}
	Display(200);	
}

//状态32 LED自上而下逐步点亮，然后从下往上逐步熄灭
void disp32()			
{
	for(i=0;i<8;i++)
	{
		LED_P0=table2[i];
		LED_P2=table3[i];
		Display(100);
	}
	for(i=0;i<8;i++)
	{
		LED_P1=table2[i];
		LED_P3=table3[i];
		Display(100);
	}
	for(i=0;i<9;i++)
	{
		LED_P1=table5[i];
		LED_P3=table4[i];
		Display(100);
	}
	for(i=0;i<9;i++)
	{
		LED_P0=table5[i];
		LED_P2=table4[i];
		Display(100);
	}
}

//状态33 LED从左往右开始点亮(直到全亮)，然后从左右两边开始熄灭(直到全部熄灭)
void disp33()			
{
	for(i=0;i<8;i++)
	{
		LED_P0=table3[i];
		LED_P1=table2[i];
		Display(100);
	}
	for(i=0;i<8;i++)
	{
		LED_P2=table3[i];
		LED_P3=table2[i];
		Display(100);
	}
	Display(500);
	for(i=0;i<9;i++)
	{
		LED_P2=table4[i];
		LED_P3=table5[i];
		LED_P1=table4[i];
		LED_P0=table5[i];
		Display(100);
	}
	Display(300);
}

//状态34 LED从左往右开始点亮(直到全亮)，然后从中间往左右边熄灭
void disp34()			
{
	for(i=0;i<8;i++)
	{
		LED_P2=table2[i];
		LED_P3=table3[i];
		Display(100);
	}
	for(i=0;i<8;i++)
	{
		LED_P0=table2[i];
		LED_P1=table3[i];
		Display(100);
	}
	Display(500);
	for(i=0;i<9;i++)
	{
		LED_P2=table5[i];
		LED_P3=table4[i];
		LED_P1=table5[i];
		LED_P0=table4[i];
		Display(100);
	}
	Display(300);	
}

//状态35  从P2.7、P1.7开始同时顺时针旋转，直到LED全亮
void disp35()			
{
	for(i=0;i<8;i++)
	{
		LED_P2=table3[i];
		LED_P1=table3[i];
		Display(100);
	}
	for(i=0;i<8;i++)
	{
		LED_P3=table3[i];
		LED_P0=table3[i];
		Display(100);
	}
}

//状态36  从P0.7、P3.1开始同时逆时针旋转，直到LED全亮
void disp36()			
{
	for(i=0;i<8;i++)
	{
		LED_P0=table2[i];
		LED_P3=table2[i];
		Display(100);
	}
	for(i=0;i<8;i++)
	{
		LED_P1=table2[i];
		LED_P2=table2[i];
		Display(100);
	}
}

//状态37 2个LED自上而下移动，并点亮最下2个LED，然后2个LED再自下而上回去，同时4个LED（上下各2个LED）再来回移动一次
void disp37()			
{
	for(i=0;i<8;i++)
	{
		LED_P0=table0[i];
		LED_P2=table1[i];
		Display(100);
	}
	LED_P0=0xff; LED_P2=0xff;
	for(i=0;i<8;i++)
	{
		LED_P1=table0[i];
		LED_P3=table1[i];
		Display(100);
	}
	
	for(i=0;i<8;i++)
	{
		LED_P1=table7[i];
		LED_P3=table6[i];
		Display(100);
	}
	LED_P1=0x7f; LED_P3=0xfe;
	for(i=0;i<8;i++)
	{
		LED_P0=table1[i];
		LED_P2=table0[i];
		Display(100);
	}
	
	for(i=0;i<8;i++)
	{
		LED_P0=table0[i];
		LED_P2=table1[i];
		LED_P1=table1[i];
		LED_P3=table0[i];
		Display(200);
	}
	
	for(i=0;i<8;i++)
	{
		LED_P0=table1[i];
		LED_P1=table0[i];
		LED_P2=table0[i];
		LED_P3=table1[i];
		Display(200);
	}	
	LED_P0=0xff;LED_P1=0xff; LED_P2=0xff;LED_P3=0xff;
}

//状态38 逐步顺时针点亮P2、P1的LED,熄灭后，再顺时针点亮P0、P3的LED
void disp38()			
{
	LED_P0=0xff; LED_P1=0xff; LED_P2=0xff; LED_P3=0xff;
	for(j=0;j<2;j++)
	{
		for(i=0;i<8;i++)
		{
			LED_P2=table3[i];
			LED_P1=table3[i];
			Display(100);
		}
		LED_P2=0xff; LED_P1=0xff;
		for(i=0;i<8;i++)
		{
			LED_P0=table3[i];
			LED_P3=table3[i];
			Display(100);
		}
		LED_P0=0xff; LED_P3=0xff;
	}	
}

//状态39 P1、P3LED(下半部分)一直亮,上半部分LED向外扩张亮,然后闪烁3次
void disp39()			
{
	LED_P1=0x00; LED_P3=0x00;
	for(i=0;i<8;i++)
	{
		LED_P0=table3[i];
		LED_P2=table3[i];
		Display(150);
	}
	for(i=0;i<8;i++)
	{
		LED_P0=table2[i];
		LED_P2=table3[i];
		Display(300);
	}
	for(i=0;i<4;i++)
	{
		LED_P0=~LED_P0; LED_P2=~LED_P2;
		Display(300);
	}
	Display(1000);
}

//状态40 LED从P3.0、P0.7开始逆时针同时熄灭，直到LED全部熄灭
void disp40()			
{
	for(i=0;i<9;i++)
	{
		LED_P3=table4[i];
		LED_P0=table4[i];
		Display(100);
	}
	for(i=1;i<9;i++)
	{
		LED_P2=table4[i];
		LED_P1=table4[i];
		Display(100);
	}
	Display(300);	
}

//状态41 LED从P2.7、P1.7开始顺时针同时熄灭，直到全部熄灭
void disp41()			
{
	for(i=0;i<9;i++)
	{
		LED_P2=table5[i];
		LED_P1=table5[i];
		Display(100);
	}
	for(i=1;i<9;i++)
	{
		LED_P0=table5[i];
		LED_P3=table5[i];
		Display(100);
	}
	Display(300);		
}

void DispStatus(unsigned char index)
{
	switch(index)
	{
		case 0	:disp0()	;	break;
		case 1	:disp1()	;	break;
		case 2	:disp2()	;	break;
		case 3	:disp3()	;	break;
		case 4	:disp4()	;	break;
		case 5	:disp5()	;	break;
		case 6	:disp6()	;	break;
		case 7	:disp7()	;	break;
		case 8	:disp8()	;	break;
		case 9	:disp9()	;	break;
		case 10	:disp10()	;	break;
		case 11	:disp11()	;	break;
		case 12	:disp12()	;	break;
		case 13	:disp13()	;	break;
		case 14	:disp14()	;	break;
		case 15	:disp15()	;	break;
		case 16	:disp16()	;	break;
		case 17	:disp17()	;	break;
		case 18	:disp18()	;	break;
		case 19	:disp19()	;	break;
		case 20	:disp20()	;	break;
		case 21	:disp21()	;	break;
		case 22	:disp22()	;	break;
		case 23	:disp23()	;	break;
		case 24	:disp24()	;	break;
		case 25	:disp25()	;	break;
		case 26	:disp26()	;	break;
		case 27	:disp27()	;	break;
		case 28	:disp28()	;	break;
		case 29	:disp29()	;	break;
		case 30	:disp30()	;	break;
		case 31	:disp31()	;	break;
		case 32	:disp32()	;	break;
		case 33	:disp33()	;	break;
		case 34	:disp34()	;	break;
		case 35	:disp35()	;	break;
		case 36	:disp36()	;	break;
		case 37	:disp37()	;	break;
		case 38	:disp38()	;	break;
		case 39	:disp39()	;	break;
		case 40	:disp40()	;	break;
		case 41	:disp41()	;	break;
		default: break;		
	}
}

void main()
{	
	int i;
	while(1)
	{
		//按照自定义场景循环播放
		for(i=0;i<SCENE_COUNT;i++)
		{
			DispStatus(scene[i]);
		}
	}
}
