#define AT24C02_GLOBALS
#include "AT24C02.h"


void init_24c02(void)
{
	Data[0]	= at24c02_reg[0].reg	= 0;
	at24c02_reg[1].reg	= 1;
	at24c02_reg[2].reg	= 2;
	//Init flag
	Data[1]	= at24c02_reg[0].data	= 1;
	//Channel
	Data[2]	= at24c02_reg[1].data	= 0;
	//VAL_Level
	Data[3]	= at24c02_reg[2].data	= 0;

	Write_24c02(Data,3);
}

unsigned char Read_24c02(unsigned char* reg,unsigned char n)
{
	return	I2C_SW_Get(AT24C02_Slave_Addr,reg,n);
}
void Write_24c02(unsigned char* reg,unsigned char n)
{
	I2C_SW_Send(AT24C02_Slave_Addr,reg,n);
}

void test(void)
{
//	Data[0]	= 0;
//	init_24c02();
//	Data[0]	= 0;
//	Read_24c02(Data);
//	Data[0]	= 1;
//	Read_24c02(Data);
//	Data[0]	= 2;
//	Read_24c02(Data);
//	init_24c02();
//	Write_24c02(Data,9);
//	Data[0]	= 0;
//	Read_24c02(Data);
//		Data[0]	= 1;
//	Read_24c02(Data);
//	Data[0]	= 2;
//	Read_24c02(Data);
}
