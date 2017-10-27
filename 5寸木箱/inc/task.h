#ifndef __TASK_H__
#define __TASK_H__

#include <stdio.h>
#include "Mini51Series.h"
#include "KEY_Scan.h"
#include "ir.h"

#ifdef TASK_GLOBALS
	#define TASK_EXT 
#else
	#define TASK_EXT extern
#endif
	
typedef enum  {IDLE=1,HEAD,DATA} irstatus_t;	
//TASK_EXT	uint8_t	LED_Flag;
TASK_EXT	uint32_t ledcount;
TASK_EXT	irstatus_t irwork;
TASK_EXT	uint8_t disp_flag,disp;
TASK_EXT	uint8_t Channel_flag,input_mode;
TASK_EXT	uint8_t KEY_data;
TASK_EXT	uint8_t	VOL_F,TREBLE_F,SUB_F,Power_Flag;
/**
  * IR Define
  */
//#define IR_BT_REV			54
//#define IR_BT_FWD			53
//#define IR_BT_POWER		52
	
/** Define GPIO Pin. 
 *
 */
//#define POWER_KEY   P01
#define BT_REV				P12
#define BT_FWD				P10
#define BT_DET				P53
#define BT_POWER			P00

#define USB_PLAY			P13
#define USB_SW				P14
#define USB_REV				P12
#define USB_FWD				P10
	
#define ICE_DAT				P47
#define ICE_CLK				P46

#define _4052_B				P13
#define _4052_A				P12

#define AMP_MUTE			P24

#define _SDA					P23
#define _SCL					P22

#define AUDIO_DET  		P15

#define ST_BY   			P36

#define SUB_ROTOB			P25
#define SUB_ROTOA			P26
#define TREBLE_ROTOB	P07
#define TREBLE_ROTOA	P06
#define VOL_ROTOB  		P05
#define VOL_ROTOA   	P04

#define IR						P31
#define	MODE_					P30
#define RST_DEV				P54

#define LED_B					P35
#define LED_G					P34
#define LED_R					P32

//#define VOL_ROTOA_1			1
//#define VOL_ROTOB_2			2
//#define TREBLE_ROTOA_3	3
//#define	TREBLE_ROTOB_4	4
//#define	SUB_ROTOA_5			5
//#define SUB_ROTOB_6			6

TASK_EXT	void GPIO_Init( void );
TASK_EXT	void _RST_8230( void );
TASK_EXT	void TMR0_IRQHandler(void);
TASK_EXT	void TMR1_IRQHandler(void);
TASK_EXT	void GPIO01_IRQHandler(void);
TASK_EXT	void GPIO234_IRQHandler(void);
TASK_EXT	void GPIO5_IRQHandler(void);
TASK_EXT	void EINT0_IRQHandler(void);

#endif



