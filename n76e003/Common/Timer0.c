#include	"timer0.h"

extern	UINT8	adc_count;
extern	bit		ms_800_flag,ms_200_flag;

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
//	set_T0M;		//ϵͳʱ��
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
//			adc_data = ADCRL;
//			adc_data = 0;
			if(adc_V < V_3_3)
			{
				power_flag = 0;
//				__delay_10ms(50);
//					while(1)
//					{
//						set_PD;						
//					}
			}
			else
			{
				power_flag = 1;
			}
		adc_flag = 0;
	}
	set_TR0;
}

#endif