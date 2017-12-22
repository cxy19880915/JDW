#ifndef	__ADC_H
#define	__ADC_H

#include "N76E003.h"
#include "config.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

#define	AINx	0
#define	times	100
//#define	LOW_BAT_NOTIFY	P30
//#define	ST_BY			P14
//#define	BT_POWER		P03
//#define	BT_DET			P04
/*************	���س�������	**************/
#define	AIN0	0
#define	AIN1	1
#define	AIN2	2
#define	AIN3	3
#define	AIN4	4
#define	AIN5	5
#define	AIN6	6
#define	AIN7	7

#define	V_3_3	0x54//0xc9//33
#define	V_3_5	0x59//0xd5//35
#define V_3_6	0x5b



/*************	���غ�������	**************/
//void Timer0_ISR_adc (void);
UINT8	adc_start(void);
void	adc_init(void);
void	AIN	(UINT8	adc_AINx);

/*************  �ⲿ�����ͱ������� *****************/

#endif