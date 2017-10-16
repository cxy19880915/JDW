#define USB_GLOBALS
#include "usb.h"

void	USB_Test_Task(void)
{
	USB_PLAY = 0;
}
void USB_PLAY_TASK(void)
{
	USB_PLAY = 1;
	CLK_SysTickDelay(250000);
	USB_PLAY = 0;
}
void USB_REV_TASK(void)
{
		BT_REV = 1;
		CLK_SysTickDelay(250000);
		BT_REV = 0;
}
void USB_FWD_TASK(void)
{
		BT_FWD = 1;
		CLK_SysTickDelay(250000);
		BT_FWD = 0;
}
