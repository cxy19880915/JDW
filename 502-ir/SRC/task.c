#define TASK_GLOBALS
#include "task.h"

#pragma anon_unions
#define TIME_INTERRUPT_PERIOD_US        128          //��ʱ�ж�ʱ�䣬���ڼ����½��ص��½���֮��ʱ�䣬Ҳ����һ������+��϶��ʱ��
#define TIME_INFRARED_HEAD_US           13500        //����ͷ��ʱ�䣺TH=9+4.5=13.5ms
#define TIME_INFRARED_REPEAT_US         11500        //�����̰��³���108msʱ�����������źŵ�����ͷ��ʱ�䣺TH=9+2.5=11.5ms
#define TIME_INFRARED_ZERO_US           1125         //���ݡ�0����ʱ�䣺T0=0.565+0.56=1.125ms
#define TIME_INFRARED_ONE_US            2245         //���ݡ�1����ʱ�䣺T1=1.685+0.56=2.245ms
#define TIME_INFRARED_STOP_US			40560		 //���ݽ�����ʱ�䣺TH=40+0.56=40.56ms
//typedef enum  {IDLE=1,HEAD,DATA} irstatus_t; 
typedef union {uint32_t data;struct {uint8_t address0;uint8_t address1;uint8_t data0;uint8_t data1;};}irdata_t;
irdata_t ir;
uint16_t irticks=0;//,audio_2=0;//,ircount=0;
uint32_t audio_1=0,ledcount=0,ir_time=0;
uint8_t ircount=0;
irstatus_t irwork=IDLE;
uint8_t disp_flag=0,disp=0;
uint8_t KEY_data = 0,_100ms_flag=0;
//uint8_t _channel=0;
uint8_t	power_change=0;
//uint8_t vol_n = 0xf0,treble_n = 0xf0,sub_n = 0xf0;
uint8_t	VOL_F=0,TREBLE_F=0,SUB_F=0;
extern	uint8_t	Channel1;
extern	uint8_t	t_s;
/************************************************************
 *@init file
 ************************************************************/
/*
 *Init GPIO mode 
 */
void GPIO_Init( void )
{
	/* Init P2.2 P2.3 P2.4 and P3.6 to be output mode */
	GPIO_SetMode(P0, BIT0, GPIO_PMD_OUTPUT);//BT_REV
	GPIO_SetMode(P0, BIT1, GPIO_PMD_OUTPUT);//BT_FWD
	GPIO_SetMode(P1, BIT0, GPIO_PMD_OUTPUT);//BT_POWER
	GPIO_SetMode(P5, BIT3, GPIO_PMD_INPUT);//BT_DET
//	
//	GPIO_SetMode(P3, BIT0, GPIO_PMD_QUASI);	//IR
	GPIO_SetMode(P1, BIT5, GPIO_PMD_INPUT);//AUDIO_DET
	
	GPIO_SetMode(P3, BIT2, GPIO_PMD_OUTPUT);//LED_B
	GPIO_SetMode(P3, BIT1, GPIO_PMD_OUTPUT);//LED_G
	GPIO_SetMode(P5, BIT4, GPIO_PMD_OUTPUT);//LED_R
	
	GPIO_SetMode(P1, BIT4, GPIO_PMD_QUASI);	//POWER_KEY
	
    GPIO_SetMode(P2, BIT2, GPIO_PMD_OPEN_DRAIN);//_SCL
	GPIO_SetMode(P2, BIT3, GPIO_PMD_OPEN_DRAIN);//_SDA
	
	GPIO_SetMode(P2, BIT4, GPIO_PMD_QUASI);//_RST
	
	GPIO_SetMode(P2, BIT4, GPIO_PMD_QUASI);//AMP_MUTE
	
	GPIO_SetMode(P1, BIT2, GPIO_PMD_OUTPUT);//_4052_A
	GPIO_SetMode(P1, BIT3, GPIO_PMD_OUTPUT);//_4052_B
	
	GPIO_SetMode(P0, BIT4, GPIO_PMD_QUASI);	//VOL_ROTOA
	GPIO_SetMode(P0, BIT5, GPIO_PMD_QUASI);	//VOL_ROTOB
	GPIO_SetMode(P0, BIT6, GPIO_PMD_QUASI);	//TREBLE_ROTOA
	GPIO_SetMode(P0, BIT7, GPIO_PMD_QUASI);	//TREBLE_ROTOB
	GPIO_SetMode(P2, BIT6, GPIO_PMD_QUASI);	//SUB_ROTOA
	GPIO_SetMode(P2, BIT5, GPIO_PMD_QUASI);	//SUB_ROTOB
	
	GPIO_SetMode(P3, BIT6, GPIO_PMD_OUTPUT);//ST_BY 
	
	GPIO_EnableInt(P2, 5, GPIO_INT_BOTH_EDGE);
	GPIO_EnableInt(P2, 6, GPIO_INT_BOTH_EDGE);
//    NVIC_EnableIRQ(GPIO234_IRQn);
	
	/*****init gpio output******/
//	_RST = 0;
//	ST_BY = 0;
//	BT_REV = 0;
//	BT_FWD = 0;
}

// The Timer1 default IRQ, declared in startup_Mini51.s.
void TMR1_IRQHandler(void)
{
	if(ADC_V>0x3f0)
	{
		if((key_count>0x100)&&(key_count<0x2000))
		{
			Channel1++;
			if(Channel1 >= 0x03 )Channel1 = 0;//2 channel
			Channel_flag = 1;
		}
		key_count = 0;
		power_change = 0;
	}
	if((ADC_V>0xf0)&&(ADC_V<0x3f0))
	{
		if((key_count>0x100)&&(key_count<0x2000))
		{
			Channel1++;
			if(Channel1 >= 0x03 )Channel1 = 0;//2 channel
			Channel_flag = 1;
		}
		key_count = 0;
		power_change = 0;
		if(AUDIO_DET)
		{
			audio_1++;
			if(audio_1 >= 0x1ad2748)	//2 hours
			{
//				_RST = 0;
				power_change = 1;
				POWER_FLAG = ~POWER_FLAG;
			}
		}
		else
		{
			audio_1 = 0;
		}
	}
	if(ADC_V<0x0f)
	{
		key_count++;
		if(key_count > 0xfff0)key_count = 0xfff0;
		if((key_count > 0x2000)&&(power_change ==0))
		{
			power_change = 1;
			POWER_FLAG = ~POWER_FLAG;
		}
	}
	if(audio_1>50)
	{
		audio_1 = 0;
		if(VOL_D)
		{
			VOL_F = 1;
		}
		if(TREBLE_D)
		{
			TREBLE_F = 1;
		}
		if(SUB_D)
		{
			SUB_F = 1;
		}
		if((VOL_B)&&(VOL_F))
		{
			vol_n++;
			VOL_F = 0;
			t_s = 1;
		}		
		if((VOL_A)&&(VOL_F))
		{
			vol_n--;
			VOL_F = 0;
			t_s = 1;
		}
		if((TREBLE_B)&&(TREBLE_F))
		{
			treble_n++;
			TREBLE_F = 0;
			t_s = 1;
		}
		if((TREBLE_A)&&(TREBLE_F))
		{
			treble_n--;
			TREBLE_F = 0;
			t_s = 1;
		}
		if((SUB_B)&&(SUB_F))
		{
			sub_n++;
			SUB_F = 0;
			t_s = 1;
		}
		if((SUB_A)&&(SUB_F))
		{
			sub_n--;
			SUB_F = 0;
			t_s = 1;
		}
	}
	if(ir_time>1100)
	{
		ir_time = 0;
		_100ms_flag = 1;
	}
	irticks++;ledcount++;audio_1++;ir_time++;//Power_Meter++;
	if(irticks>0xfffd)irticks = 0xfffd;
    TIMER_ClearIntFlag(TIMER1);
}




/**
 * @brief       Port2/Port3/Port4 IRQ
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The Port2/Port3/Port4 default IRQ, declared in startup_Mini51.s.
 */
void GPIO234_IRQHandler(void)
{
	uint8_t irdata;
    /* To check if P3.0 interrupt occurred */
	if(P3->ISRC & BIT0)
	{
		if(irticks > 0xf0)irwork=IDLE;
		switch(irwork)
    {
			case IDLE: 
				irwork=HEAD;
        break;
						
      case HEAD: 
				irwork=(irticks>((TIME_INFRARED_HEAD_US+TIME_INFRARED_REPEAT_US)/2)/TIME_INTERRUPT_PERIOD_US)?DATA:IDLE;
				if( irwork == DATA)			//BOOT_code
				{
					ir.data = 0;
					ircount = 0;
					disp_flag = 0;
				}
        else// if( disp_flag == 1)	//REPEAT_code
				{
					disp++;
					disp_flag = 1;
					KEY_data = ir.data0;
				}								
        break;
						

      case DATA: 
					irdata=(irticks>((TIME_INFRARED_ZERO_US+TIME_INFRARED_ONE_US )/2)/TIME_INTERRUPT_PERIOD_US)?1:0;
					if( ircount < 8 )
					{
//						ir.address0 >>= 1;
//						ir.address0 |= ( irdata << 7 );
						disp_flag = 0;
					}
					else if( ircount < 16 )
					{
//						ir.address1 >>= 1;
//						ir.address1 |= ( irdata << 7 );
						disp_flag = 0;
					}
					else if( ircount < 24 )
					{
						ir.data0 >>= 1;
						ir.data0 |= ( irdata << 7 );
						disp_flag = 0;
					}
					else if( ircount < 32 )
					{
//						ir.data1 >>= 1;
//						ir.data1 |= ( irdata << 7 );
						disp_flag = 0;
					}
					ircount++;
					if( ircount >= 32 )	
					{
						irwork = IDLE;
						disp_flag=1;
						disp = 0;
						KEY_data = ir.data0;
					}
					break;
    }  
		irticks=0; 
		P3->ISRC = BIT0;
	}
	else 
	{
        /* Un-expected interrupt. Just clear all PORT2, PORT3 and PORT4 interrupts */
        P2->ISRC = P2->ISRC;
        P3->ISRC = P3->ISRC;
        P4->ISRC = P4->ISRC;
    }
}

