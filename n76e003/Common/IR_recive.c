#include "IR_recive.h"


#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

/********ms***********/
#define	First_Boot_code				8
#define	Second_Boot_code			4
#define	Data_0_1_code					1
#define	Stop_code							40

#define	Data_count						0x04				

#define ir_pin								P03
#define Key_count							14

UINT8 dat[Data_count]={0},key_press=0;
bit Recive_flag=0;

extern	void	NPCA110P_SOURCE(void);
extern	void	NPCA110P_VOL_A(void);
extern	void	NPCA110P_VOL_B(void);
extern	void	NPCA110P_MUTE(void);
extern	void  GPIO_MUTE(void);
extern	bit	power_flag,led_flag;

void IR_init(void)
{
    P03_Input_Mode;
		P03 = 1;
		Enable_BIT3_LowLevel_Trig;
		set_EPI;							// Enable pin interrupt
}



void PinInterrupt_ISR (void) interrupt 7
{
	UINT8 i=0,j=0;
	if(PIF & 0x08)
	{
    PIF =PIF & 0xf7;                             //clear interrupt flag
	#if 1
		clr_EPI;
//		clr_GPIO1;																//亮指示灯
		for(i=0;i<First_Boot_code;i++)						//8ms low
		{
				Timer1_Delay1ms(1);
				if(ir_pin)
				{
						dat_clr();
						set_EPI;
						return;
				}
		}
		while(!ir_pin);

		for(i=0;i<Second_Boot_code;i++)						//4ms	high
		{
				Timer1_Delay1ms(1);
				if(!ir_pin)
				{
						dat_clr();
						set_EPI;
						return;
				}
		}
		while(ir_pin);
	
		for(i=0;i<Data_count;i++)							//32bit数据码
		{
				for(j=0;j<8;j++)
				{
						while(!ir_pin);									//0.56ms	low
					
						Timer1_Delay1ms(Data_0_1_code);
						if(ir_pin)												//数据 1	high
						{
								dat[i] >>= 1;
								dat[i] |= 0x80;
								while(ir_pin);
						}
						else													//数据 0	high
						{
								dat[i] >>= 1;
						}
				}
				
		}
			
		while(!ir_pin);													//0.56ms	low
		
		for(i=0;i<Stop_code;i++)					//40ms		high
		{
				Timer1_Delay1ms(1);
				if(!ir_pin)
				{
					dat_clr();
					set_EPI;
					return;
				}
		}
//		while(ir_pin);	
		set_GPIO1;
		Data_Check();
		Timer1_Delay1ms(2);									//delay2ms
		
		for(i=0;i<First_Boot_code-2;i++)				
		{
				Timer1_Delay1ms(1);
				if(ir_pin)
				{
						dat_clr();
						set_EPI;
						return;
				}
		}
		while(!ir_pin);													//8ms		low

//		for(i=0;i<Second_Boot_code;i++)				
//		{
//				Timer1_Delay1ms(1);
//				if(!ir_pin)
//				{
//						dat_clr();
//						set_EX1;
//						return;
//				}
//		}
		while(ir_pin);														//2ms		high
		
		while(!ir_pin);													//0.56ms	low
//		Timer1_Delay1ms(2000);									//delay2ms
//		while(ir_pin);
		
		dat_clr();
		set_EPI;
		return;
		#endif		
	}
	else
	{
		PIF = 0x00;                             //clear interrupt flag
	}
}



void Data_Check(void)
{
		if(dat[2] == ~dat[3])
		{
				key_press = dat[2];
				dat_clr();
				Recive_flag = 1;
		}
		else
		{
				key_press = 0;
				Recive_flag = 0;
		}
}

void dat_clr(void)
{
		UINT8	i;    
		for(i=0;i<Data_count;i++)
		{
				dat[i] = 0;
		}		
}

void IR_Deal(void)
{
	if(Recive_flag)
	{
		switch(key_press)//switch(ir.dat.data0)
		{
			case	0x01:				//BASS+
				break;
			case	0x02:				//BASS-
				break;
			case	0x03:				//TREBLE+
				break;
			case	0x04:				//TREBLE-
				break;
			case	0x0a:				//LINE IN
				break;
			case	0x0b:				//AUX IN
				break;
			case	0x0c:				//BLUETOOTH
				break;
			case	0x0d:				//OPTICAL
			if(ST_BY)
			{
				NPCA110P_SOURCE();
				led_flag = 1;
			}
				break;
			case	0x0e:				//COAXIAL
				break;
			case	0x12:				//VOL+
			if(ST_BY)
			{
				NPCA110P_VOL_A();
			}
				break;
			case	0x13:				//VOL-
			if(ST_BY)
			{
				NPCA110P_VOL_B();
			}
				break;
			case	0x14:				//ON-OFF
			{
				power_flag = ~power_flag;
				break;
			}
			case	0x15:				//MUTE
			if(ST_BY)
			{
//				NPCA110P_MUTE();
				GPIO_MUTE();
			}
				break;
			case	0x18:				//HDMI
				break;
			default:
				break;
		}
		Recive_flag = 0;
	}
}
