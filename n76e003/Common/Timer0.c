#include	"timer0.h"

extern	UINT8	adc_count,KEY_VALUE;
extern	bit		ms_800_flag,ms_200_flag;
extern	UINT8	key_flag;
extern	void __delay_10ms( UINT16 u16CNT );
extern	UINT8 ir_status,ir_count;
UINT16	adc_data = 0;
UINT8	adc_V = 0;
UINT8 key_status = 0;
bit		adc_V_flag = 0;//,VA=0,VB=0,V_M = 0,V_S = 0,V_power = 0;
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
	adc_flag++;
	if(adc_flag>5)//50ms
	{
		adc_data = adc_start();
		adc_V =	adc_data;
		if((key_status & 0x80)||(key_flag & 0x80))mn++;
		if(mn>15)
		{
			if(ir_count>2)
			{
				ir_status = 0x01;
			}
			if(ir_count==1)
			{
				ir_status = 0x02;
			}
			if(ir_count==0)
			{
				ir_status = 0x04;
			}
		}
		if(adc_V < 0xfd)				//key down
		{
			if(adc_V > V_2_4)
			{			
				key_status = key_status | 0x81;
			}
			else if(adc_V > V_2_0)
			{
				if((key_status&0x02)&&(mn>15))
				{
					key_flag = 1;
					KEY_VALUE =  VOL_A;
				}
				key_status = key_status | 0x82;
			}
			else if(adc_V > V_1_5)
			{
				if((key_status&0x04)&&(mn>15))
				{
					key_flag = 1;
					KEY_VALUE =  VOL_B;
				}
				key_status = key_status | 0x84;
			}
			else if(adc_V > V_1_2)
			{
//				if(key_status&0x08)
//				{
//					key_flag = 1;
//					KEY_VALUE = SOURCE;
//				}
				key_status = key_status | 0x88;
			}
			else if(adc_V > V_0_7)
			{
//				if(key_status&0x10)
//				{
//					key_flag = 1;
//					KEY_VALUE = MODE;					
//				}
				key_status = key_status | 0x90;
			}
		}
		else
		{
			if(key_status&0x80)
			{
				if(key_status&0x01)
				{
					key_flag = 1;
					KEY_VALUE =  POWER;
				}	
				if(key_status&0x02)
				{
					key_flag = 1;
					KEY_VALUE =  VOL_A;
				}
				if(key_status&0x04)
				{
					key_flag = 1;
					KEY_VALUE =  VOL_B;
				}
				if(key_status&0x08)
				{
					key_flag = 1;
					KEY_VALUE = SOURCE;
				}
				if(key_status&0x10)
				{
					key_flag = 1;
					KEY_VALUE = MODE;					
				}
			}
			key_status = key_status & 0x00;//key up
			mn = 0;
		}
		adc_flag = 0;
	}
	set_TR0;
}

#endif