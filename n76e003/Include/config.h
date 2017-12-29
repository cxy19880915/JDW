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


#define		POWER		0xf0
#define		MODE		0x10
#define		VOL_A		0x20
#define		VOL_B		0x30
#define		SOURCE	0x40

#define		ir_play						0x01
#define		ir_fwd						0x02
#define		ir_rev						0x03
#define		ir_hall						0x04
#define		ir_music					0x05
#define		ir_speech					0x06
#define		ir_mute						0x07
#define		ir_volA						0x20
#define		ir_volB						0x30
#define		ir_source					0x40
#define		ir_power					0xf0

#define		sys_source		0x0001
#define		sys_mode			0x0002
#define		sys_volA			0x0004
#define		sys_volB			0x0008
#define		sys_power_on	0x0010
#define		sys_power_off	0x0020
#define		sys_fwd				0x0040
#define		sys_rev				0x0080
#define		sys_hall			0x0100
#define		sys_music			0x0200
#define		sys_speech		0x0400
#define		sys_mute			0x0800
#define		sys_play			0x0100

//#define	VOL_UP		P00
//#define	VOL_DOWN	P01
//#define	PAIR		P10

#endif
