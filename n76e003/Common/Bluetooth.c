#define Bluetooth_GLOBALS
#include "Bluetooth.h"

extern	void __delay_10ms( UINT16 u16CNT );
extern	UINT8 VOL_LED;
extern	bit led_flag;
extern	UINT16	sys_flag;
extern	UINT8		KEY_VALUE;

void Bluetooth_Test_Task(void)
{
	if(BT_POWER)
	{
		switch(KEY_VALUE)
		{
			case	ir_play:
				BT_Play_Pause();
			break;
			
			case	ir_fwd:
				BT_FWD_TASK();
//				VOL_level--;
			break;
			
			case	ir_rev:
				BT_REV_TASK();
//				VOL_level--;
			break;
			
		}
	}
//	VOL_LED = 1;
//	led_flag = 1;
//	__delay_10ms(20);
//			LED_B = ~LED_B;//LED_G = ~LED_G;LED_R = ~LED_R;
//			__delay_10ms(25);
//			LED_B = ~LED_B;//LED_G = ~LED_G;LED_R = ~LED_R;
//			__delay_10ms(25);
}

void BT_patch(void)
{
		BT_REV = 1;	BT_FWD = 1;
		__delay_10ms(60);
		BT_REV = 0;	BT_FWD = 0;
		BT_connect = 0;
}
void BT_Play_Pause(void)
{
		BT_REV = 1;	BT_FWD = 1;
		__delay_10ms(25);
		BT_REV = 0;	BT_FWD = 0;
}
void BT_REV_TASK(void)
{
		BT_REV = 1;
		__delay_10ms(25);
		BT_REV = 0;
}
void BT_FWD_TASK(void)
{
		BT_FWD = 1;
		__delay_10ms(25);
		BT_FWD = 0;
}


