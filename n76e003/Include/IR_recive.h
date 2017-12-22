#ifndef	__IR_RECIVE_H
#define	__IR_RECIVE_H

#include "task_deal.h"


#define	key_ON_OFF						0x14
#define	key_MUTE							0x15
#define	key_HDMI							0x18
#define	key_LINE_IN						0x0a
#define	key_AUX_IN						0x0b
#define	key_BLUETOOTH					0x0c
#define	key_OPTICAL						0x0d
#define	key_COAXIAL						0x0e
#define	key_VOLUME_PLUS				0x12
#define	key_VOLUME_MINUS			0x13
#define	key_BASS_PLUS					0x01
#define	key_BASS_MINUS				0x02
#define	key_TREBLE_PLUS				0x03
#define	key_TREBLE_MINUS			0x04


void IR_init(void);
void IR_Deal(void);
void Data_Check(void);
void dat_clr(void);

#endif
