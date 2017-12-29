#ifndef	__CONFIG_H
#define	__CONFIG_H

#include "N76E003.h"
#include "Common.h"
//#include "task_deal.h"

#define	MUTE				P11
#define	BT_LED			P01
#define	IR					P03
#define	AD_KEY			P04

#define	AUX2_LED		P02
#define	AUX1_LED		P00

#define	ST_BY				P10

#define	BT_POWER		P05
#define	BT_DET			P30
//#define	BT_PLAY			P11
#define	BT_REV			P07
#define	BT_FWD			P06

#define	MUSIC_LED		P17
#define	MOVIE_LED		P16
#define	VOICE_LED		P15

#define	SDA					P14
#define	SCL					P13
#define	NPCA_RST		P12


#define		POWER		0x00
#define		MODE		0x10
#define		VOL_A		0x20
#define		VOL_B		0x30
#define		SOURCE	0x40

#define		sys_source		0x01
#define		sys_mode			0x02
#define		sys_volA			0x04
#define		sys_volB			0x08
#define		sys_power_on	0x10
#define		sys_power_off	0x20

//#define	VOL_UP		P00
//#define	VOL_DOWN	P01
//#define	PAIR		P10

#endif
