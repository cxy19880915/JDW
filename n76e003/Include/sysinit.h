#ifndef	__SYSINIT_H
#define	__SYSINIT_H

#include <stdio.h>
#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "I2C_M.h"
//#include "Define.h"
#include "IR_recive.h"
#include	"adc.h"
#include	"timer0.h"
//#include	"time1.h"

void 	gpio_init(void);
//void	time0_init(void);
//void	adc_init(void);
void	sys_init(void);
void	SetSysClock(void);


#endif