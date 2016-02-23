/******************************************************************************************
*˵������32��LED�ֳ�4��LED_P0,LED_P1,LED_P3,LED_P2,ÿһ�����8��LED�ƣ�Ҳ���ǽ����ηֳ�4�����֣�
*      ����ͼ��ʾ������������ֻ�������Щֵ��Ȼ����Щֵ��Ӧ����Ӧ��IO���ϾͿ�����
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

#define FOSC 12000000L //�������ã�ʹ��11.0592M Hz 6T˫�ٱ�ģʽ

volatile uchar LED_P0 = 0xff;
volatile uchar LED_P1 = 0xff;
volatile uchar LED_P2 = 0xff;
volatile uchar LED_P3 = 0xff;

#define SCENE_COUNT 20//����ѭ�����ŷ�������

//���Զ��峡����������˳�򲥷Ŷ���״̬
uchar scene[SCENE_COUNT] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};

uchar code table0[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//LED�ӵ�λ����λ��
uchar code table1[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};//LED�Ӹ�λ����λ��
uchar code table2[]={0xfe,0xfc,0xf8,0xf0,0xe0,0xc0,0x80,0x00};//LED��1������8��������(�ӵ�λ����λ)
uchar code table3[]={0x7f,0x3f,0x1f,0x0f,0x07,0x03,0x01,0x00};//LED��1������8��������(�Ӹ�λ����λ)
uchar code table4[]={0x00,0x01,0x03,0x07,0x0f,0x1f,0x3f,0x7f,0xff};//LED��8��ȫ����һ��������(�ӵ�λ����λ)
uchar code table5[]={0x00,0x80,0xc0,0xe0,0xf0,0xf8,0xfc,0xfe,0xff};//LED��8��ȫ����һ��������(�Ӹ�λ����λ)
uchar code table6[]={0xfe,0xfc,0xfa,0xf6,0xee,0xde,0xbe,0x7e};//LED�ӵ�λ����λ��(���λʼ��Ϊ0)
uchar code table7[]={0x7f,0x3f,0x5f,0x6f,0x77,0x7b,0x7d,0x7e};//LED�Ӹ�λ����λ��(���λʼ��Ϊ0)
uchar i,j;		//����ѭ������
uint tt=70;		//����ʱ��ָ��
	
//��ʱ����
void Delayms(uint ms)
{
	uint x,y;
	for(x=ms;x>0;x--)
	for(y=125;y>0;y--);
}

//��LED_P0,LED_P1,LED_P3,LED_P2��ֵ�Ķ�Ӧ������IO���ϣ�����ʱ
void Display(uint time)	
{
	P0 = ((LED_P0 & 0xfe)>>1) + ((LED_P1 & 0x01)<<7);
	
	P1 = ((LED_P1 & 0xfe)>>1) + ((LED_P3 & 0x01)<<7);
	
	P3 = ((LED_P3 & 0xfe)>>1) + ((LED_P2 & 0x01)<<7);
	
	P2 = ((LED_P2 & 0xfe)>>1) + ((LED_P0 & 0x01)<<7);
	
	Delayms(time);
}

//״̬0 ����LED��˸3��
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

//״̬1 LED˳ʱ��תһȦ
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

//״̬2 LED��ʱ��תһȦ
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

//״̬3 4��LEDͬʱ˳ʱ����ʱ���ƶ�1/4Ȧ
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

//״̬4  2��LEDͬʱ˳ʱ���ƶ���Ȧ
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

//״̬5  2��LEDͬʱ��ʱ���ƶ���Ȧ
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

//״̬6 LED���϶����𽥵���(һ�����һ�벻��)
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

//״̬7 LED���¶����𽥵���(ֱ��ȫ������)
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

//״̬8 ���8���4��LED������ʱ����ת
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

//״̬9 ���8���4��LED����Ȼ����ʱ���𽥵���(ֱ��ȫ������)
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

//״̬10 ��LEDȫ������ȫ����(���8���4��LED��ʼ��ʱ��Ϩ��)
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

//״̬11 ���8���4��LED����˳ʱ����ת
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

//���8���4��LED����Ȼ��˳ʱ���𽥵���(ֱ��ȫ������)
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

//״̬13 ��LEDȫ������ȫ����(���8���4��LED��ʼ˳ʱ��Ϩ��)
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

//״̬14 ��LED������ȫ��(��P0.0��P1.0��P2.0��P3.7��ʼ�𲽵���)
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

//״̬15 ��LEDȫ����ȫ����(��P0.7��P1.7��P2.7��P3.0��ʼ��Ϩ��
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

//״̬16 LED�ƽ�����˸(Ƶ���������)
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

//״̬17 LED��P0.7��ʼ��ʱ���𲽵���,(ѭ��2��)�����ٶȻ������
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

//״̬18 LED��P0.7��ʼ��ʱ���𲽵���(ÿ��8λ���Ϩ��)
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

//״̬19 LED��P2.7��ʼ˳ʱ���𲽵���,(ѭ��2��)�����ٶȻ������
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

//״̬20 LED��P2.7��ʼ˳ʱ���𲽵���(ÿ��8λ���Ϩ��)
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

//״̬21 2��LED��ʼ�����ƶ���Ȧ
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

//װ̬22 2��LED���϶����ƶ�(ѭ��5��,��Ƶ�ʽ���,�����ʱ����ѭ��16��,Ȼ��ѭ��5��Ƶ�����𽥽���)
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

//״̬23 LED���½�����˸
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

//״̬24 LED���ҽ�����˸
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

//״̬25 LED������˸
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

//״̬26 2��LED��ʼ�����ƶ���Ȧ(LED������ˮ)
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

//״̬27 ��˳ʱ�����P2��P1��LED,Ϩ�����˳ʱ�����P0��P3��LED
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
		
//״̬28 P1��P2��P0��P3������˸		
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

//״̬29 ��˳ʱ�����P2��P1��LED,��˳ʱϨ�����˳ʱ�����P0��P3��LED,��˳ʱϨ��
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

//״̬30 ����ʱ�����P2��P1��LED,Ϩ�������ʱ�����P0��P3��LED
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

//״̬31 ����ʱ�����P2��P1��LED,����ʱϨ�������ʱ�����P0��P3��LED,����ʱϨ��
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

//״̬32 LED���϶����𲽵�����Ȼ�����������Ϩ��
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

//״̬33 LED�������ҿ�ʼ����(ֱ��ȫ��)��Ȼ����������߿�ʼϨ��(ֱ��ȫ��Ϩ��)
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

//״̬34 LED�������ҿ�ʼ����(ֱ��ȫ��)��Ȼ����м������ұ�Ϩ��
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

//״̬35  ��P2.7��P1.7��ʼͬʱ˳ʱ����ת��ֱ��LEDȫ��
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

//״̬36  ��P0.7��P3.1��ʼͬʱ��ʱ����ת��ֱ��LEDȫ��
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

//״̬37 2��LED���϶����ƶ�������������2��LED��Ȼ��2��LED�����¶��ϻ�ȥ��ͬʱ4��LED�����¸�2��LED���������ƶ�һ��
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

//״̬38 ��˳ʱ�����P2��P1��LED,Ϩ�����˳ʱ�����P0��P3��LED
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

//״̬39 P1��P3LED(�°벿��)һֱ��,�ϰ벿��LED����������,Ȼ����˸3��
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

//״̬40 LED��P3.0��P0.7��ʼ��ʱ��ͬʱϨ��ֱ��LEDȫ��Ϩ��
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

//״̬41 LED��P2.7��P1.7��ʼ˳ʱ��ͬʱϨ��ֱ��ȫ��Ϩ��
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
		//�����Զ��峡��ѭ������
		for(i=0;i<SCENE_COUNT;i++)
		{
			DispStatus(scene[i]);
		}
	}
}
