;;==================================================================================================
;;
;;	include	head files
;;
;;==================================================================================================
	ORG	0000H																	
									
	include	"MC81F4416.h"	
	include	"main.h"	
	include	"io.h"	
	include	"at24c02.h"
	include	"volume.h"
	include	"power.h"
	include	"ir.h"

;;==================================================================================================
;;
;;	Power	On Initial
;;
;;==================================================================================================

	ORG	0C000H

Program_Start:
	di																			;disable all interrupt	
	ldx	#0FFh																;stack	point	initialize
	txsp				
									
	ldm	CKCTLR,#00011110B										;Basic Interval Timer Off,	bit4=0:disable watchdog
	call	!WDTC

	clrg																		
	ldx	#00
	lda	#00
L_ClearRamPage0_Loop:
	sta	{x}+																;page0	(000h~08Fh)	clear
	cmpx	#0B0H
	bne	L_ClearRamPage0_Loop
	ldm	RPR,#0000_0001B											;Page	1	00~FF
	setg
	ldx	#00
	lda	#00
L_ClearRamPage1_Loop:
	sta	{x}+																;	page1	(000h~0fFh)	clear
	cmpx	#00
	bne	L_ClearRamPage1_Loop
	clrg
	ldm	RPR,#0000_0010b											;Page	2	00~6F
	setg
	ldx	#00
	lda	#00
L_ClearRamPage2_Loop:
	sta	{x}+																;	page2	(000h~06Fh)	clear
	cmpx	#050h
	bne	L_ClearRamPage2_Loop
	clrg
	ldm	RPR,#0000_0000b											;lcd ram

L_Main:
	call	F_InitialMC81F4416
	call	F_InitialSystem

Main_Loop:
	call	WDTC
	bbc	R_Flag.B_128Hz,main_loop
	clr1	R_Flag.B_128Hz
	not1	R_Flag.B_64Hz
	bbc	R_Flag.B_64Hz,main_iPod_loop
	
	call	F_CheckBackNormalTime
	
	call	F_CheckTime

	call	F_CheckVolume	
	call	F_CheckBass
	call	F_CheckTreble
	call	F_VolumeRamUp

	call	F_DisplayLcd
	
	call	F_CheckAuxSleep
	call	F_CheckOpticalSleep
	call	F_CheckBTSleep
	
	call	F_KeyBoardScan
	call	F_KeyDecoder
	jmp	Main_Loop
	
main_iPod_loop:
	call	F_CheckAuxSleep
	call	F_CheckOpticalSleep
	call	F_CheckBTSleep
	jmp	Main_Loop	
	
;;==================================================================================================
;;
;;Module Name:	F_Timer0_INT
;;
;;Describe:			2Hz Interrupt
;;
;;==================================================================================================
F_Timer0_INT:
	clr1	T0MIR
	clr1	T0MIF
	set1	R_Flag.B_2HzKey
	inc	R_HalfSecond
	push	A
	
	bbc	R_Flag1.B_MuteFlag,L_Timer0_INT_Exit
	call	F_PowerOffLed
	bbs	R_HalfSecond.0,L_Timer0_INT_Exit
	call	F_DisplayLed
L_Timer0_INT_Exit:		
	pop	A	
	reti																

;;==================================================================================================
;;
;;Module Name:	F_Timer3_INT
;;
;;Describe:			8192Hz Interrupt
;;
;;==================================================================================================
F_Timer3_INT:
			push	A																												
			push	Y
			push	X
			clr1	T3MIR
			clr1	T3MIF
			set1	R_Flag.B_8192Hz
			not1	R_Flag1.B_4KHz
			bbc	R_Flag1.B_4KHz,L_IRInterrupt	

L_IRInterrupt:	
			call	F_ReceiveIR
;			call	F_CoderProcess
			call	F_CoderProcess1
			call	F_CoderProcess2
			call	F_CoderProcess3

L_Timer3_INT:			
			pop		X									
			pop		Y
			pop		A															
			reti																


;;==================================================================================================
;;
;;Module Name:	F_Timer2_INT
;;
;;Describe:			256Hz Interrupt
;;
;;==================================================================================================
F_Timer2_INT:
			push	A		
			clr1	T2MIR			
			clr1	T2MIF										
			not1	R_Flag.B_256Hz
			bbc	R_Flag.B_256Hz,L_256HzTimer
L_128HzTimer:			
			set1	R_Flag.B_128Hz	
			call	F_DisplayBTLed

L_256HzTimer:			
L_Timer2_INT:										
			pop		A															
			reti																								

;;==================================================================================================
;;
;;	Include Programming file
;;
;;==================================================================================================
	include	"MC81F4416.asm"
	include	"key.asm"
	include	"scan.asm"
	include	"at24c02.asm"
	include	"time.asm"
	include	"power.asm"
	include	"ir.asm"
	include	"coder1.asm"
	include	"coder2.asm"
	include	"coder3.asm"
	include	"volume.asm"
	include	"tas5713.asm"
	include	"led.asm"
	include	"bt.asm"
	include	"optical.asm"

	include	"key.tab"
	include	"tas5713.tab"

;;==================================================================================================
;;
;;	Interrupt	Vector Table
;;
;;==================================================================================================
No_Interrupt:
	reti

	ORG		0FFE0H
																					
	dw		No_Interrupt											;00	*WT/WTD	Int				FFE0
	dw		No_Interrupt											;01	BIT	Int						FFE2
	dw		F_Timer3_INT											;02	ADC/I2C	Int				FFE4
	dw		F_Timer2_INT											;03	Timer3	Int				FFE6
	dw		No_Interrupt											;04	Timer2	Int				FFE8
	dw		F_Timer0_INT											;05	Timer1	Int				FFEA
	dw		No_Interrupt											;06	Timer0	Int				FFEC
	dw		No_Interrupt											;07	*SPI		Int				FFEE
	dw		No_Interrupt											;08	*Not Used					FFF0
	dw		No_Interrupt											;09	Uart0_Tx_Rx	Int		FFF2
	dw		No_Interrupt											;10	*External	Int	3		FFF4
	dw		No_Interrupt											;11	*External	Int	2		FFF6
	dw		No_Interrupt											;12	*External	Int	1		FFF8
	dw		No_Interrupt											;13	*External	Int	0		FFFA
	dw		No_Interrupt											;14	*Not Used					FFFC
	dw		Program_start											;15	*Reset (NMI)			FFFE

;;==================================================================================================
;;	end	of Main.asm
;
;
;;
;;