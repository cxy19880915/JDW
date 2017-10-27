
#include <stdio.h>
#include "Mini51Series.h"
#include "task.h"
#include "i2c_gpio.h"
#include "KEY_Scan.h"
#include "Bluetooth.h"
#include "ir.h"
#include "usb.h"
//#include "pcm9211.h"


#define PLLCON_SETTING  CLK_PLLCON_50MHz_HXT
#define PLL_CLOCK       50000000

static void SYS_Init(void)
{
	/*---------------------------------------------------------------------------------------------------------*/
	/* Init System Clock                                                                                       */
	/*---------------------------------------------------------------------------------------------------------*/
    /* Set P5 multi-function pins for XTAL1 and XTAL2 */
    SYS->P5_MFP &= ~(SYS_MFP_P50_Msk | SYS_MFP_P51_Msk);
    SYS->P5_MFP |= (SYS_MFP_P50_XTAL1 | SYS_MFP_P51_XTAL2);

    /* Enable External XTAL (4~24 MHz) */
    CLK->PWRCON &= ~CLK_PWRCON_XTLCLK_EN_Msk;
    CLK->PWRCON |= (0x1 << CLK_PWRCON_XTLCLK_EN_Pos); // XTAL12M (HXT) Enabled

    /* Waiting for 12MHz clock ready */
    CLK_WaitClockReady( CLK_CLKSTATUS_XTL_STB_Msk);

    /* Switch HCLK clock source to XTAL */
    CLK->CLKSEL0 &= ~CLK_CLKSEL0_HCLK_S_Msk;
    CLK->CLKSEL0 |= CLK_CLKSEL0_HCLK_S_XTAL;

    /* Enable IP clock */
    CLK->APBCLK |= CLK_APBCLK_UART_EN_Msk; // UART Clock Enable

//    /* Select IP clock source */
    CLK->CLKSEL1 &= ~CLK_CLKSEL1_UART_S_Msk;
    CLK->CLKSEL1 |= (0x0 << CLK_CLKSEL1_UART_S_Pos);// Clock source from external 12 MHz or 32 KHz crystal clock

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    SystemCoreClockUpdate();//选择系统时钟源

}


static void SetupHardware(void)
{
	/* Unlock protected registers */
	SYS_UnlockReg();

	/* Init System, peripheral clock and multi-function I/O */
	SYS_Init();
	
	/* Init GPIO mode */
	GPIO_Init();
	
	/* Init IR mode */
	IR_init();
	ADC_init();
	
	/* Lock protected registers */
	SYS_LockReg();
	
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{	
	unsigned char step = 1;
	Power_Flag = 0;
	SYS_power_flag = 1;
	input_mode = 0;
	Channel_flag = 1;
	LED_Flag = 1;
	LED_ON_Flag = 0;
	SetupHardware();
	I2C_SW_Open(500000);
	ST_BY = 1;
	USB_PLAY = 0;	
	bd_init();
	Data[0] = at24c02_reg[0].reg;
	Data[1] = 0;
	Read_24c02(Data);
	if(Data[1]!=1)
	{
		init_24c02();	
	}
	while(1)
	{
		switch(step)
		{
			case 1:
				if((Power_Flag)&&(SYS_power_flag == 0))
				{
					Sys_power_on();
				}
				else if((!Power_Flag)&&(SYS_power_flag == 1))
				{
					Sys_power_off();
				}
				step = 2;
				break;
			case 2:
				if(LED_Flag)
				{
					LED_Test();
					LED_Flag = 0;
				}	
				step = 3;
				break;
			case 3:
				if(Channel_flag)
				{
					if(input_mode < 3)
					{
						BD_InputMode(0x00);
						CLK_SysTickDelay(1000);
						if(input_mode == 0x00)
						{
							pcm9211_InputMode(0x01);
						}
						else
						{
							pcm9211_InputMode(input_mode+0xc1);	
						}				
					}
					else if(input_mode < 6)
					{
						BD_InputMode(input_mode-0x02);
					}
					LED_Flag = 0x02;
					Channel_flag = 0;
				}
				step = 4;
				break;
			case 4:
				if(IR_flag == 1)
				{
					IR_test_task();
					IR_flag = 0;
				}
				step = 5;
				break;
			case 5:
				if(VOL_F||TREBLE_F||SUB_F)
				{
					if(ST_BY)Encoder_Task();
					VOL_F=0,TREBLE_F=0,SUB_F=0;
				}
				step = 6;
				break;
			case 6:
				if(USB_SW == 1)
				{
					USB_Test_Task();
				}
				step = 1;
				break;
			default:
				step = 1;
				break;
		}
		

		
//		if(BT_connect == 1)
//		{
//			Bluetooth_Test_Task();			
//		}
		
		
//		if(AUDIO_flag == 1)
//		{
//			AMP_MUTE = 1;
//		}
//		else
//		{
//			AMP_MUTE = 0;
//		}
	}
	
	#if 0
	while(1)
	{
		if( POWER_FLAG && (SYS_power_flag == 0) )  		//power on 
		{
			Sys_power_on();
			TAS_5754_Init(slave_addr);
			CLK_SysTickDelay(5000);	
			test_24c02();
			Channel_select(Channel);
		}
		else if( (!POWER_FLAG) && (SYS_power_flag == 1) )//power off
		{
			AMP_MUTE = 0;
			LED_Flag = 0;
			Sys_power_off();			
		}
		IR_test_task();								//IR
		if(VOL_F||TREBLE_F||SUB_F)
			Encoder_Task();
		if(Channel_flag)								//channel
		{
			Channel_flag = 0;
			Channel_select( Channel );	
			LED_Flag = 0;			
		}
		Bluetooth_Test_Task();							//Bluetooth
		// Trigger ADC conversion if it is idle
    if(!ADC_IS_BUSY(ADC)) 							//Voltage
		{
        ADC_START_CONV(ADC);
    }
		if(LED_Flag)
		{
			led_chang(0x2000);
		}
	}
	#endif
}
