#include "IR_recive.h"
#include "config.h"

#include "N76E003.h"
#include "Common.h"
//#include "Delay.h"
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

//#define		ir_play						0x01
//#define		ir_fwd						0x02
//#define		ir_rev						0x03
//#define		ir_hall						0x04
//#define		ir_music					0x05
//#define		ir_speech					0x06
//#define		ir_mute						0x07
//#define		ir_volA						0x20
//#define		ir_volB						0x30
//#define		ir_source					0x40
//#define		ir_power					0xf0
//#define		ir_play						0x10

UINT8 dat[Data_count]={0},key_press=0,ir_status=0,ir_count=0,key_PRE=0;
bit Recive_flag=0;

extern	void __delay_1ms( UINT16 u16CNT );
extern	void Timer1_Delay1ms(UINT32 u32CNT);
extern	void	NPCA110P_SOURCE(void);
extern	void	NPCA110P_MODE(void);
extern	void	NPCA110P_VOL_A(void);
extern	void	NPCA110P_VOL_B(void);
extern	void	NPCA110P_MUTE(void);
extern	void  GPIO_MUTE(void);
extern	bit	power_flag,led_flag,_50ms_ir;

extern	void BT_Play_Pause(void);	
extern	void BT_REV_TASK(void);	
extern	void BT_FWD_TASK(void);	

extern	UINT8 KEY_VALUE;
extern	UINT8 mode_in;
extern	UINT8		key_flag;

bit	ir_long=0,ir_short=0;
UINT8	ir_play_lg=0,ir_fwd_lg=0,ir_rev_lg=0,ir_source_lg=0,ir_hall_lg=0;
UINT8	ir_music_lg=0,ir_speech_lg=0,ir_volA_lg=0,ir_volB_lg=0,ir_power_lg=0,ir_mute_lg=0;

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
//			Timer1_Delay1ms(1);
			__delay_1ms(1);
		}while(!ir_pin);
		if(n11<5)//没有达到8ms low
		{
			dat_clr();
			set_EPI;
			return;
		}
		n11=0;
		
		do//4ms	high or 2ms	high
		{
			n11++;
//			Timer1_Delay1ms(1);
			__delay_1ms(1);
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
					
//						Timer1_Delay1ms(Data_0_1_code);
						__delay_1ms(1);
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
		__delay_1ms(3);
//		Timer1_Delay1ms(11);		
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
	if(_50ms_ir)
	{
		_50ms_ir = 0;
		if(ir_status & 0x80)
		{
			ir_count++;
			if(key_press == 0x00)//key up
			{
				ir_count = 0;
				switch(key_PRE)//switch(ir.dat.data0)
				{
					case	0x10:				//PLAY
							key_flag = 0x80;
							KEY_VALUE = ir_play;			
					break;
					case	0x11:				//FWD
							key_flag = 0x80;
							KEY_VALUE = ir_fwd;
						break;
					case	0x16:				//REV
							key_flag = 0x80;
							KEY_VALUE = ir_rev;
						break;
					case	0x04:				//TREBLE-
						break;
					case	0x0a:				//LINE IN
						break;
					case	0x0b:				//AUX IN
						break;
					case	0x0c:				//BLUETOOTH
						break;
					case	0x41:				//SOURCE
							key_flag = 0x80;
							KEY_VALUE = ir_source;
						break;
					case	0x4a:				//HALL
							key_flag = 0x80;
							KEY_VALUE = ir_hall;
						break;
					case	0x4b:				//MUSIC
							key_flag = 0x80;
							KEY_VALUE = ir_music;
						break;
					case	0x4c:				//SPEECH
							key_flag = 0x80;
							ir_speech_lg++;
							KEY_VALUE = ir_speech;			
						break;
					case	0x12:				//VOL+
							key_flag = 0x80;
							KEY_VALUE = ir_volA;	
						break;			
					case	0x13:				//VOL-
							key_flag = 0x80;
							KEY_VALUE = ir_volB;
						break;
					case	0x14:				//ON-OFF
							key_flag = 0x80;
							KEY_VALUE = ir_power;
						break;
					case	0x15:				//MUTE
							key_flag = 0x80;
							KEY_VALUE = ir_mute;
						break;
					case	0x18:				//HDMI
						break;
					default:
						break;
				}
				ir_status = ir_status & 0x00;
			}
		}
		if(Recive_flag)//key down
		{
			Recive_flag = 0;	
			ir_status =ir_status | 0x80;
			key_PRE = key_press;
			if(ir_count>2)
			switch(key_press)//switch(ir.dat.data0)
			{
//				case	0x10:				//PLAY
//						key_flag = 0x80;
//						KEY_VALUE = ir_play;			
//				break;
//				case	0x11:				//FWD
//						key_flag = 0x80;
//						KEY_VALUE = ir_fwd;
//					break;
//				case	0x16:				//REV
//						key_flag = 0x80;
//						KEY_VALUE = ir_rev;
//					break;
//				case	0x04:				//TREBLE-
//					break;
//				case	0x0a:				//LINE IN
//					break;
//				case	0x0b:				//AUX IN
//					break;
//				case	0x0c:				//BLUETOOTH
//					break;
//				case	0x41:				//SOURCE
//						key_flag = 0x80;
//						KEY_VALUE = ir_source;
//					break;
//				case	0x4a:				//HALL
//						key_flag = 0x80;
//						KEY_VALUE = ir_hall;
//					break;
//				case	0x4b:				//MUSIC
//						key_flag = 0x80;
//						KEY_VALUE = ir_music;
//					break;
//				case	0x4c:				//SPEECH
//						key_flag = 0x80;
//						ir_speech_lg++;
//						KEY_VALUE = ir_speech;			
//					break;
				case	0x12:				//VOL+
						key_flag = 0x80;
						KEY_VALUE = ir_volA;	
					break;			
				case	0x13:				//VOL-
						key_flag = 0x80;
						KEY_VALUE = ir_volB;
					break;
//				case	0x14:				//ON-OFF
//						key_flag = 0x80;
//						KEY_VALUE = ir_power;
//					break;
//				case	0x15:				//MUTE
//						key_flag = 0x80;
//						KEY_VALUE = ir_mute;
//					break;
//				case	0x18:				//HDMI
//					break;
				default:
					break;
			}
			key_press = 0;

//		}
		#if 0
		if(ir_status & 0x02)//long
		{
			switch(key_press)//switch(ir.dat.data0)
			{
				case	0x10:				//PLAY
						key_flag = 0x80;
						KEY_VALUE = ir_play;			
				break;
				case	0x11:				//FWD
						key_flag = 0x80;
						KEY_VALUE = ir_fwd;
					break;
				case	0x16:				//REV
						key_flag = 0x80;
						KEY_VALUE = ir_rev;
					break;
				case	0x04:				//TREBLE-
					break;
				case	0x0a:				//LINE IN
					break;
				case	0x0b:				//AUX IN
					break;
				case	0x0c:				//BLUETOOTH
					break;
				case	0x41:				//SOURCE
						key_flag = 0x80;
						KEY_VALUE = ir_source;
					break;
				case	0x4a:				//HALL
						key_flag = 0x80;
						KEY_VALUE = ir_hall;
					break;
				case	0x4b:				//MUSIC
						key_flag = 0x80;
						KEY_VALUE = ir_music;
					break;
				case	0x4c:				//SPEECH
						key_flag = 0x80;
						ir_speech_lg++;
						KEY_VALUE = ir_speech;			
					break;
				case	0x12:				//VOL+
						key_flag = 0x80;
						KEY_VALUE = ir_volA;	
					break;			
				case	0x13:				//VOL-
						key_flag = 0x80;
						KEY_VALUE = ir_volB;
					break;
				case	0x14:				//ON-OFF
						key_flag = 0x80;
						KEY_VALUE = ir_power;
					break;
				case	0x15:				//MUTE
						key_flag = 0x80;
						KEY_VALUE = ir_mute;
					break;
				case	0x18:				//HDMI
					break;
				default:
					break;
			}			
		}
		#endif
		}
//	ir_count = 0;
	}
}
