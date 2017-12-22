#ifndef	__TASK_DEAL_H
#define	__TASK_DEAL_H

#include	"config.h"


#ifdef	task_GLOBALS
	#define	task_ext
#else
	#define	task_ext	extern
#endif
	

task_ext	bit	power_change;
task_ext	bit	power_flag;
task_ext	UINT8	KEY_data;
	
	void	POWER_ON_OFF(void);	
	void	IR_EVENT(void);
	void  GPIO_MUTE(void);
	void	LED_DISPLAY(void);
	
#endif
