#include "Common.h"

extern	void Timer0_Delay1ms(UINT32 u32CNT);
extern const unsigned char code g_abMax1xDSPCommands[];
extern	void I2C_Write_Command(UINT8 u8Address, UINT8* p8Data, UINT32 u32ByteSize);
#define		NPCA110P_EEPROM_SLA			0xe6

UINT8	source_in = 0,mode_in = 0;

//模拟输入通道切换命令：
const unsigned char code channel_Commands[] = 
{
0xFF,0xAD,0x83, 	0x00,0x00,0x88,      //通道1 	
0xFF,0xAD,0x86, 	0x00,0x00,0x00,	
0xFF,0xAD,0x86, 	0x00,0x00,0x01,	
0xFF,0xAD,0x86, 	0x00,0x00,0x00,
                                
0xFF,0xAD,0x83, 	0x00,0x00,0x99,      //通道2 	
0xFF,0xAD,0x86, 	0x00,0x00,0x00,	
0xFF,0xAD,0x86, 	0x00,0x00,0x01,	
0xFF,0xAD,0x86, 	0x00,0x00,0x00,
                                
0xFF,0xAD,0x83, 	0x00,0x00,0xAA,      //通道3 	
0xFF,0xAD,0x86, 	0x00,0x00,0x00,	
0xFF,0xAD,0x86, 	0x00,0x00,0x01,	
0xFF,0xAD,0x86, 	0x00,0x00,0x00
};     
unsigned char volume_Control[] = 
{
0xFF,0xd0,0x9a
}; 
   
void	NPCA110P_init(void)
{
	int i;
	source_in = 1,mode_in = 0;
	for(i=0;i<308;i++)
	{
		I2C_Write_Command(NPCA110P_EEPROM_SLA,(g_abMax1xDSPCommands+i*3),3);//924);
		Timer0_Delay1ms(1);
	}
}
void	NPCA110P_VOL_A(void)
{
	volume_Control[2]++;
//	volume_Control[5]++;
	I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
}
void	NPCA110P_VOL_B(void)
{
	volume_Control[2]--;
//	volume_Control[5]--;
	I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
}
void	NPCA110P_MUTE(void)
{
//	I2C_Write_Command(NPCA110P_EEPROM_SLA,g_abMax1xDSPCommands,10);
}
void	NPCA110P_MODE(void)
{
	mode_in++;
	if(mode_in==1)
	I2C_Write_Command(NPCA110P_EEPROM_SLA,g_abMax1xDSPCommands,10);
}
void	NPCA110P_SOURCE(void)
{
	UINT8 i;
	source_in++;
	if(source_in>3)source_in = 1;
	if(source_in==1)	
		for(i=0;i<8;i++)
		{
			I2C_Write_Command(NPCA110P_EEPROM_SLA,channel_Commands+i*3,3);
			Timer0_Delay1ms(1);
		}
	else	if(source_in==2)	
		for(i=0;i<8;i++)
		{
			I2C_Write_Command(NPCA110P_EEPROM_SLA,channel_Commands+24+i*3,3);
			Timer0_Delay1ms(1);
		}
	else	if(source_in==3)	
		for(i=0;i<8;i++)
		{
			I2C_Write_Command(NPCA110P_EEPROM_SLA,channel_Commands+48+i*3,3);
			Timer0_Delay1ms(1);
		}
}