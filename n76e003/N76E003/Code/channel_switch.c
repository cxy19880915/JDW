#include "Common.h"
#include "config.h"

void	NPCA110P_VOL(void);
void	NPCA110P_SOURCE(void);
extern	UINT8 VOL_LED;
extern	bit	led_flag;
extern	bit	led_flag,flag_m,flag_s;
extern	void	delay(void);
//extern	void	GPIO_MUTE(void);
extern const unsigned char code g_abMax1xDSPCommands[];
extern const unsigned char code g_abMax2xDSPCommands[];
extern const unsigned char code g_abMax3xDSPCommands[];
extern	void I2C_Write_Command(UINT8 u8Address, UINT8* p8Data, UINT32 u32ByteSize);
void	NPCA110P_SOURCE(void);
#define		NPCA110P_EEPROM_SLA			0xe6

UINT8	source_in = 1,mode_in = 2,VOL_level = 15;
extern	UINT16 sys_flag;

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
//	GPIO_MUTE();
//	MUTE = 1;
//	if(!MUTE){MUTE = 1;flag_s = 1;flag_m = 1;}
	sys_flag = sys_flag | sys_source;
//	source_in--;
	NPCA110P_SOURCE();
	switch(mode_in)
	{
		case	1:
				for(i=0;i<308;i++)
				{
					I2C_Write_Command(NPCA110P_EEPROM_SLA,(g_abMax1xDSPCommands+i*3),3);//924);
					delay();
				}
				break;
		case	2:
				for(i=0;i<308;i++)
				{
					I2C_Write_Command(NPCA110P_EEPROM_SLA,(g_abMax2xDSPCommands+i*3),3);//924);
					delay();
				}
				break;		
		case	3:
				for(i=0;i<308;i++)
				{
					I2C_Write_Command(NPCA110P_EEPROM_SLA,(g_abMax3xDSPCommands+i*3),3);//924);
					delay();
				}
				break;		
		default:
			break;
	}
	

	
	NPCA110P_VOL();
//	if((flag_s)||(flag_m)){MUTE = 0;flag_s = 0;flag_m = 0;}
//	MUTE = 0;
//	source_in--;
//	NPCA110P_SOURCE();
//	GPIO_MUTE();
}
void	NPCA110P_VOL(void)
{
	switch(VOL_level)
	{
		case	0:
//			GPIO_MUTE();
			volume_Control[0]=0x00;
			volume_Control[2]=0x00;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	1:
//			GPIO_MUTE();
			volume_Control[0]=0x00;
			volume_Control[2]=0x55;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	2:
			volume_Control[0]=0x00;
			volume_Control[2]=0x69;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	3:
			volume_Control[0]=0x00;
			volume_Control[2]=0x9a;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	4:
			volume_Control[0]=0x00;
			volume_Control[2]=0xcd;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	5:
			volume_Control[0]=0x00;
			volume_Control[2]=0xff;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	6:
			volume_Control[0]=0x01;
			volume_Control[2]=0x18;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	7:
			volume_Control[0]=0x01;
			volume_Control[2]=0x31;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	8:
			volume_Control[0]=0x01;
			volume_Control[2]=0x36;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	9:
			volume_Control[0]=0x01;
			volume_Control[2]=0x3b;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	10:
			volume_Control[0]=0x01;
			volume_Control[2]=0x40;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	11:
			volume_Control[0]=0x01;
			volume_Control[2]=0x45;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	12:
			volume_Control[0]=0x01;
			volume_Control[2]=0x4a;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	13:
			volume_Control[0]=0x01;
			volume_Control[2]=0x4f;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	14:
			volume_Control[0]=0x01;
			volume_Control[2]=0x54;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	15:
			volume_Control[0]=0x01;
			volume_Control[2]=0x59;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	16:
			volume_Control[0]=0x01;
			volume_Control[2]=0x5e;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	17:
			volume_Control[0]=0x01;
			volume_Control[2]=0x63;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	18:
			volume_Control[0]=0x01;
			volume_Control[2]=0x68;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	19:
			volume_Control[0]=0x01;
			volume_Control[2]=0x6d;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	20:
			volume_Control[0]=0x01;
			volume_Control[2]=0x72;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	21:
			volume_Control[0]=0x01;
			volume_Control[2]=0x77;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	22:
			volume_Control[0]=0x01;
			volume_Control[2]=0x7c;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	23:
			volume_Control[0]=0x01;
			volume_Control[2]=0x81;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	24:
			volume_Control[0]=0x01;
			volume_Control[2]=0x86;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	25:
			volume_Control[0]=0x01;
			volume_Control[2]=0x8b;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	26:
			volume_Control[0]=0x01;
			volume_Control[2]=0x90;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	27:
			volume_Control[0]=0x01;
			volume_Control[2]=0x95;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	28:
			volume_Control[0]=0x01;
			volume_Control[2]=0x9a;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	29:
			volume_Control[0]=0x01;
			volume_Control[2]=0x9f;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
		case	30:
			volume_Control[0]=0x01;
			volume_Control[2]=0x9f;
			I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
			break;
		
	}
}
//void	NPCA110P_VOL_B(void)
//{
//	VOL_LED = 1;
//	if(volume_Control[2]<=0x00)
//	{
//		VOL_LED = 0;
//		led_flag = 0;
//		return;
//	}
//	if(volume_Control[2]<6)volume_Control[2]=6;
//	volume_Control[2]=volume_Control[2]-6;
////	volume_Control[5]--;
//	I2C_Write_Command(NPCA110P_EEPROM_SLA,volume_Control,3);
//}
void	NPCA110P_MUTE(void)
{
//	I2C_Write_Command(NPCA110P_EEPROM_SLA,g_abMax1xDSPCommands,10);
}
void	NPCA110P_MODE(void)
{
//	mode_in++;
//	if(mode_in>3)mode_in = 1;
//	if(!MUTE){MUTE = 1;flag_m = 1;}
	NPCA110P_init();
//	if(flag_m){MUTE = 0;flag_s = 0;flag_m = 0;}
}
void	NPCA110P_SOURCE(void)
{
	UINT8 i;
//	if(!MUTE){MUTE = 1;flag_s = 1;flag_m = 1;}
	if(source_in==1)	
		for(i=0;i<8;i++)
		{
			I2C_Write_Command(NPCA110P_EEPROM_SLA,channel_Commands+i*3,3);
			delay();delay();
		}
	else	if(source_in==2)	
		for(i=0;i<8;i++)
		{
			I2C_Write_Command(NPCA110P_EEPROM_SLA,channel_Commands+24+i*3,3);
			delay();delay();
		}
	else	if(source_in==3)	
	{
		for(i=0;i<8;i++)
		{
			I2C_Write_Command(NPCA110P_EEPROM_SLA,channel_Commands+48+i*3,3);
			delay();delay();
		}		
	}
//	if(flag_s){MUTE = 0;flag_s = 0;flag_m = 0;}
}