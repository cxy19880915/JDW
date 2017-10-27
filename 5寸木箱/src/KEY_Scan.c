
#define KEY_GLOBALS
#include "KEY_Scan.h"


uint8_t	SYS_power_flag = 0;
uint16_t key_count = 0;
uint8_t Channel[1] = {0x00};

uint16_t ADC_V=0x4fe;

void ADC_init(void)
{
	CLK_EnableModuleClock(ADC_MODULE);
	CLK_SetModuleClock(ADC_MODULE,CLK_CLKSEL1_ADC_S_XTAL,CLK_CLKDIV_ADC(6));
		/* Set P3.0 to ADC channel 6 input pin */
	SYS->P1_MFP = SYS_MFP_P14_AIN4;
	/* Analog pin OFFD to prevent leakage */
	P1->OFFD |= (1<<4) << GPIO_OFFD_OFFD_Pos;	
	// Enable channel 6
    ADC_Open(ADC, 0, 0, 0x01 << 4);
	// Power on ADC
    ADC_POWER_ON(ADC);
	// Enable ADC convert complete interrupt
    ADC_EnableInt(ADC, ADC_ADF_INT);
    NVIC_EnableIRQ(ADC_IRQn);	
}

void LED_Test(void)
{
	if(ST_BY)
	{
		if(LED_Flag==0x01)
		{
				CLK_SysTickDelay(50000);
				RST_DEV = 1;
				bd_init();
				LED_B = 0;LED_G = 0;LED_R = 0;
				LED_Flag = 0x02;
		}
		if(LED_Flag==0x02)
		{
			AMP_MUTE = 1;
			if(input_mode==0x00)
			{
//				pcm9211_RST();
//				pcm9211_init();
				LED_B = 0;LED_G = 0;LED_R = 0;
//				AMP_MUTE = 0;
			}
			if(input_mode==0x01)
			{
//				pcm9211_RST();
//				pcm9211_init();
				LED_B = 0;LED_G = 0;LED_R = 1;
//				AMP_MUTE = 0;
			}
			if(input_mode==0x02)
			{
//				pcm9211_RST();
//				pcm9211_init();
				LED_B = 0;LED_G = 0;LED_R = 1;
				USB_SW = 1;
			}
			if(input_mode==0x03)
			{
				LED_B = 0;LED_G = 1;LED_R = 1;
			}
			if(input_mode==0x04)
			{
				LED_B = 1;LED_G = 1;LED_R = 0;
			}
			if(input_mode==0x05)
			{
				BT_POWER = 1;
				LED_B = 1;LED_G = 0;LED_R = 0;
				CLK_SysTickDelay(50000);
			}
			else
			{
				BT_POWER = 0;
				BT_connect = 0;
			}
			AMP_MUTE = 0;
		}
		if(LED_Flag==0x03)
		{
			LED_B = ~LED_B;LED_G = ~LED_G;LED_R = ~LED_R;
			CLK_SysTickDelay(50000);
			LED_B = ~LED_B;LED_G = ~LED_G;LED_R = ~LED_R;
		}
	}
	else
	{
			AMP_MUTE = 1;
			RST_DEV = 0;
			BT_POWER = 0;
			LED_B = 1;LED_G = 1;LED_R = 1;
	}
}


void ADC_IRQHandler(void)
{
    uint32_t u32Flag;

    // Get ADC comparator interrupt flag
    u32Flag = ADC_GET_INT_FLAG(ADC, ADC_ADF_INT);

    // Get ADC convert result
	ADC_V = (uint32_t)ADC_GET_CONVERSION_DATA(ADC, 0);
    ADC_CLR_INT_FLAG(ADC, u32Flag);
}
void Sys_power_on( void )
{			
	ST_BY = 1;
	SYS_power_flag = 1;
	CLK_SysTickDelay(200000);	
	RST_DEV = 1;
	bd_init();
	LED_B = 0;LED_G = 0;LED_R = 0;
	LED_Flag = 0x02;
}

void Sys_power_off( void )
{
	BT_POWER = 0;
	ST_BY = 0;
	SYS_power_flag = 0;
	LED_R = 1;LED_B = 1;LED_G = 1;
}

void Channel_select( uint8_t* Channel )
{
	uint8_t p[2];
	p[0] = 31;
	AMP_MUTE = 0;
	switch( *Channel )
	{
//		case 2:
//			_4052_A = 0;
//			_4052_B = 0;
//			if( SYS_power_flag )
//			{
//				LED_R = 0;LED_B = 1;LED_G = 1;		
//			}
//			p[1] = 0;
//			I2C_SW_Send(_24c02_addr,p,2);
//			*Channel = 0x00;
//			break;
		case 0:		//Bluetooth
			CLK_SysTickDelay(200000);
			_4052_A = 1;
			_4052_B = 0;
			if( SYS_power_flag )
			{
				BT_POWER = 1;
				LED_R = 1;LED_B = 0;LED_G = 1;		
			}
			p[1] = 0;
			I2C_SW_Send(_24c02_addr,p,2);
			*Channel = 0x00;
			break;
		case 1:			//aux
			_4052_A = 0;
			_4052_B = 1;
			if( SYS_power_flag )
			{
				BT_POWER = 0;
				LED_R = 1;LED_B = 1;LED_G = 0;		
			}
			p[1] = 1;
			I2C_SW_Send(_24c02_addr,p,2);
			*Channel = 0x01;
			break;
//		case 3:
//			_4052_A = 1;
//			_4052_B = 1;
//			if( SYS_power_flag )
//			{
//				LED_R = 0;LED_B = 0;LED_G = 0;		
//			}
//			p[1] = 3;
//			I2C_SW_Send(_24c02_addr,p,2);
//			*Channel = 0x03;
//			break;
		default:
			break;
	}
	CLK_SysTickDelay(100000);
	AMP_MUTE = 1;
}
