#define	PCM9211_GLOBALS
#include "pcm9211.h"

typedef struct PCM9211_REG
{
	unsigned char	reg_addr;
	unsigned char	reg_value;
}PCM9211_REG;

PCM9211_REG	pcm_reg[500] = {0};

static void Transmit(PCM9211_REG reg)
{
	static unsigned char p8Data[2];
		p8Data[0] = reg.reg_addr;
		p8Data[1] = reg.reg_value;
		I2C_SW_Send(PCM_Slave_Addr,p8Data,2);
}
/*#System RST Control*/
void pcm9211_RST(void)
{
	#if 1
	pcm_reg[14].reg_addr = 0x40;
	pcm_reg[14].reg_value = 0x33;
	Transmit(pcm_reg[14]);
//	pcm_reg[14].reg_addr = 0x40;
	pcm_reg[14].reg_value = 0xc0;
	Transmit(pcm_reg[14]);
	#endif
}

void pcm9211_InputMode(unsigned char n)
{
	pcm_reg[12].reg_addr = 0x34;
	pcm_reg[12].reg_value = n;
	Transmit(pcm_reg[12]);
}

void pcm9211_init(void)
{

/**#System RST Control
	*/
/**#XTI Source, Clock (SCK/BCK/LRCK) Frequency Setting
	*# XTI CLK source 12.288 and BCK 3.072, LRCK 48k = XTI/512
	*/
	pcm_reg[9].reg_addr = 0x31;pcm_reg[9].reg_value = 0x1a;
	Transmit(pcm_reg[9]);
	pcm_reg[11].reg_addr = 0x33;pcm_reg[11].reg_value = 0x22;
	Transmit(pcm_reg[11]);
	pcm_reg[0].reg_addr = 0x20;pcm_reg[0].reg_value = 0x00;
	Transmit(pcm_reg[0]);
	pcm_reg[4].reg_addr = 0x24;pcm_reg[4].reg_value = 0x00;
	Transmit(pcm_reg[4]);
/**#ADC clock source is chosen by REG42
	*/
	pcm_reg[5].reg_addr = 0x26;pcm_reg[5].reg_value = 0x81;
	Transmit(pcm_reg[5]);
/**#XTI Source, Secondary Bit/LR Clock (SBCK/SLRCK) Frequency Setting
	*/
	pcm_reg[11].reg_addr = 0x33;pcm_reg[11].reg_value = 0x22;
	Transmit(pcm_reg[11]);
/**#-------------------------------Start DIR settings----------------
	*#REG. 21h, DIR Receivable Incoming Biphase's Sampling Frequency Range Setting
	*/
	pcm_reg[1].reg_addr = 0x21;pcm_reg[1].reg_value = 0x00;
	Transmit(pcm_reg[1]);
	//#REG. 22h, DIR CLKSTP and VOUT delay
	pcm_reg[2].reg_addr = 0x22;pcm_reg[2].reg_value = 0x01;
	Transmit(pcm_reg[2]);
	//#REG. 23h, DIR OCS start up wait time and Process for Parity Error Detection and ERROR Release Wait Time Setting
	pcm_reg[3].reg_addr = 0x23;pcm_reg[3].reg_value = 0x04;
	Transmit(pcm_reg[3]);
	//# REG 27h DIR Acceptable fs Range Setting & Mask
	pcm_reg[6].reg_addr = 0x27;pcm_reg[6].reg_value = 0x00;
	Transmit(pcm_reg[6]);
	//# REG 2Fh, DIR Output Data Format, 24bit I2S mode
	pcm_reg[7].reg_addr = 0x2f;pcm_reg[7].reg_value = 0x04;
	Transmit(pcm_reg[7]);
	//# REG. 30h, DIR Recovered System Clock (SCK) Ratio Setting
	pcm_reg[8].reg_addr = 0x30;pcm_reg[8].reg_value = 0x02;
	Transmit(pcm_reg[8]);
	//#REG. 32h, DIR Source, Secondary Bit/LR Clock (SBCK/SLRCK) Frequency Setting
	pcm_reg[10].reg_addr = 0x32;pcm_reg[10].reg_value = 0x22;
	Transmit(pcm_reg[10]);
	//#REG 34h DIR Input Biphase Signal Source Select and RXIN01 Coaxial Amplifier
	//#--PWR up amplifier, select RXIN1
//	pcm_reg[12].reg_addr = 0x34;pcm_reg[12].reg_value = 0xc3;
//	Transmit(pcm_reg[12]);
	//#REG. 37h, Port Sampling Frequency Calculator Measurement Target Setting, Cal and DIR Fs
	pcm_reg[13].reg_addr = 0x37;pcm_reg[13].reg_value = 0x00;
	Transmit(pcm_reg[13]);
	//#------------------------------- End DIR settings---------------
/**#---------------------------------Start  MainOutput Settings----------
	*#MainOutput
	*/
	//#REG. 6Ah, Main Output & AUXOUT Port Control
	pcm_reg[16].reg_addr = 0x6a;pcm_reg[16].reg_value = 0x00;
	Transmit(pcm_reg[16]);
	//#REG. 6Bh, Main Output Port (SCKO/BCK/LRCK/DOUT) Source Setting
	pcm_reg[17].reg_addr = 0x6b;pcm_reg[17].reg_value = 0x11;
	Transmit(pcm_reg[17]);
	//#REG. 6Dh, MPIO_B & Main Output Port Hi-Z Control
	pcm_reg[18].reg_addr = 0x6d;pcm_reg[18].reg_value = 0x00;
	Transmit(pcm_reg[18]);
	
	//#--------------------------------- End MainOutput settings-----
	
}

