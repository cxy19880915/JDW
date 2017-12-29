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
extern	void	NPCA110P_MODE(void);
extern	void	NPCA110P_VOL_A(void);
extern	void	NPCA110P_VOL_B(void);
extern	void	NPCA110P_MUTE(void);
extern	void  GPIO_MUTE(void);
extern	bit	power_flag,led_flag;

extern	void BT_Play_Pause(void);	
extern	void BT_REV_TASK(void);	
extern	void BT_FWD_TASK(void);	

extern	UINT8 VOL_LED;
extern	UINT8 mode_in;

void dat_clr(void);

void IR_init(void)
{
    P03_Input_Mode;
		P03 = 1;
		Enable_BIT3_LowLevel_Trig;
		set_EPI;							// Enable pin interrupt
}



void PinInterrupt_ISR (void) interrupt 7
{
	UINT8 i=0,j=0,n11=0;
	if(PIF & 0x08)
	{
    PIF =PIF & 0xf7;                             //clear interrupt flag
		clr_EPI;
		i++;
		do//9ms low
		{
			n11++;
			Timer1_Delay1ms(1);
		}while(!ir_pin);
//		if(n<First_Boot_code)//没有达到8ms low
//		{
////			dat_clr();
//			set_EPI;
//			return;
//		}
		n11=0;
		
		do//4ms	high or 2ms	high
		{
			n11++;
			Timer1_Delay1ms(1);
//			if((!ir_pin)&&(n<Second_Boot_code))//2ms	high
//				{
//						dat_clr();
//						set_EPI;
//						return;
//				}
		}while(ir_pin);
		n11=0;
		
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
//		do//40ms	high
//		{
//			n11++;
//			Timer1_Delay1ms(1);
////				if(n>30)//20ms	high
////				{
////					n=0;
////					Data_Check();
////					dat_clr();
//////					Timer1_Delay1ms(100);
////					set_EPI;
////					return;
////				}
//		}while(ir_pin);
		Data_Check();
		Timer1_Delay1ms(30);		
		dat_clr();
		set_EPI;
		return;
		#if 0
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
	UINT8 mod=0;
	if(Recive_flag)
	{
		switch(key_press)//switch(ir.dat.data0)
		{
			case	0x10:				//PLAY
			if(ST_BY)
			{
				BT_Play_Pause();
				led_flag = 1;
				VOL_LED = 1;
			}
				break;
			case	0x11:				//FWD
			if(ST_BY)
			{
				BT_FWD_TASK();
				led_flag = 1;
				VOL_LED = 1;
			}	
				break;
			case	0x16:				//REV
			if(ST_BY)
			{
				BT_REV_TASK();
				led_flag = 1;
				VOL_LED = 1;
			}
				break;
			case	0x04:				//TREBLE-
				break;
			case	0x0a:				//LINE IN
				break;
			case	0x0b:				//AUX IN
				break;
			case	0x0c:				//BLUETOOTH
//			if()
				break;
			case	0x41:				//SOURCE
			if(ST_BY)
			{
				NPCA110P_SOURCE();
				led_flag = 1;
			}
				break;
			case	0x4a:				//HALL
			if(ST_BY)	
			{
				mod = 1;
				if(mode_in!=mod)
				{
					mode_in = 1;
					NPCA110P_MODE();
					led_flag = 1;
				}
			}
				break;
			case	0x4b:				//HALL
			if(ST_BY)	
			{
				mod = 2;
				if(mode_in!=mod)
				{
					mode_in = 2;
					NPCA110P_MODE();
					led_flag = 1;
				}
			}
				break;
			case	0x4c:				//HALL
			if(ST_BY)	
			{
				mod = 3;
				if(mode_in!=mod)
				{
					mode_in = 3;
					NPCA110P_MODE();
					led_flag = 1;
				}
			}
				break;
			case	0x12:				//VOL+
			if(ST_BY)
			{
				NPCA110P_VOL_A();
				led_flag = 1;
			}
				break;
			case	0x13:				//VOL-
			if(ST_BY)
			{
				NPCA110P_VOL_B();
				led_flag = 1;
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
