#define Bluetooth_GLOBALS
#include "Bluetooth.h"


void Bluetooth_Test_Task(void)
{
			LED_B = ~LED_B;//LED_G = ~LED_G;LED_R = ~LED_R;
			CLK_SysTickDelay(250000);
			LED_B = ~LED_B;//LED_G = ~LED_G;LED_R = ~LED_R;
			CLK_SysTickDelay(250000);
}

void BT_patch(void)
{
		BT_REV = 1;	BT_FWD = 1;
		CLK_SysTickDelay(600000);
		BT_REV = 0;	BT_FWD = 0;
		BT_connect = 0;
}
void BT_Play_Pause(void)
{
		BT_REV = 1;	BT_FWD = 1;
		CLK_SysTickDelay(300000);
		BT_REV = 0;	BT_FWD = 0;
}
void BT_REV_TASK(void)
{
		BT_REV = 1;
		CLK_SysTickDelay(300000);
		BT_REV = 0;
}
void BT_FWD_TASK(void)
{
		BT_FWD = 1;
		CLK_SysTickDelay(300000);
		BT_FWD = 0;
}


