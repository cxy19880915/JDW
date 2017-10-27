#define BD_GLOBALS 

#define IN_Selector		0x04
#define IN_Gain				0x06
#define Vol_Gain_1ch	0x21
#define Vol_Gain_2ch	0x22
#define Bass_Gain			0x51
#define Treble_Gain		0x57
#define Surround_Gain	0x78
#define Test_Mode			0xf0
#define Sys_Reset			0xfe

#include "bd3490.h"


//typedef enum BD_InputMode_Value
//{
//	A=0x00,
//	B=0x01,
//	C=0x02,
//	D=0x03,
//	INPUT_SHUT=0x05,
//	INPUT_MUTE=0x07
//}BD_InputMode_Value;
//enum BD_InpuGain_Value
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
//enum BD_SurroundGain_Value
//{
//	A_OFF=0x00,
//	A_Low=0x05,
//	A_Middle=0x0a,
//	A_High=0x0f,
//	B_OFF=0x10,
//	B_Low=0x15,
//	B_Middle=0x1a,
//	B_High=0x1f
//};
//BD_InpuGain_Value	bd_input_value = _0dB;

 
typedef struct BD3490_REG
{
	unsigned char	reg_addr;
	unsigned char	reg_value;
}BD3490_REG;

BD3490_REG bd_REG[] =
{
	IN_Selector,0x07,//INPUT_MUTE,
	IN_Gain,0x14,//_0dB,
	Vol_Gain_1ch,0xff,
	Vol_Gain_2ch,0xff,
	Bass_Gain,0x80,
	Treble_Gain,0x80,
	Surround_Gain,0x00,//A_OFF,
	Test_Mode,0x00,
	Sys_Reset,0x81
};

void Transmit(BD3490_REG reg);


void Transmit(BD3490_REG reg)
{
	static unsigned char p8Data[2];
		p8Data[0] = reg.reg_addr;
		p8Data[1] = reg.reg_value;
		I2C_SW_Send(BD_Slave_addr,p8Data,2);
}
void bd_init( void )
{
	BD_SysReset();
	CLK_SysTickDelay(10000);
	for(int i=0;i<6;i++)
		Transmit(bd_REG[i]);
}
void BD_InputMode(unsigned char n)
{
	bd_REG[0].reg_addr = IN_Selector;
	bd_REG[0].reg_value = n;
	Transmit(bd_REG[0]);
}
void BD_InputGain(unsigned char n)
{
	bd_REG[1].reg_value = bd_REG[1].reg_value + n;
	Transmit(bd_REG[1]);
}
void BD_VOL_A(void)
{
	bd_REG[2].reg_value = bd_REG[2].reg_value+4;
	if(bd_REG[2].reg_value >= 0xd6)
	{		
		bd_REG[2].reg_value = 0xd6;
		LED_ON_Flag = 1;
	}
	else
	{
		LED_ON_Flag = 0;
	}
	bd_REG[3].reg_value = bd_REG[3].reg_value+4;
	if(bd_REG[3].reg_value >= 0xd6)
			bd_REG[3].reg_value = 0xd6;
	Transmit(bd_REG[2]);
	Transmit(bd_REG[3]);
}
void BD_VOL_B(void)
{
	bd_REG[2].reg_value = bd_REG[2].reg_value-4;
	if(bd_REG[2].reg_value <= 0x80)
	{
		bd_REG[2].reg_value = 0x80;
		LED_ON_Flag = 1;
	}
	else
	{
		LED_ON_Flag = 0;
	}
	bd_REG[3].reg_value = bd_REG[3].reg_value-4;
	if(bd_REG[3].reg_value <= 0x80)
			bd_REG[3].reg_value = 0x80;
	Transmit(bd_REG[2]);
	Transmit(bd_REG[3]);
}
void BD_BASS_A(void)
{
	if(bd_REG[4].reg_value >> 7)
	{
		bd_REG[4].reg_value = bd_REG[4].reg_value - 2;
		if(bd_REG[4].reg_value == 0x80)
			bd_REG[4].reg_value = 0x00;
	}
	else
	{
		bd_REG[4].reg_value = bd_REG[4].reg_value + 2;
		if(bd_REG[4].reg_value >= 0x0e)
		{
			bd_REG[4].reg_value = 0x0e;
			LED_ON_Flag = 1;
		}
		else
		{
		LED_ON_Flag = 0;
		}	
	}
		Transmit(bd_REG[4]);
}
void BD_BASS_B(void)
{
	if(bd_REG[4].reg_value >> 7)
	{
		bd_REG[4].reg_value = bd_REG[4].reg_value + 2;
		if(bd_REG[4].reg_value >= 0x8e)
		{
			bd_REG[4].reg_value = 0x8e;
			LED_ON_Flag = 1;
		}
		else
		{
		LED_ON_Flag = 0;
		}	
	}
	else
	{
		bd_REG[4].reg_value = bd_REG[4].reg_value - 2;
		if(bd_REG[4].reg_value == 0x00)
			bd_REG[4].reg_value = 0x80;
	}
	Transmit(bd_REG[4]);
}
void BD_TREBLE_A(void)
{
	if(bd_REG[5].reg_value >> 7)
	{
		bd_REG[5].reg_value = bd_REG[5].reg_value - 2;
		if(bd_REG[5].reg_value == 0x80)
			bd_REG[5].reg_value = 0x00;
	}
	else
	{
		bd_REG[5].reg_value = bd_REG[5].reg_value + 2;
		if(bd_REG[5].reg_value >= 0x0e)
		{
			bd_REG[5].reg_value = 0x0e;
			LED_ON_Flag = 1;
		}
		else
		{
		LED_ON_Flag = 0;
		}	
	}
		Transmit(bd_REG[5]);
}
void BD_TREBLE_B(void)
{
	if(bd_REG[5].reg_value >> 7)
	{
		bd_REG[5].reg_value = bd_REG[5].reg_value + 2;
		if(bd_REG[5].reg_value >= 0x8e)
		{
			bd_REG[5].reg_value = 0x8e;
			LED_ON_Flag = 1;
		}
		else
		{
		LED_ON_Flag = 0;
		}	
	}
	else
	{
		bd_REG[5].reg_value = bd_REG[5].reg_value - 2;
		if(bd_REG[5].reg_value == 0x00)
			bd_REG[5].reg_value = 0x80;
	}
	Transmit(bd_REG[5]);
}
void BD_SURROUND(unsigned char n)
{
	bd_REG[6].reg_value = bd_REG[6].reg_value + n;
	Transmit(bd_REG[6]);
}
void BD_TestMode(void)
{
	bd_REG[7].reg_value = 0x00;
	Transmit(bd_REG[7]);
}
void BD_SysReset(void)
{
	bd_REG[8].reg_value = 0x81;
	Transmit(bd_REG[8]);
}
