dpint				ds	2					;用于中断
dpmain			ds	2					;用于主程序

;;===================================================================
;;
;;for ram0
;;
;;===================================================================
R0					ds	1
R1					ds	1
R2					ds	1
R3					ds	1
R4					ds	1
R5					ds	1
R6					ds	1
R7					ds	1

R_Flag			ds	1
B_64Hz 			EQU	0
B_128Hz 		EQU	1
B_256Hz 		EQU	2
B_8192Hz		EQU	3
B_2HzKey		EQU	4
B_RCAMode		EQU	7				;位置不能变

R_Flag1			ds	1
B_4KHz			EQU	0
B_MuteFlag	EQU	1

R_MainMode			ds	1
C_NormalMode		EQU	0
C_BTMode				EQU	1	
C_AuxMode				EQU	2
C_OpticalMode		EQU	3
R_ModeTemp			ds	1	
R_SetTimeFlag		ds	1	
C_NonSet				EQU	0
C_SetVolume			EQU	1
C_SetBass				EQU	2
C_SetTreble			EQU	3

;;========================================================================================
R_HalfSecond					ds	1

R_Volume							ds	1	
R_VolumeTemp					ds	1
R_VolumeTime					ds	1	
R_VolumeRamUpTime			ds	1
R_Bass								ds	1
R_BassTime						ds	1
R_Treble							ds	1
R_TrebleTime					ds	1

R_BackNormalTimeLo		ds	1	
R_BackNormalTimeHi		ds	1	

R_KeyminderBufferCol0	ds	1	
R_KeyminderBufferCol1	ds	1	
R_KeyminderBufferCol2	ds	1	
R_KeyminderBufferCol3	ds	1
R_KeyBuffer						ds	1	
R_KeyFlag							ds	1	
B_KeyAction						EQU	0	
B_IRKeyScan						EQU	1		
R_KeyTime							ds	1	

R_AuxSleepBaseTime		ds	1
R_AuxSleepSecond			ds	1
R_AuxSleepMinute			ds	1
R_AuxSleepCounter			ds	1
R_AuxSleepCounterTime	ds	1

R_OpticalSleepBaseTime		ds	1
R_OpticalSleepSecond			ds	1
R_OpticalSleepMinute			ds	1
R_OpticalSleepCounter			ds	1
R_OpticalSleepCounterTime	ds	1

R_BTSleepBaseTime			ds	1
R_BTSleepSecond				ds	1
R_BTSleepMinute				ds	1
R_BTSleepCounter			ds	1
R_BTSleepCounterTime	ds	1

;;=================================================================
;;
;;for ir variable
;;
;;=================================================================	
R_IRKeyTemp				ds	1
R_IRKeyBuffer			ds	1	

R_IRMode					ds	1
C_IRMode0					EQU	0
C_IRMode1					EQU	1
R_IRFlag					ds	1
B_IRBitLow				EQU	0
R_IRKeyStore			ds	1				
R_IRIntervalLo		ds	1
R_IRIntervalHi		ds	1
R_IRIIRTime				ds	1
R_IRBitTime				ds	1
R_IRBitLowTime		ds	1	
R_IRBitCounter		ds	1
R_IRBit0					ds	1
R_IRBit1					ds	1
R_IRBit2					ds	1
R_IRBit3					ds	1	

R_BTLedTime				ds	1
;;=======================================================================
;;
;;for coder variable
;;
;;=======================================================================	
R_CoderFlag				ds	1					;for time
B_CoderLFlag			EQU	0
B_CoderRFlag			EQU	1
B_WaitCoderH			EQU	2
	
R_CoderTurnL			ds	1
R_CoderTurnR			ds	1

R_CoderFlag1			ds	1					;for volume
B_CoderLFlag1			EQU	0
B_CoderRFlag1			EQU	1
B_WaitCoderH1			EQU	2
	
R_CoderTurnL1			ds	1
R_CoderTurnR1			ds	1

R_CoderFlag2			ds	1					;for bass
B_CoderLFlag2			EQU	0
B_CoderRFlag2			EQU	1
B_WaitCoderH2			EQU	2
	
R_CoderTurnL2			ds	1
R_CoderTurnR2			ds	1

R_CoderFlag3			ds	1					;for treble
B_CoderLFlag3			EQU	0
B_CoderRFlag3			EQU	1
B_WaitCoderH3			EQU	2
	
R_CoderTurnL3			ds	1
R_CoderTurnR3			ds	1
;
;
;;
;;