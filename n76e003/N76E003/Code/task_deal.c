#define	task_GLOBALS
#include "task_deal.h"

bit	led_flag;
UINT8 VOL_LED=0;
extern	UINT8	source_in,mode_in;
extern	bit Recive_flag;
extern	void	NPCA110P_init(void);
extern	void __delay_10ms( UINT16 u16CNT );

void	POWER_ON_OFF(void)
{
	if((power_change == 1)&&(power_flag == 1))
	{
		MUTE = 1;
		ST_BY = 1;
		power_change = 0;
		AUX1_LED = 0;AUX2_LED = 0;BT_LED = 0;
		MUSIC_LED = 0;MOVIE_LED = 0;VOICE_LED = 0;
		__delay_10ms(2);
			NPCA110P_init();
		MUTE = 0;
	}
	else if((power_change == 0)&&(power_flag == 0))
	{
		ST_BY = 0;
		power_change = 1;
		AUX1_LED = 1;AUX2_LED = 1;BT_LED = 1;
		MUSIC_LED = 1;MOVIE_LED = 1;VOICE_LED = 1;
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



