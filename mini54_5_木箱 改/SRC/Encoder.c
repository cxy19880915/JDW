
#define Encoder_GLOBALS
#include "Encoder.h"

//uint8_t	tone;
//uint8_t	tone_flag;
//uint8_t	tone_1=0,tone_2=0,tone_3=0,tone_4=0,tone_5=0,tone_6=0;


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
}
