#include "Function.h"

void LED_Task(void)
{
	switch(led)
	{
		case White://白色
			LED_B = 0;LED_G = 0;LED_R = 0;
		case Blue://蓝色
			LED_B = 0;LED_G = 1;LED_R = 1;
		case Red://红色
			LED_B = 1;LED_G = 1;LED_R = 0;
		case Green://绿色
			LED_B = 1;LED_G = 0;LED_R = 0;
		case Twinkle://闪烁
			LED_B = ~LED_B;LED_G = ~LED_G;LED_R = ~LED_R;
			CLK_SysTickDelay(50000);
			LED_B = ~LED_B;LED_G = ~LED_G;LED_R = ~LED_R;
		default:
			break;
	}
}
