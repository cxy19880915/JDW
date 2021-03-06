#ifndef _USB_H_
#define	_USB_H_

#include "task.h"

#ifdef USB_GLOBALS
	#define USB_EXT 
#else
	#define USB_EXT extern
#endif
	
USB_EXT	unsigned char USB_SW_flag;
USB_EXT void USB_PLAY_TASK(void);
USB_EXT	void USB_FWD_TASK(void);
USB_EXT	void USB_REV_TASK(void);

#endif
