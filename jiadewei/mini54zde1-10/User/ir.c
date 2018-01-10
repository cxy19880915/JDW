/******************************************************************************
* @file     ir.c
* @brief    The Driver code for VS1838A with MINI54FDE
* @version  1.0.0
* @date     22, August, 2014
*
* @note
* Copyright (C) 2000-2014 PM9GZY by yuanxihua@21cn.com. All rights reserved.
******************************************************************************/
#include "ir.h"

uint8_t	ir_static=0,KEY_pre=0;
uint8_t	pause_flag=0;//1play 0 pause
extern	uint8_t	Channel1,mute_flag;
extern	uint8_t	_100ms_flag;

void IR_init(void)
{	
	/*  Configure P1.0 as Quasi-bidirection mode and enable interrupt by falling edge trigger */
    GPIO_SetMode(P3, BIT0, GPIO_PMD_QUASI);
    GPIO_EnableInt(P3, 0, GPIO_INT_FALLING);
    NVIC_EnableIRQ(GPIO234_IRQn);
	
	// Enable IP clock
    CLK_EnableModuleClock(TMR1_MODULE);        
    // Select Timer 1 clock source from internal 22.1184MHz RC clock.
    CLK_SetModuleClock(TMR1_MODULE,CLK_CLKSEL1_TMR1_S_IRC22M,1);
    // configure timer to operate in specified mode.
    TIMER_Open(TIMER1, TIMER_PERIODIC_MODE, 7812);        //7.8125K = 0.128MS = 128US
    // start Timer counting
    TIMER_Start(TIMER1);
    // enable the Timer time-out interrupt function.
    TIMER_EnableInt(TIMER1);
    // Enable timer interrupt
    NVIC_EnableIRQ(TMR1_IRQn);
}

void IR_test_task(void)
{
	uint8_t p[2];
	if(_100ms_flag)
	{
		p[0] = 29;
		_100ms_flag = 0;
		if(ir_static & 0x01)
		{
			if(KEY_data==0x00)//key up
			{
				ir_static = ir_static | 0x04;
				if((KEY_pre!=0x15)||(KEY_pre!=0x14))
				{
					LED_Flag = 0;
					_RST = 1;
					if(Channel1==1)
					{
							LED_G = 0;LED_R = 1;LED_B = 1;
					}
					else	if(Channel1==2)
					{
							LED_R = 0;LED_B = 0;LED_G = 1;
					}
					else if((BT_DET)&&(Channel1==0))
					{
							LED_B = 0;LED_G = 1;LED_R = 1;
					}
				}				
				
				switch(KEY_pre)
				{
						case 0x0a:							//LINE IN
							{
								p[1] = Channel1 = 2;
								Channel_select(Channel1);
								I2C_SW_Send(_24c02_addr,p,2);
							}
						break;
						
						case 0x0b:							//AUX IN
							{
								p[1] = Channel1 = 1;
								Channel_select(Channel1);
								I2C_SW_Send(_24c02_addr,p,2);
							}
						break;
												
						case 0x0c:							//BLUETOOTH
							if(Channel1)
							{
								p[1] = Channel1 = 0;
								Channel_select(Channel1);
								I2C_SW_Send(_24c02_addr,p,2);
								pause_flag = 0;
							}
							else if(disp<3)
							{
								BT_Play_Pause();	
								LED_R = 1;LED_G = 1;LED_B = 1;
								CLK_SysTickDelay(40000);LED_B = 0;									
							}
						break;

//						case 0x0d:							//OPTICAL
//						break;
//						
//						case 0x0E:							//COAXIAL
//						break;
						
						case 0x14:							//ON-OFF
							POWER_FLAG = ~POWER_FLAG;
						break;

						case 0x15:							//MUTE
							if( SYS_power_flag )
							{
								if(mute_flag)
								{
									_RST=1;
									mute_flag = 0;
									LED_Flag=0;
								}
								else
								{
									_RST=0;
									LED_Flag=1;
									mute_flag=1;
								}								
							}							
						break;

//						case 0x18:							//HDMI
//						break;
						default:
							break;
				}
				ir_static = ir_static & 0x00;
			}
		}
		if(disp_flag)//key down
		{
			disp_flag = 0;
			ir_static=ir_static | 0x01;
			KEY_pre = KEY_data;
			switch(KEY_pre)
			{
						case 0x01:							//BASS+
							if( SYS_power_flag )
							{
								Amplifier_BASS_A();									
							}
						break;
							
						case 0x02:							//BASS-
							if( SYS_power_flag )
							{
								Amplifier_BASS_B();	
							}
						break;
						
						case 0x03:							//TREBLE+
							if( SYS_power_flag )
							{
								Amplifier_TREBLE_A();	
							}	
						break;
						
						case 0x04:							//TREBLE-
							if( SYS_power_flag )
							{
								Amplifier_TREBLE_B();
							}
						break;
							
						case 0x0c:							//BLUETOOTH
							if(( SYS_power_flag )&&(Channel1==0))
							{
								if(disp>2)
								{
									BT_patch();
//									LED_R = 1;LED_G = 1;LED_B = 1;
//									CLK_SysTickDelay(40000);								
//									LED_B = 0;
								}
							}
							
						case 0x12:							//VOL+
							if( SYS_power_flag )
							{
								Amplifier_VOL_A();
							}
						break;

						case 0x13:							//VOL-
							if( SYS_power_flag )
							{
								Amplifier_VOL_B();
							}
						break;
							
//						case 0x15:
//							if( SYS_power_flag && (disp>=0x15) )
//							{
//								_RST = 0;
//								treble_level = 0;
//								bass_level = 0;
//								LED_Flag = 0;
//								bass_adjust(bass_level);
//								treble_adjust(treble_level);
//								_RST = 1;
//							}
						
						default:
							break;
			}
			KEY_data = 0x00;
		}		
	}
}
#if 0
void IR_test_task(void)
{
	uint8_t p[2];
	p[0] = 31;
	if(KEY_data!=0x15)
		LED_Flag = 0;
				if(disp_flag == 1)
                {
					switch(KEY_data)
					{
						case 0x01:							//BASS+
							if( SYS_power_flag )
							{
								Amplifier_BASS_A();							
							}
//							disp_flag=0;
						break;
							
						case 0x02:							//BASS-
							if( SYS_power_flag )
							{
								Amplifier_BASS_B();	
							}
//							disp_flag=0;
						break;
						
						case 0x03:							//TREBLE+
							if( SYS_power_flag )
							{
								Amplifier_TREBLE_A();						
							}	
//							disp_flag=0;
						break;
						
						case 0x04:							//TREBLE-
							if( SYS_power_flag )
							{
								Amplifier_TREBLE_B();	
							}
//							disp_flag=0;
						break;
						
						case 0x0a:							//ÔÝÊ±BLUETOOTHÌæ´úLINE IN
							if(disp==0)
							{
								p[1] = Channel[0] = 0;
								Channel_select(Channel);
//								if( SYS_power_flag )
//								{
//									_RST = 0;
//									_4052_A = 1;_4052_B = 0;
//									BT_POWER = 1;
//									LED_R = 1;LED_B = 0;LED_G = 1;
////									if(LED_R == 0){LED_R = ~LED_R;CLK_SysTickDelay(40000);LED_R = ~LED_R;}
////									if(LED_G == 0){LED_G = ~LED_G;CLK_SysTickDelay(40000);LED_G = ~LED_G;}
////									if(LED_B == 0){LED_B = ~LED_B;CLK_SysTickDelay(40000);LED_B = ~LED_B;}
////									CLK_SysTickDelay(40000);LED_B = 1;
////									CLK_SysTickDelay(40000);LED_B = 0;
//								}
								I2C_SW_Send(_24c02_addr,p,2);
//								CLK_SysTickDelay(9000);
//								_RST = 1;
							}
//						disp_flag=0;
						break;
						
						case 0x0b:							//AUX IN
							if(disp==0)
							{
								p[1] = Channel[0] = 1;
								Channel_select(Channel);
//								if(SYS_power_flag)
//								{
//									_RST = 0;
//									_4052_A = 0;_4052_B = 1;
//									BT_POWER = 0;
//									LED_R = 1;LED_B = 1;LED_G = 0;
//	//								CLK_SysTickDelay(40000);LED_G = 1;
//	//								CLK_SysTickDelay(40000);LED_G = 0;
//	//								if(LED_R == 0){LED_R = ~LED_R;CLK_SysTickDelay(40000);LED_R = ~LED_R;}
//	//								if(LED_G == 0){LED_G = ~LED_G;CLK_SysTickDelay(40000);LED_G = ~LED_G;}
//	//								if(LED_B == 0){LED_B = ~LED_B;CLK_SysTickDelay(40000);LED_B = ~LED_B;}
//								}
								I2C_SW_Send(_24c02_addr,p,2);
//								CLK_SysTickDelay(9000);
//								_RST = 1;
							}
//							disp_flag=0;
						break;
												
						case 0x0c:							//BLUETOOTH
//							_4052_A = 1;_4052_B = 0;
							if(( SYS_power_flag )&&(Channel[0]==0))
							{
								if(disp>2)
								{
									BT_patch();
								}
								else 
								{
									BT_Play_Pause();
								}
//								if(LED_R == 0){LED_R = ~LED_R;CLK_SysTickDelay(40000);LED_R = ~LED_R;}
//								if(LED_G == 0){LED_G = ~LED_G;CLK_SysTickDelay(40000);LED_G = ~LED_G;}
								LED_R = 1;LED_G = 1;
								CLK_SysTickDelay(40000);LED_B = 1;
								CLK_SysTickDelay(40000);LED_B = 0;
//								if(LED_B == 0){LED_B = ~LED_B;CLK_SysTickDelay(40000);LED_B = ~LED_B;}								
							}
//							disp_flag=0;
						break;

						case 0x0d:							//OPTICAL
//							disp_flag=0;
						break;
						
						case 0x0E:							//COAXIAL
//							disp_flag=0;
						break;

						case 0x12:							//VOL+
							disp_flag=0;
							if( SYS_power_flag )
							{
								Amplifier_VOL_A();			
							}
						break;

						case 0x13:							//VOL-
							disp_flag=0;
//							n++;
							if( SYS_power_flag )
							{
								Amplifier_VOL_B();
							}
						break;

						case 0x14:							//ON-OFF
							if(disp==0)
							POWER_FLAG = ~POWER_FLAG;
							
						break;

						case 0x15:							//MUTE
							if( SYS_power_flag && (disp==0) )
							{
								_RST = ~_RST;
								LED_Flag = ~LED_Flag;
								if(LED_Flag==0)
								{
									if(Channel[0])
										LED_G = 0;
									else if((BT_DET)&&(Channel[0]==0))
										LED_B = 0;
								}
							}
							if( SYS_power_flag && (disp>=0x15) )
							{
								treble_level = 0;
								bass_level = 0;
								LED_Flag = 0;
								bass_adjust(bass_level);
								treble_adjust(treble_level);
							}
//							disp_flag=0;
						break;

						case 0x18:							//HDMI
//							disp_flag=0;
						break;
						default:
							irwork = IDLE;
							break;
					}
				}
		disp_flag=0;
}
#endif
