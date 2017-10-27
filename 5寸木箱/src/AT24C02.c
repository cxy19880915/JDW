#define AT24C02_GLOBALS
#include "AT24C02.h"


void init_24c02(void)
{
	at24c02_reg[0].reg	= 0;
	at24c02_reg[0].data	= 1;
	at24c02_reg[1].reg	= 1;
	at24c02_reg[1].data	= 0;
	at24c02_reg[2].reg	= 2;
	at24c02_reg[0].data	= 0;
	Write_24c02(Data,6);
}

unsigned char Read_24c02(unsigned char* reg)
{
	return I2C_SW_Get(AT24C02_Slave_Addr,reg,1);
}
void Write_24c02(unsigned char* reg,unsigned char n)
{
	I2C_SW_Send(AT24C02_Slave_Addr,reg,n);
}

