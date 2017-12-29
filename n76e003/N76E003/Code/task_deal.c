#define	task_GLOBALS
#include "task_deal.h"
#include "sysinit.h"

bit	led_flag;
UINT8 VOL_LED=0,sys_flag=0;
extern	UINT8	source_in,mode_in,VOL_level;
extern	bit Recive_flag;
extern	void	NPCA110P_init(void);
extern	void __delay_10ms( UINT16 u16CNT );

extern	void	NPCA110P_SOURCE(void);
extern	void	NPCA110P_VOL_A(void);
extern	void	NPCA110P_VOL_B(void);
extern	void	NPCA110P_MODE(void);

void	POWER_ON_OFF(void);
void	SYS_SOURCE(void);
void	SYS_VOL_A(void);
void	SYS_VOL_B(void);
void	SYS_MODE(void);

void	POWER_ON_OFF(void)
{
	if((sys_flag & sys_power_on)&&(power_flag == 1))
	{
		clr_EA;
		MUTE = 1;
		ST_BY = 1;
		sys_flag = sys_flag & (~sys_power_on);
		sys_flag = sys_flag | sys_power_off;
		AUX1_LED = 0;
		MUSIC_LED = 0;
		__delay_10ms(20);
		set_EA;
			NPCA110P_init();
		MUTE = 0;
	}
	else if((sys_flag & sys_power_off)&&(power_flag == 0))
	{
		clr_EA;
		ST_BY = 0;
		sys_flag = sys_flag & (~sys_power_off);
		sys_flag = sys_flag | sys_power_on;
		AUX1_LED = 1;AUX2_LED = 1;BT_LED = 1;
		MUSIC_LED = 1;MOVIE_LED = 1;VOICE_LED = 1;
		__delay_10ms(30);
		set_EA;
	}
}

void	SYS_SOURCE(void)
{
	if(sys_flag == sys_source)
	{
		sys_flag = sys_flag & (~sys_source); 
		BT_POWER = 0;
		source_in++;
		if(source_in>3)
		{
			source_in = 1;			
		}
		else if(source_in==3)		
		{
			BT_POWER = 1;
		}
		NPCA110P_SOURCE();
	}
}

void	SYS_MODE(void)
{
	if(sys_flag == sys_mode)
	{
		sys_flag = sys_flag & (~sys_mode);
		mode_in++;
		NPCA110P_init();
	}
}

void	SYS_VOL_A(void)
{
	if(sys_flag == sys_volA)
	{
		sys_flag = sys_flag & (~sys_volA);
		VOL_level++;
		NPCA110P_VOL_A();
	}
}

void	SYS_VOL_B(void)
{
	if(sys_flag == sys_volB)
	{
		sys_flag = sys_flag & (~sys_volB);
		VOL_level++;
		NPCA110P_VOL_B();
	}
}

void  GPIO_MUTE(void)
{
	if(Recive_flag)
	{
		MUTE = ~MUTE;
	}
}

void	LED_DISPLAY(void)
{
	if(led_flag)
	{
		if(VOL_LED)
		{
			AUX1_LED = 1;AUX2_LED = 1;BT_LED = 1;
			__delay_10ms(20);
		}
		if(source_in == 1)
		{
			AUX1_LED = 0;AUX2_LED = 1;BT_LED = 1;
		}
		if(source_in == 2)
		{
			AUX1_LED = 1;AUX2_LED = 0;BT_LED = 1;
		}
		if(source_in == 3)
		{
			AUX1_LED = 1;AUX2_LED = 1;BT_LED = 0;
		}
		if(mode_in == 1)
		{
			MUSIC_LED = 0;MOVIE_LED = 1;VOICE_LED = 1;
		}
		if(mode_in == 2)
		{
			MUSIC_LED = 1;MOVIE_LED = 0;VOICE_LED = 1;
		}
		if(mode_in == 3)
		{
			MUSIC_LED = 1;MOVIE_LED = 1;VOICE_LED = 0;
		}
		led_flag = 0;
	}
}

void	IR_EVENT(void)
{
	switch(KEY_data)
	{
		case 0x01:							//BASS+
		{
				break;
		}
							
		case 0x02:							//BASS-
		{
			break;
		}
						
		case 0x03:							//TREBLE+
		break;
						
		case 0x04:							//TREBLE-
		break;
						
		case 0x0a:							//??BLUETOOTH??LINE IN
		break;
						
		case 0x0b:							//AUX IN
		break;
												
		case 0x0c:							//BLUETOOTH
		break;

		case 0x0d:							//OPTICAL
		break;
						
		case 0x0E:							//COAXIAL
		break;

		case 0x12:							//VOL+
		break;

		case 0x13:							//VOL-
		break;

		case 0x14:							//ON-OFF
		break;

		case 0x15:							//MUTE
		break;

		case 0x18:							//HDMI
		break;
	}
}



