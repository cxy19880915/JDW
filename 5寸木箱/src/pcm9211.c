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
	static unsigned char *p8Data;
		p8Data[0] = reg.reg_addr;
		p8Data[1] = reg.reg_value;
		I2C_SW_Send(PCM_Slave_Addr,p8Data,2);
}
/*#System RST Control*/
void pcm9211_RST(void)
{
//	pcm_reg[14].reg_addr = 0x40;
	pcm_reg[14].reg_value = 0x33;
	Transmit(pcm_reg[14]);
//	pcm_reg[14].reg_addr = 0x40;
	pcm_reg[14].reg_value = 0xc0;
	Transmit(pcm_reg[14]);
}

void pcm9211_init(void)
{
	pcm_reg[0].reg_addr = 0x20;pcm_reg[0].reg_value = 0x00;
	pcm_reg[1].reg_addr = 0x21;pcm_reg[1].reg_value = 0x00;
	pcm_reg[2].reg_addr = 0x22;pcm_reg[2].reg_value = 0x01;
	pcm_reg[3].reg_addr = 0x23;pcm_reg[3].reg_value = 0x04;
	pcm_reg[4].reg_addr = 0x24;pcm_reg[4].reg_value = 0x00;
	pcm_reg[5].reg_addr = 0x26;pcm_reg[5].reg_value = 0x81;
	pcm_reg[6].reg_addr = 0x27;pcm_reg[6].reg_value = 0x00;
	pcm_reg[7].reg_addr = 0x2f;pcm_reg[7].reg_value = 0x04;
	pcm_reg[8].reg_addr = 0x30;pcm_reg[8].reg_value = 0x02;
	pcm_reg[9].reg_addr = 0x31;pcm_reg[9].reg_value = 0x1a;
	pcm_reg[10].reg_addr = 0x32;pcm_reg[10].reg_value = 0x22;
	pcm_reg[11].reg_addr = 0x33;pcm_reg[11].reg_value = 0x22;
	pcm_reg[12].reg_addr = 0x34;pcm_reg[12].reg_value = 0x01;
	pcm_reg[13].reg_addr = 0x37;pcm_reg[13].reg_value = 0x00;
	pcm_reg[14].reg_addr = 0x38;pcm_reg[14].reg_value = 0x01;
	pcm_reg[15].reg_addr = 0x40;
	pcm_reg[16].reg_addr = 0x6a;pcm_reg[16].reg_value = 0x00;
	pcm_reg[17].reg_addr = 0x6b;pcm_reg[17].reg_value = 0x11;
	pcm_reg[18].reg_addr = 0x6d;pcm_reg[18].reg_value = 0x00;
	Transmit(pcm_reg[9]);
	Transmit(pcm_reg[11]);
	Transmit(pcm_reg[0]);
	Transmit(pcm_reg[4]);
	Transmit(pcm_reg[5]);
	Transmit(pcm_reg[11]);
	Transmit(pcm_reg[1]);
	Transmit(pcm_reg[2]);
	Transmit(pcm_reg[3]);
	Transmit(pcm_reg[6]);
	Transmit(pcm_reg[7]);
	Transmit(pcm_reg[8]);
	Transmit(pcm_reg[10]);
	Transmit(pcm_reg[12]);
	Transmit(pcm_reg[13]);
	Transmit(pcm_reg[14]);
	Transmit(pcm_reg[16]);
	Transmit(pcm_reg[17]);
	Transmit(pcm_reg[18]);
}

