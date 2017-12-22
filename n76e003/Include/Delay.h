#ifndef	__DELAY_H
#define	__DELAY_H

#if 0
void Delay10us(UINT16 u16CNT);
void Timer0_Delay1ms (UINT32 u32CNT);
void Timer1_Delay1ms (UINT32 u32CNT);
void Timer2_Delay1ms (UINT32 u32CNT);
void Timer3_Delay1ms (UINT32 u32CNT);
void WakeUp_Timer_Delay25ms(UINT32 u32CNT);
#endif
void __delay_10ms( UINT16 u16CNT );


void Timer0_Delay100us(UINT32 u32CNT);
void Timer0_Delay1ms(UINT32 u32CNT);
void Timer1_Delay1ms(UINT32 u32CNT);
void Timer1_Delay10ms(UINT32 u32CNT);
void Timer2_Delay500us(UINT32 u32CNT);
void Timer3_Delay100ms(UINT32 u32CNT);

void Timer0_Delay40ms(UINT32 u32CNT);
void Timer3_Delay10us(UINT32 u32CNT);
#endif