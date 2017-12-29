#include "sysInit.h"

extern	UINT16	sys_flag;

void	SetSysClock(void)
{
	CKSWT = 0x30;
	CKEN  = 0x30;
//	CKDIV = 0x02;
	__delay_10ms(2);
}

void gpio_init(void)
{
	Set_All_GPIO_Quasi_Mode;
	#if 0
	P00_PushPull_Mode;
	P01_PushPull_Mode;
	P02_PushPull_Mode;
	P03_PushPull_Mode;
	P04_PushPull_Mode;
//	P04_Input_Mode;
	P05_Input_Mode;
	P06_Input_Mode;
	P07_PushPull_Mode;
	P10_PushPull_Mode;
	P11_PushPull_Mode;
	P12_PushPull_Mode;
	P13_PushPull_Mode;
	P14_PushPull_Mode;
	P15_PushPull_Mode;
	P17_Input_Mode;
	P30_PushPull_Mode;
	#endif
//	BAT_DET		

//	LOW_BAT_NOTIFY	= 0;
	P10_PushPull_Mode;
//	P11_PushPull_Mode;
	ST_BY = 0;
	BT_POWER = 0;
	sys_flag = sys_power_off;
	power_flag = 0;	
//	BT_POWER = 0;		
////	BT_DET			

////	GPIO1		
////	GPIO2		
////	GPIO3		

//	PLAY = 0;	
//	REV = 0;			
//	FWD = 0;			
//	VOL_UP = 0;		
//	VOL_DOWN = 0;	
//	PAIR = 0;		
}

void	sys_init(void)
{
//	sys_flag = 0x00;
//	unsigned char	*p8Data = g_abMax1xDSPCommands;
	SetSysClock();
	gpio_init();
	timer0_init();
//	timer1_init();
	adc_init();
	IR_init();
	Init_I2C();
	set_EA;                                     //enable interrupts
	set_TR0;                                    //Timer0 run
//  set_TR2;                                    // Timer2 run	
}

//void	time0_init(void)
//{
//	TIMER0_MODE1_ENABLE;
//	u8TH0_Tmp = (65536-TH0_INIT)/256;
//    u8TL0_Tmp = (65536-TL0_INIT)%256;
//	TH0 = u8TH0_Tmp;
//    TL0 = u8TL0_Tmp;
//	set_ET0;
//}

//void	adc_init(void)
//{
//	Enable_ADC_AIN0;
//}

