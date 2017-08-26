R_StandbyCtrl		EQU	P2
B_StandbyCtrl		EQU	7
R_MuteCtrl			EQU	P3
B_MuteCtrl			EQU	0

R_TAS5713Power	EQU	P5
B_TAS5713Power	EQU	1
R_TAS5713Reset	EQU	P5
B_TAS5713Reset	EQU	1

R_IRPin					EQU	P1
B_IRPin					EQU	1

R_BTPowerCtrl		EQU	P0
B_BTPowerCtrl		EQU	3

R_BTLedCtrl					EQU	P1
B_BTLedCtrl					EQU	5
R_AuxLedCtrl				EQU	P1
B_AuxLedCtrl				EQU	4
R_OpticalLedCtrl		EQU	P1
B_OpticalLedCtrl		EQU	2

R_BTSleepDetect					EQU	P0
B_BTSleepDetect					EQU	0
C_AuxSleepChannelL			EQU	02
C_AuxSleepChannelR			EQU	02
C_OpticalSleepChannelL	EQU	02
C_OpticalSleepChannelR	EQU	02

C_ADC_KeyChannel				EQU	000 
R_KeyIO0								EQU	P0
B_KeyIO0								EQU	5
;;=======================================================================
;;
;;
;;
;;=======================================================================
R_24C02SCL				EQU	P2
B_24C02SCL				EQU	5
R_24C02SDAO				EQU	P2
B_24C02SDAO				EQU	6
R_24C02SDAI				EQU	P2
B_24C02SDAI				EQU	6
R_24C02DAI_O			EQU	P2CONH
C_24C02DAIOMask		EQU	11001111B
C_24C02DAIOInput	EQU	00000000B
C_24C02DAIOOutput	EQU	00010000B			

;;=======================================================================
;;
;;for amplify IO
;;
;;=======================================================================		
R_D2AudioCK						EQU	P2
B_D2AudioCK						EQU	5
R_D2AudioDAO					EQU	P2
B_D2AudioDAO					EQU	6
R_D2AudioDAI					EQU	P2
B_D2AudioDAI					EQU	6		
R_D2AudioDAIO					EQU	P2CONH
C_D2AudioDAIOMask			EQU	11001111B
C_D2AudioDAIOInput		EQU	00000000B
C_D2AudioDAIOOutput		EQU	00010000B

R_TC4052A						EQU	P1
B_TC4052A						EQU	6
R_TC4052B						EQU	P1
B_TC4052B						EQU	7
R_MixCtrl						EQU	P0
B_MixCtrl						EQU	4
;;=======================================================================
;;
;;for volume coder IO
;;
;;=======================================================================				
R_CoderLPin1			EQU	P5												;for volume
B_CoderLPin1			EQU	2	
R_CoderRPin1			EQU	P5				
B_CoderRPin1			EQU	2

R_CoderLPin2			EQU	P5												;for bass
B_CoderLPin2			EQU	2	
R_CoderRPin2			EQU	P5				
B_CoderRPin2			EQU	2

R_CoderLPin3			EQU	P5												;for treble
B_CoderLPin3			EQU	2	
R_CoderRPin3			EQU	P5				
B_CoderRPin3			EQU	2

;;=======================================================================
;;
;;for set coder IO
;;
;;=======================================================================		
;R_CoderLPin		EQU	P5																			;for set
;B_CoderLPin		EQU	2			
;R_CoderRPin		EQU	P5				
;B_CoderRPin		EQU	2	
;
;
;;
;;