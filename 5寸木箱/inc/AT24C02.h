#ifndef __AT24C02_H__
#define __AT24C02_H__

#ifdef AT24C02_GLOBALS
	#define AT24C02_EXT 
#else
	#define AT24C02_EXT extern
#endif

#define AT24C02_Slave_Addr		(0x50<<1)
	
#include "i2c_gpio.h"
	
typedef struct AT24C02_REG
{
	unsigned char reg;
	unsigned char data;
}AT24C02_REG;

AT24C02_EXT	AT24C02_REG at24c02_reg[3];
AT24C02_EXT unsigned char Data[10];

AT24C02_EXT	void Write_24c02(unsigned char* reg,unsigned char n);
AT24C02_EXT	unsigned char Read_24c02(unsigned char* reg);
AT24C02_EXT	void init_24c02(void);
	
#endif
