
#define Encoder_GLOBALS
#include "Encoder.h"

//uint8_t	tone;
//uint8_t	tone_flag;
//uint8_t	tone_1=0,tone_2=0,tone_3=0,tone_4=0,tone_5=0,tone_6=0;
extern	uint8_t	Channel1;
extern	uint8_t vol_n,treble_n,sub_n;

void Encoder_Task(void)
{
	if(vol_n>0xf0)
	{
		Amplifier_VOL_A();
		vol_n = 0xf0;
	}
	if(vol_n<0xf0)
	{
		Amplifier_VOL_B();
		vol_n = 0xf0;
	}
	if(treble_n>0xf0)
	{
		Amplifier_TREBLE_A();
		treble_n = 0xf0;
	}
	if(treble_n<0xf0)
	{
		Amplifier_TREBLE_B();
		treble_n = 0xf0;
	}
	if(sub_n>0xf0)
	{
		Amplifier_BASS_A();
		sub_n = 0xf0;
	}
	if(sub_n<0xf0)
	{
		Amplifier_BASS_B();
		sub_n = 0xf0;
	}
	LED_Flag = 0;
	_RST = 1;
	if(Channel1==1)
	{
		LED_G = 0;LED_R = 1;LED_B = 1;
	}
	else	if(Channel1==2)
	{
		LED_R = 0;LED_B = 0;LED_G = 1;
	}
	else if((BT_DET)&&(Channel1==0))
	{
		LED_B = 0;LED_G = 1;LED_R = 1;
	}

}
