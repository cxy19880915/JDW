#include	"timer0.h"

extern	UINT8	adc_count,KEY_VALUE;
extern	bit		ms_800_flag,ms_200_flag;
extern	bit	led_flag,key_flag;


UINT16	adc_data = 0;
UINT8	adc_V = 0;
bit		adc_V_flag = 0;
bit		adc_PWM_flag = 0;
//UINT8	u8TH0_Tmp_1ms,u8TL0_Tmp_1ms;
UINT8	adc_flag=0;

//#define	TH0_INIT_1ms	16000//13290
//#define	TL0_INIT_1ms	16000//13290
//#define	u8TH0_Tmp_1ms	(65536-TH0_INIT_1ms)/256
//#define	u8TL0_Tmp_1ms	(65536-TL0_INIT_1ms)%256

void timer0_init(void)
{
//	set_T0M;		//ÏµÍ³Ê±ÖÓ
	clr_T0M;
//	u8TH0_Tmp_1ms = (65536-TH0_INIT_1ms)/256;
//	u8TL0_Tmp_1ms = (65536-TL0_INIT_1ms)%256;
	TIMER0_MODE1_ENABLE;
	TH0 = HIBYTE(TIMER_DIV12_VALUE_10ms);
  TL0 = LOBYTE(TIMER_DIV12_VALUE_10ms);
	set_ET0;
}

#if 1
void Timer0_ISR (void) interrupt 1 
{
	clr_TR0;
	TH0 = TIMER_DIV12_VALUE_10ms;
    TL0 = TIMER_DIV12_VALUE_10ms;
	adc_flag++;
	if(adc_flag>5)//50ms
	{
		adc_data = adc_start();
		adc_V =	adc_data;
		if(adc_V < 0xfd)
		{
//			adc_data = ADCRL;
//			adc_data = 0;
			if(adc_V > V_2_4)
			{
				KEY_VALUE = POWER;
				key_flag = 1;
//				power_flag = ~power_flag;
			}
			else if(adc_V > V_2_0)
			{
				KEY_VALUE = VOL_A;
				key_flag = 1;
//				VOL_level ++;
			}
			else if(adc_V > V_1_5)
			{
				KEY_VALUE = VOL_B;
				key_flag = 1;
//				VOL_level ++;
			}
			else if(adc_V > V_1_2)
			{
				KEY_VALUE = SOURCE;
				key_flag = 1;
//				source_in++;
			}
			else if(adc_V > V_0_7)
			{
				KEY_VALUE = MODE;
				key_flag = 1;
//				mode_in++;
			}
		}
		adc_flag = 0;
	}
	set_TR0;
}

#endif