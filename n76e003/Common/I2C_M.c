/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2017 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Nuvoton Technoledge Corp. 
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Apr/29/2017
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: N76E003 I2C master mode demo code, the Slave address = 0xA4
//
//   ____________            _____________ 
//  |            |   SDA    |             |
//  |            |<-------->|             |
//  |            |          |             |
//  |N76E003(M) |          | N76E003(S) |
//  |(I2C_Master)|          | (I2C_Slave) |
//  |            |   SCL    |             |
//  |            |--------->|             |
//  |____________|          |_____________|
//
//  The protocol of I2C is same the "24LC64"
//***********************************************************************************************************

#include "I2C_M.h"


#define I2C_CLOCK               13
//#define EEPROM_SLA              0xA4
#define EEPROM_WR               0
#define EEPROM_RD               1
#define ERROR_CODE              0x78
#define PAGE_SIZE               32
#define	SDA_I2C									SDA
#define	SCL_I2C									SCL
#if 1

//========================================================================================================
void	delay(void)
{
		UINT16 i = 0;
		for(i=0;i<50;i++);
//		Timer1_Delay10us(1);
}
//========================================================================================================
void I2C_Error(void)
{
//    P3 = I2STAT;
//    P3 = ERROR_CODE;
    while (1)P12 = 0;    
}

void Init_I2C(void)
{
		SCL_I2C = 1;                                //set SDA and SCL pins high
		delay();
    SDA_I2C = 1;
		delay();
}
//========================================================================================================
void start_I2C(void)
{
		SDA_I2C = 1;
		delay();
		SCL_I2C = 1; 
		delay();
		SDA_I2C = 0;
		delay();
}

//========================================================================================================
void respons_I2C(void)
{
		UINT16 i = 0;
		SCL_I2C = 1;
		delay();
		while((SDA_I2C == 1)&&(i<50000))
		{
				i++;
				if(i==5000)
				{
						I2C_Error();
				}
		}
		SCL_I2C = 0;
		delay();
}

//========================================================================================================
void stop_I2C(void)
{
		SDA_I2C = 0;
		delay();
		SCL_I2C = 1;
		delay();
		SDA_I2C = 1;
		delay();
}

void writebyte_I2C(UINT8 data_I2C)
{
		UINT8 i,temp;
		temp = data_I2C;
		for(i = 0;i < 8;i++)
		{
				SCL_I2C = 0;
				delay();
				if(temp&0x80)
				{
						SDA_I2C = 1;
				}
				else
				{
						SDA_I2C = 0;
				}
				temp = temp << 1;
				delay();
				SCL_I2C = 1;
				delay();
		}
		SCL_I2C = 0;
		delay();
		SDA_I2C = 1;
		delay();
}

UINT8 readbyte_I2C(bit SDA_I2C,bit SCL_I2C)
{
		UINT8 i,k;
		SCL_I2C = 0;
		delay();
		SDA_I2C = 1;
		delay();
		for(i = 0;i < 8;i++)
		{
				SCL_I2C = 1;
				delay();
				k = (k << 1)| SDA_I2C;
				SCL_I2C = 0;
				delay();
		}
		delay();
		return k;
}

void I2C_Write_Command(UINT8 u8Address, UINT8* p8Data, UINT32 u32ByteSize)
{
		UINT8 i=0;
		start_I2C();
		writebyte_I2C(u8Address|EEPROM_WR);
		respons_I2C();
		for(i=0;i<u32ByteSize;i++)
		{
				writebyte_I2C(*p8Data++);
				respons_I2C();
		}
		stop_I2C();	
}
#endif
#if 0
//========================================================================================================
void Init_I2C(void)
{
		P13_OpenDrain_Mode;					// Modify SCL pin to Open drain mode. don't forget the pull high resister in circuit
		P14_OpenDrain_Mode;					// Modify SDA pin to Open drain mode. don't forget the pull high resister in circuit
//		SDA = 1;
//		SCL = 1;
    /* Set I2C clock rate */
    I2CLK = I2C_CLOCK; 

    /* Enable I2C */
    set_I2CEN;                                   
}
//========================================================================================================
void I2C_Error(void)
{
				set_STO;
				clr_SI;
				if(SI)
				{
						clr_I2CEN;
						set_I2CEN;
						clr_SI;
						clr_I2CEN;		
				} 
//    P3 = I2STAT;
//    P3 = ERROR_CODE;
//    while (1);    
}
//========================================================================================================
void I2C_Write_Command(UINT8 u8Address, UINT8* p8Data, UINT32 u32ByteSize)
{
	UINT32 u32count = 0;
	  /* Step1 */
		set_STA;                                /* Send Start bit to I2C EEPROM */         
    clr_SI;
    while (!SI);
    if (I2STAT != 0x08)                     /* 0x08:  A START condition has been transmitted*/
        I2C_Error();
		
		/* Step2 */
		clr_STA;                                    //STA=0
		I2DAT = (u8Address | EEPROM_WR);
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x18)              
        I2C_Error();
		
		/* Step3 */
    while(u32count<u32ByteSize)
    {
        I2DAT = *(p8Data+u32count++);
        clr_SI;
        while (!SI);                            //Check SI set or not
        if (I2STAT != 0x28)              
            I2C_Error();    
    }
		
		/* Step4 */
		set_STO;                            /* Set I2C STOP Control Bit */
    clr_SI;
		while (STO);
}
//========================================================================================================
UINT8 I2C_Receive_Command(UINT8 u8Address, UINT8* p8Data, UINT32 u32ByteSize)
{
	UINT8 xdata u8DAT[256];
	UINT32 u32count = 0;
	  /* Step1 */
		set_STA;                                /* Send Start bit to I2C EEPROM */         
    clr_SI;
    while (!SI);
    if (I2STAT != 0x08)                     /* 0x08:  A START condition has been transmitted*/
        I2C_Error();
		
		/* Step2 */
    clr_STA;                                    //STA=0
    I2DAT = (u8Address | EEPROM_WR);
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x18)              
        I2C_Error();
		
		/* Step3 */
    while(u32count<2)
    {
        I2DAT = *(p8Data+u32count++);
        clr_SI;
        while (!SI);                            //Check SI set or not
        if (I2STAT != 0x28)              
            I2C_Error();    
    }
		
		/* Step4 */
    set_STA;                                /* Repeated START */
    clr_SI; 
    while (!SI);
    if (I2STAT != 0x10)                     /* 0x10: A repeated START condition has been transmitted */
				I2C_Error(); 
		
		/* Step5 */
    clr_STA;                                    //STA=0
    I2DAT = (u8Address | EEPROM_RD);
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x40)              
        I2C_Error();
		
		for(u32count=0;u32count<u32ByteSize;u32count++)
		{
        set_AA;
        clr_SI;        
        while (!SI);                            //Check SI set or not

        if (I2STAT != 0x50)              
            I2C_Error();	
				u8DAT[u32count] = I2DAT;
		}
		
		/* Step6 */
    clr_AA;
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x58)              
        I2C_Error();

    /* Step7 */
    set_STO;
    clr_SI;
    while (STO);                                /* Check STOP signal */ 
		return	u8DAT;
}
#endif
#if 0
//========================================================================================================
void I2C_Process(UINT8 u8DAT)
{
    UINT32 u32Count;

//--------------------------------------------------------------------------------------------
//----  Page Write----------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
    /* Step1 */
    set_STA;                                    /* Send Start bit to I2C EEPROM */
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x08)                         //Check status value after every step
        I2C_Error();
    
    /* Step2 */
    clr_STA;                                    //STA=0
    I2DAT = (EEPROM_SLA | EEPROM_WR);
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x18)              
        I2C_Error();

    /* Step3 */
    I2DAT = 0x00;                               //address high for I2C EEPROM
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x28)              
        I2C_Error();
                    
    /* Step4 */
    I2DAT = 0x00;                               //address low for I2C EEPROM
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x28)              
        I2C_Error();

    /* Step5 */
    for (u32Count = 0; u32Count < PAGE_SIZE; u32Count++)
    {
        I2DAT = u8DAT;
        clr_SI;
        while (!SI);                            //Check SI set or not
        if (I2STAT != 0x28)              
            I2C_Error();

        u8DAT = ~u8DAT;        
    }

//--------------------------------------------------------------------------------------------
//----  Waitting the ready for I2C write------------------------------------------------------
//--------------------------------------------------------------------------------------------
    /* Step6 */
    do{
        set_STO;
        clr_SI;
        
        set_STA;                                //Check if no ACK is returned by EEPROM, it is under timed-write cycle
        clr_SI;
        while (!SI);                            //Check SI set or not
        if (I2STAT != 0x08)                     //Check status value after every step
            I2C_Error();

        clr_STA;
        I2DAT = (EEPROM_SLA | EEPROM_WR);
        clr_SI;
        while (!SI);                            //Check SI set or not
    }while (I2STAT != 0x18);
    
    /* Step7 */
    set_STO;
    clr_SI;
    while (STO);                                /* Check STOP signal */
//--------------------------------------------------------------------------------------------
//----  Page Read ----------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
    /* Step8 */
    set_STA;
    clr_SI;          
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x08)                         //Check status value after every step
        I2C_Error();

    /* Step9 */
    I2DAT = (EEPROM_SLA | EEPROM_WR);
    clr_STA;
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x18)              
        I2C_Error();

    /* Step10 */
    I2DAT = 0x00;                               //address high for I2C EEPROM
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x28)              
        I2C_Error();

    /* Step11 */
    I2DAT = 0x00;                               //address low for I2C EEPROM
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x28)              
        I2C_Error();

    /* Step12 */
    /* Repeated START */
    set_STA;                       
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x10)                         //Check status value after every step
        I2C_Error();
    
    /* Step13 */
    clr_STA;                                    //STA needs to be cleared after START codition is generated
    I2DAT = (EEPROM_SLA | EEPROM_RD);
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x40)              
        I2C_Error();
    
    /* Step14 */
    for (u32Count = 0; u32Count <PAGE_SIZE-1; u32Count++)
    {
        set_AA;
        clr_SI;        
        while (!SI);                            //Check SI set or not

        if (I2STAT != 0x50)              
            I2C_Error();
        
        if (I2DAT != u8DAT)             
            I2C_Error();
        u8DAT = ~u8DAT; 
    } 
    
    /* Step15 */
    clr_AA;
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x58)              
        I2C_Error();

    /* Step16 */
    set_STO;
    clr_SI;
    while (STO);                                /* Check STOP signal */ 
}
//========================================================================================================
//void main(void)
//{
//    /* Note
//       MCU power on system clock is HIRC (22.1184MHz), so Fsys = 22.1184MHz
//    */
//    
//    Set_All_GPIO_Quasi_Mode;	
//    Init_I2C();                                 //initial I2C circuit
//    I2C_Process(0x55);                          /* I2C Master will send 0x55,0xAA,.... to slave */
//    
//    P0 = 0x00;
//    P3 = 0x00;
//    
//    while (1);
///* =================== */
//}
#endif

