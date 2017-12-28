#include "Common.h"
#include "config.h"

extern	UINT8 VOL_LED;
extern	void Timer0_Delay1ms(UINT32 u32CNT);
extern	void	GPIO_MUTE(void);
extern const unsigned char code g_abMax1xDSPCommands[];
extern const unsigned char code g_abMax2xDSPCommands[];
extern const unsigned char code g_abMax3xDSPCommands[];
extern	void I2C_Write_Command(UINT8 u8Address, UINT8* p8Data, UINT32 u32ByteSize);
void	NPCA110P_SOURCE(void);
#define		NPCA110P_EEPROM_SLA			0xe6

UINT8	source_in = 1,mode_in = 1;

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
	0x01, 0xd0, 0x9a
}; 
   
void	NPCA110P_init(void)
{
	int i;
//	source_in = 1,mode_in = 1;
	GPIO_MUTE();
	switch(mode_in)
	{
		case	1:
				for(i=0;i<308;i++)
				{
					I2C_Write_Command(NPCA110P_EEPROM_SLA,(g_abMax1xDSPCommands+i*3),3);//924);
					Timer0_Delay1ms(1);
				}
				break;
		case	2:
				for(i=0;i<308;i++)
				{
					I2C_Write_Command(NPCA110P_EEPROM_SLA,(g_abMax2xDSPCommands+i*3),3);//924);
					Timer0_Delay1ms(1);
				}
				break;		
		case	3:
				for(i=0;i<308;i++)
				{
					I2C_Write_Command(NPCA110P_EEPROM_SLA,(g_abMax3xDSPCommands+i*3),3);//924);
					Timer0_Delay1ms(1);
				}
				break;		
		default:
			break;
	}
	source_in--;
	NPCA110P_SOURCE();
	GPIO_MUTE();
}
void	NPCA110P_VOL_A(void)
{
	VOL_LED = 1;
	if(volume_Control[2]>=0xf3)
	{
		VOL_LED = 0;
		return;
	}
	volume_Control[2]=volume_Control[2]+6;
//	volume_Control[5]++;
	I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
}
void	NPCA110P_VOL_B(void)
{
	VOL_LED = 1;
	if(volume_Control[2]<=0x00)
	{
		VOL_LED = 0;
		return;
	}
	if(volume_Control[2]<6)volume_Control[2]=6;
	volume_Control[2]=volume_Control[2]-6;
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
	if(mode_in>3)mode_in = 1;
	NPCA110P_init();
}
void	NPCA110P_SOURCE(void)
{
	UINT8 i;
	BT_POWER = 0;
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
	{
		BT_POWER = 1;
		for(i=0;i<8;i++)
		{
			I2C_Write_Command(NPCA110P_EEPROM_SLA,channel_Commands+48+i*3,3);
			Timer0_Delay1ms(1);
		}		
	}

}