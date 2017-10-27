#ifndef __BD3490_H__
#define __BD3490_H__

#include "i2c_gpio.h"
//#include "Mini51Series.h"

#ifdef BD_GLOBALS
	#define BD_EXT 
#else
	#define BD_EXT extern
#endif
	
#define BD_Slave_addr (0x40<<1)
	

//typedef enum BD_InputMode_Value
//{
//	A=0x00,
//	B=0x01,
//	C=0x02,
//	D=0x03,
//	INPUT_SHUT=0x05,
//	INPUT_MUTE=0x07
//}BD_InputMode_Value;	
//typedef	enum BD_InpuGain_Value
//{
//	_0dB=0x00,
//	_2dB=0x02,
//	_4dB=0x04,
//	_6dB=0x06,
//	_8dB=0x08,
//	_12dB=0x0c,
//	_16dB=0x10,
//	_20dB=0x14
//}BD_InpuGain_Value;
//typedef	enum BD_SurroundGain_Value
//{
//	A_OFF=0x00,
//	A_Low=0x05,
//	A_Middle=0x0a,
//	A_High=0x0f,
//	B_OFF=0x10,
//	B_Low=0x15,
//	B_Middle=0x1a,
//	B_High=0x1f
//}BD_SurroundGain_Value;

BD_EXT	unsigned char	VOL_Level;
BD_EXT	unsigned char LED_ON_Flag;

BD_EXT	void bd_init( void );
BD_EXT	void BD_InputMode(unsigned char n);
BD_EXT	void BD_InputGain(unsigned char n);
BD_EXT	void BD_VOL_A(void);
BD_EXT	void BD_VOL_B(void);
BD_EXT	void BD_BASS_A(void);
BD_EXT	void BD_BASS_B(void);
BD_EXT	void BD_TREBLE_A(void);
BD_EXT	void BD_TREBLE_B(void);
BD_EXT	void BD_SURROUND(unsigned char n);
BD_EXT	void BD_TestMode(void);
BD_EXT	void BD_SysReset(void);
	
#endif
