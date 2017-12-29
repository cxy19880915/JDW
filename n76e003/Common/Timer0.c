#include	"timer0.h"

extern	UINT8	adc_count,KEY_VALUE;
extern	bit		ms_800_flag,ms_200_flag;
extern	UINT8	key_flag;
extern	void __delay_10ms( UINT16 u16CNT );

UINT16	adc_data = 0;
UINT8	adc_V = 0;
bit		adc_V_flag = 0,VA=0,VB=0;
bit		adc_PWM_flag = 0;
//UINT8	u8TH0_Tmp_1ms,u8TL0_Tmp_1ms;
UINT8	adc_flag=0,nm=0,mn=0;

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
	adc_flag++;mn++;
	if(mn>20)
	{
		nm = 1;
	}
	if(adc_flag>5)//50ms
	{
		adc_data = adc_start();
		adc_V =	adc_data;
		if(adc_V < 0xfd)
		{
			if(adc_V > V_2_4)
			{
				key_flag = 1;
				KEY_VALUE =  POWER;
				VA = 0;VB = 0;
//				__delay_10ms(1);
			}
			else if(adc_V > V_2_0)
			{
				key_flag = 1;
				KEY_VALUE =  VOL_A;
				if(VA==0)	__delay_10ms(30);
				VA = 1;VB = 0;
			}
			else if(adc_V > V_1_5)
			{
				key_flag = 1;
				KEY_VALUE =  VOL_B;
				if(VB==0)	__delay_10ms(30);
				VB = 1;VA = 0;
			}
			else if(adc_V > V_1_2)
			{
				key_flag = 1;
				KEY_VALUE = SOURCE;
				VA = 0;VB = 0;
				__delay_10ms(30);
			}
			else if(adc_V > V_0_7)
			{
				key_flag = 1;
				KEY_VALUE = MODE;
				VA = 0;VB = 0;
				__delay_10ms(15);
			}
		}
		adc_flag = 0;
	}
	set_TR0;
}

#endif