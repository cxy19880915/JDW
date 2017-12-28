#include "adc.h"

/*************	本地变量声明	**************/
UINT8	adc_count = 0;
bit		key_flag = 0;
UINT8	adc_RH = 0;
//UINT8	adc_V = 0;
//bit		adc_V_flag = 0;

#define		POWER		0x00
#define		MODE		0x10
#define		VOL_A		0x20
#define		VOL_B		0x30
#define		SOURCE	0x40

extern	bit power_flag,led_flag;
extern	void	NPCA110P_MODE(void);
extern	void	NPCA110P_SOURCE(void);
extern	void	NPCA110P_VOL_A(void);
extern	void	NPCA110P_VOL_B(void);

UINT8	adc_start(void)
{
	UINT8	adc_dat = 0;
	clr_ADCF;
	set_ADCS;
	while(ADCF == 0);
	adc_dat = ADCRH;
	adc_count++;
	return	adc_dat;
}

void	KEY_EVENT(void)
{
	if(key_flag)
	{
		if(adc_RH == POWER)
		{
			power_flag = ~power_flag;
		}
		if(adc_RH == MODE)
		{
			NPCA110P_MODE();
			led_flag = 1;
		}
		if(adc_RH == VOL_A)
		{
			NPCA110P_VOL_A();
		}
		if(adc_RH == VOL_B)
		{
			NPCA110P_VOL_B();
		}
		if(adc_RH == SOURCE)
		{
			NPCA110P_SOURCE();
			led_flag = 1;
		}
		key_flag = 0;
	}
}

void	adc_init(void)
{
//	InitialUART0_Timer1(115200);
	P04_Quasi_Mode;
	Enable_ADC_AIN5;
//	P04_FALLINGEDGE_TRIG_ADC;											// P0.4 falling edge as adc start trig signal
//	set_EADC;																			// Enable ADC interrupt (if use interrupt)
}

/******************************************************************************
 * FUNCTION_PURPOSE: ADC interrupt Service Routine
 ******************************************************************************/
void ADC_ISR (void) interrupt 11
{
    clr_ADCF;                               //clear ADC interrupt flag
		adc_RH = ADCRH;
		key_flag = 1;
//		if(ADCRH)
//		printf ("\n Value = 0x%bx",ADCRH);
}

#if 0
void	adc_init(void)
{
	ADCCON0&=0xc0;		//AD转换启动AD标志完成
	AINDIDS=0x00;		
	AIN(AINx);			//通道选择并配置
	ADCCON1|=SET_BIT0;	//ADC使能
}

void	AIN	(UINT8	adc_AINx)
{
	switch(adc_AINx)
	{
		case	AIN0:
			ADCCON0 |= 0x00;
			P17_Input_Mode;
			AINDIDS|=SET_BIT0;
			break;
		
		case	AIN1:
			ADCCON0 |= 0x01;
			P30_Input_Mode;
			AINDIDS|=SET_BIT1;
			break;
		
		case	AIN2:
			ADCCON0 |= 0x02;
			P07_Input_Mode;
			AINDIDS|=SET_BIT2;
			break;
			
		case	AIN3:
			ADCCON0 |= 0x03;
			P06_Input_Mode;
			AINDIDS|=SET_BIT3;
			break;
			
		case	AIN4:
			ADCCON0 |= 0x04;
			P05_Input_Mode;
			AINDIDS|=SET_BIT4;
			break;
			
		case	AIN5:
			ADCCON0 |= 0x05;
			P04_Input_Mode;
			AINDIDS|=SET_BIT5;
			break;
			;
		case	AIN6:
			ADCCON0 |= 0x06;
			P03_Input_Mode;
			AINDIDS|=SET_BIT6;
			break;
			
		case	AIN7:
			ADCCON0 |= 0x07;
			P11_Input_Mode;
			AINDIDS|=SET_BIT7;
			break;
			
		default:
			break;
	}
}
#endif