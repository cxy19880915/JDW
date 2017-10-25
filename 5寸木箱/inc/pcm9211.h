#ifndef __PCM9211_H__
#define __PCM9211_H__

#ifdef PCM9211_GLOBALS
	#define PCM9211_EXT 
#else
	#define PCM9211_EXT extern
#endif
	
#include "i2c_gpio.h"

#define PCM_Slave_Addr	(0x41<<1)
	
PCM9211_EXT	void pcm9211_RST(void);
PCM9211_EXT	void pcm9211_init(void);
PCM9211_EXT	void pcm9211_InputMode(unsigned char n);
	
#endif

