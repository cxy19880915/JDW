/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2017 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Jan/21/2017
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: N76E003 GPIO demo code
//***********************************************************************************************************
//#include "N76E003.h"
//#include "SFR_Macro.h"
//#include "Function_define.h"
//#include "Common.h"
//#include "Delay.h"
#include "sysinit.h"
#include "task_deal.h"

extern const unsigned char code g_abMax1xDSPCommands[];
extern const unsigned char code g_abMax2xDSPCommands[];
extern const unsigned char code g_abMax3xDSPCommands[];
extern	void Bluetooth_Test_Task(void);
extern	void	KEY_EVENT(void);
extern	void	SYS_SOURCE(void);
extern	void	SYS_VOL_A(void);
extern	void	SYS_VOL_B(void);
extern	void	SYS_MODE(void);
extern	void	KEY_SCAN(void);

extern unsigned char BT_connect;
extern UINT8 Dat_count,nm;

//*****************  The Following is in define in Fucntion_define.h  ***************************
//****** Always include Function_define.h call the define you want, detail see main(void) *******
//***********************************************************************************************
#if 0
////------------------- Define Port as Quasi mode  -------------------
//#define P00_Quasi_Mode				P0M1&=~SET_BIT0;P0M2&=~SET_BIT0
//#define P01_Quasi_Mode				P0M1&=~SET_BIT1;P0M2&=~SET_BIT1
//#define P02_Quasi_Mode				P0M1&=~SET_BIT2;P0M2&=~SET_BIT2
//#define P03_Quasi_Mode				P0M1&=~SET_BIT3;P0M2&=~SET_BIT3
//#define P04_Quasi_Mode				P0M1&=~SET_BIT4;P0M2&=~SET_BIT4
//#define P05_Quasi_Mode				P0M1&=~SET_BIT5;P0M2&=~SET_BIT5
//#define P06_Quasi_Mode				P0M1&=~SET_BIT6;P0M2&=~SET_BIT6
//#define P07_Quasi_Mode				P0M1&=~SET_BIT7;P0M2&=~SET_BIT7
//#define P10_Quasi_Mode				P1M1&=~SET_BIT0;P1M2&=~SET_BIT0
//#define P11_Quasi_Mode				P1M1&=~SET_BIT1;P1M2&=~SET_BIT1
//#define P12_Quasi_Mode				P1M1&=~SET_BIT2;P1M2&=~SET_BIT2
//#define P13_Quasi_Mode				P1M1&=~SET_BIT3;P1M2&=~SET_BIT3
//#define P14_Quasi_Mode				P1M1&=~SET_BIT4;P1M2&=~SET_BIT4
//#define P15_Quasi_Mode				P1M1&=~SET_BIT5;P1M2&=~SET_BIT5
//#define P16_Quasi_Mode				P1M1&=~SET_BIT6;P1M2&=~SET_BIT6
//#define P17_Quasi_Mode				P1M1&=~SET_BIT7;P1M2&=~SET_BIT7
//#define P20_Quasi_Mode				P2M1&=~SET_BIT0;P2M2&=~SET_BIT0
//#define P30_Quasi_Mode				P3M1&=~SET_BIT0;P3M2&=~SET_BIT0
////------------------- Define Port as Push Pull mode -------------------
//#define P00_PushPull_Mode			P0M1|=SET_BIT0;P0M2&=~SET_BIT0
//#define P01_PushPull_Mode			P0M1|=SET_BIT1;P0M2&=~SET_BIT1
//#define P02_PushPull_Mode			P0M1&=~SET_BIT2;P0M2|=SET_BIT2
//#define P03_PushPull_Mode			P0M1&=~SET_BIT3;P0M2|=SET_BIT3
//#define P04_PushPull_Mode			P0M1&=~SET_BIT4;P0M2|=SET_BIT4
//#define P05_PushPull_Mode			P0M1&=~SET_BIT5;P0M2|=SET_BIT5
//#define P06_PushPull_Mode			P0M1&=~SET_BIT6;P0M2|=SET_BIT6
//#define P07_PushPull_Mode			P0M1&=~SET_BIT7;P0M2|=SET_BIT7
//#define P10_PushPull_Mode			P1M1&=~SET_BIT0;P1M2|=SET_BIT0
//#define P11_PushPull_Mode			P1M1&=~SET_BIT1;P1M2|=SET_BIT1
//#define P12_PushPull_Mode			P1M1&=~SET_BIT2;P1M2|=SET_BIT2
//#define P13_PushPull_Mode			P1M1&=~SET_BIT3;P1M2|=SET_BIT3
//#define P14_PushPull_Mode			P1M1&=~SET_BIT4;P1M2|=SET_BIT4
//#define P15_PushPull_Mode			P1M1&=~SET_BIT5;P1M2|=SET_BIT5
//#define P16_PushPull_Mode			P1M1&=~SET_BIT6;P1M2|=SET_BIT6
//#define P17_PushPull_Mode			P1M1&=~SET_BIT7;P1M2|=SET_BIT7
//#define P20_PushPull_Mode			P2M1&=~SET_BIT0;P2M2|=SET_BIT0
//#define P30_PushPull_Mode			P3M1&=~SET_BIT0;P3M2|=SET_BIT0
////------------------- Define Port as Input Only mode -------------------
//#define P00_Input_Mode				P0M1|=SET_BIT0;P0M2&=~SET_BIT0
//#define P01_Input_Mode				P0M1|=SET_BIT1;P0M2&=~SET_BIT1
//#define P02_Input_Mode				P0M1|=SET_BIT2;P0M2&=~SET_BIT2
//#define P03_Input_Mode				P0M1|=SET_BIT3;P0M2&=~SET_BIT3
//#define P04_Input_Mode				P0M1|=SET_BIT4;P0M2&=~SET_BIT4
//#define P05_Input_Mode				P0M1|=SET_BIT5;P0M2&=~SET_BIT5
//#define P06_Input_Mode				P0M1|=SET_BIT6;P0M2&=~SET_BIT6
//#define P07_Input_Mode				P0M1|=SET_BIT7;P0M2&=~SET_BIT7
//#define P10_Input_Mode				P1M1|=SET_BIT0;P1M2&=~SET_BIT0
//#define P11_Input_Mode				P1M1|=SET_BIT1;P1M2&=~SET_BIT1
//#define P12_Input_Mode				P1M1|=SET_BIT2;P1M2&=~SET_BIT2
//#define P13_Input_Mode				P1M1|=SET_BIT3;P1M2&=~SET_BIT3
//#define P14_Input_Mode				P1M1|=SET_BIT4;P1M2&=~SET_BIT4
//#define P15_Input_Mode				P1M1|=SET_BIT5;P1M2&=~SET_BIT5
//#define P16_Input_Mode				P1M1|=SET_BIT6;P1M2&=~SET_BIT6
//#define P17_Input_Mode				P1M1|=SET_BIT7;P1M2&=~SET_BIT7
//#define P20_Input_Mode				P2M1|=SET_BIT0;P2M2&=~SET_BIT0
//#define P30_Input_Mode				P3M1|=SET_BIT0;P3M2&=~SET_BIT0
////-------------------Define Port as Open Drain mode -------------------
//#define P00_OpenDrain_Mode		P0M1|=SET_BIT0;P0M2|=SET_BIT0
//#define P01_OpenDrain_Mode		P0M1|=SET_BIT1;P0M2|=SET_BIT1
//#define P02_OpenDrain_Mode		P0M1|=SET_BIT2;P0M2|=SET_BIT2
//#define P03_OpenDrain_Mode		P0M1|=SET_BIT3;P0M2|=SET_BIT3
//#define P04_OpenDrain_Mode		P0M1|=SET_BIT4;P0M2|=SET_BIT4
//#define P05_OpenDrain_Mode		P0M1|=SET_BIT5;P0M2|=SET_BIT5
//#define P06_OpenDrain_Mode		P0M1|=SET_BIT6;P0M2|=SET_BIT6
//#define P07_OpenDrain_Mode		P0M1|=SET_BIT7;P0M2|=SET_BIT7
//#define P10_OpenDrain_Mode		P1M1|=SET_BIT0;P1M2|=SET_BIT0
//#define P11_OpenDrain_Mode		P1M1|=SET_BIT1;P1M2|=SET_BIT1
//#define P12_OpenDrain_Mode		P1M1|=SET_BIT2;P1M2|=SET_BIT2
//#define P13_OpenDrain_Mode		P1M1|=SET_BIT3;P1M2|=SET_BIT3
//#define P14_OpenDrain_Mode		P1M1|=SET_BIT4;P1M2|=SET_BIT4
//#define P15_OpenDrain_Mode		P1M1|=SET_BIT5;P1M2|=SET_BIT5
//#define P16_OpenDrain_Mode		P1M1|=SET_BIT6;P1M2|=SET_BIT6
//#define P17_OpenDrain_Mode		P1M1|=SET_BIT7;P1M2|=SET_BIT7
//#define P20_OpenDrain_Mode		P2M1|=SET_BIT0;P2M2|=SET_BIT0
//#define P30_OpenDrain_Mode		P3M1|=SET_BIT0;P3M2|=SET_BIT0
////--------- Define all port as quasi mode ---------
//#define Set_All_GPIO_Quasi_Mode			P0M1=0;P0M1=0;P1M1=0;P1M2=0;P2M1=0;P2M2=0;P3M1=0;P3M2=0
#endif

/*------------------------------------------------
The main C function.  Program execution starts
here after stack initialization.
------------------------------------------------*/
extern	UINT8 ir_status;
void main (void) 
#if 1
{
	UINT8 step = 0,n=0;
	sys_init();
	while(1)
	{
		switch(step)
		{
			case 0:
			{
				POWER_ON_OFF();
				step = 1;
				break;
			}
			case 1:
			{
				SYS_MODE();
				step = 2;
				break;
			}
			case 2:
			{
				SYS_SOURCE();
				step = 3;
				break;
			}
			case 3:
			{
				SYS_VOL_A();
				step = 4;
				break;
			}
			case 4:
			{
				SYS_VOL_B();
				step = 5;
				break;
			}
			case 5:
			{
				IR_Deal();
				step = 6;
				break;
			}
			case	6:
			{
				KEY_SCAN();
				step = 7;
				break;
			}
			case 7:
			{
				KEY_EVENT();
				step = 8;
				break;
			}
			case 8:
			{
				LED_DISPLAY();
				step = 0;
				break;
			}
//			case 8:
//			{
//				Bluetooth_Test_Task();	
//				step = 0;			
//				break;
//			}
			default:
				step = 0;
		}
		
	}
}
#endif
#if 0
{
//	unsigned char temp;
	Set_All_GPIO_Quasi_Mode;					// Define in Function_define.h
	
#if 0
	InitialUART0_Timer3(115200);
//	set_CLOEN;  										// For clock out from P1.1
  
  while(1)
  {
		clr_GPIO1;											// Tiny board GPIO1 LED define
		P0 = 0x00;
		P2 = 0x00;
		P1 = 0x00;
		Timer0_Delay1ms(30);
		P0 = 0xff;
		P2 = 0xff;
		P1 = 0xff;
		set_GPIO1;	

		Send_Data_To_UART0(0x35);					//UART0 send ascii "U"
		temp = 0x31 + P0;
		Send_Data_To_UART0(temp);
		temp = 0x31 + P1;
		Send_Data_To_UART0(temp);

		Timer0_Delay1ms(30);
  }
#endif

#if 1
  
  while(1)
  {
		clr_GPIO1;											// Tiny board GPIO1 LED define
		P0 = 0x00;
		P2 = 0x00;
		P1 = 0x00;
		Timer0_Delay1ms(30);
		P0 = 0xff;
		P2 = 0xff;
		P1 = 0xff;
		set_GPIO1;	
		Timer0_Delay1ms(30);
  }
#endif
	

}
#endif



