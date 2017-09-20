
#include "FM12832R.h"






unsigned char XPOS;                     //�з���LCD����λ��ָ��
unsigned char YPOS;                     //�з���LCD����λ��ָ��

//sbit A0PIN  =P3^2;
//sbit RESPIN =P3^1;
//sbit SCLPIN =P3^3;
//sbit SIPIN  =P3^4;
//sbit CSPIN  =P3^0;
//sbit key    =P2^0;


//typedef	struct typFNT_GB16 GB;
/////////////////////////////////////////////////////////////////////////
// ������ģ��                                                          //
// ���ֿ�: ����16.dot ����ȡģ�¸�λ,��������:�����Ҵ��ϵ���         //
/////////////////////////////////////////////////////////////////////////
GB GB_16[] =          // ���ݱ�
{
"?", 0x10,0x10,0xD0,0xFF,0x90,0x18,0xF7,0x14,
      0x54,0x94,0x14,0x14,0xF6,0x04,0x00,0x00,
      0x04,0x03,0x00,0xFF,0x00,0x1D,0x13,0x11,
      0x15,0x19,0x51,0x91,0x7F,0x11,0x01,0x00,

"?", 0x04,0x04,0x04,0xC4,0x3F,0x04,0x04,0x04,
      0xE4,0x04,0x1F,0x84,0xC4,0x06,0x04,0x00,
      0x04,0x02,0x01,0xFF,0x00,0x20,0x10,0x08,
      0x3F,0x42,0x41,0x40,0x40,0x40,0x70,0x00,
	
"?", 0x40,0x42,0x44,0xCC,0x00,0x00,0xF1,0x91,
      0x95,0xF9,0x95,0x93,0xF9,0x10,0x00,0x00,
      0x00,0x40,0x20,0x1F,0x20,0x40,0xBF,0x84,
      0x84,0xBF,0x94,0xA4,0x9F,0xC0,0x40,0x00,

"?", 0x40,0x42,0x44,0xCC,0x00,0x04,0xE5,0xB6,
      0xAC,0xA4,0xA4,0xA6,0xF5,0x24,0x00,0x00,
      0x00,0x40,0x20,0x1F,0x20,0x40,0xBF,0xA4,
      0xA4,0xA4,0xA4,0xA4,0xBF,0xC0,0x40,0x00	
};

// ���ֱ�
// ͨ��

void Backlight(unsigned char ms)
{
	LCD_BL = 0;
	CLK_SysTickDelay(ms);
	LCD_BL = 1;
	CLK_SysTickDelay(200-ms);
}

//-------------------------------------------------------------------------------
//�ӳ�������:void transbyte(unsigned char d).
//����:��1�ֽ����ݵ�Һ����ʾ������.
//-------------------------------------------------------------------------------
void transbyte(unsigned char d)         //��1�ֽ����ݵ�Һ����ʾ�������ӳ���
{   unsigned char i;
    for(i=0;i<8;i++)
    {   if((d&0x80) == 0x80)
		{
			LCD_SDA = 1;
			CLK_SysTickDelay(_1us);
			LCD_SCL = 1;
			CLK_SysTickDelay(_1us);
			LCD_SCL = 0;
			CLK_SysTickDelay(_1us);
			LCD_SCL = 1;
		}
        else
		{
			LCD_SDA = 0;
			CLK_SysTickDelay(_1us);
			LCD_SCL = 1;
			CLK_SysTickDelay(_1us);
			LCD_SCL = 0;
			CLK_SysTickDelay(_1us);
			LCD_SCL = 1;			
		}
        d<<=1;                          //�Ӹߵ���λ���ֽ�λ���ݵ�Һ����ʾ������
    }
}


void WriteData(unsigned char d)
{
	LCD_A0 = 1;
	LCD_CSB = 1;
	LCD_CSB = 0;
	transbyte(d);
	LCD_CSB = 1;
}
//-------------------------------------------------------------------------------
//�ӳ�������:lcdwc(unsigned char c).
//����:��Һ����ʾ��������ָ��.
//-------------------------------------------------------------------------------
void WriteCommand(unsigned char c)
{
	LCD_A0 = 0;
	LCD_CSB = 1;
	LCD_CSB = 0;
	transbyte(c);
	LCD_CSB = 1;	
}

void lcdreset(void)                     //Һ����ʾ��������ʼ���ӳ���
{   
	LCD_RSTB = 0;
	CLK_SysTickDelay(_10ms);
	LCD_RSTB = 1;
	CLK_SysTickDelay(_10ms);
    LCD_COMMAND_WRITE(0xA2);                        //����LCD bias �Աȶ�
    CLK_SysTickDelay(_10ms);
    LCD_COMMAND_WRITE(0xA0);                        //����ADC select
    CLK_SysTickDelay(_10ms);
    LCD_COMMAND_WRITE(0xC8);                        //����COM����
    CLK_SysTickDelay(_10ms);
	LCD_COMMAND_WRITE(0x24);							//��ѹ�ڲ��������
    CLK_SysTickDelay(_10ms);
	LCD_COMMAND_WRITE(0x81);							//��ѹ���� ��������
    CLK_SysTickDelay(_10ms);
	LCD_COMMAND_WRITE(0x03);							//
    CLK_SysTickDelay(_10ms);
	LCD_COMMAND_WRITE(0x29);
    CLK_SysTickDelay(_10ms);
	LCD_COMMAND_WRITE(0x2B);
    CLK_SysTickDelay(_10ms);
//    WriteCommand(0x60);                        //������ʾ��ʼ��
//    CLK_SysTickDelay(_10ms);
    LCD_COMMAND_WRITE(0x2F);                        //���õ�Դ����ģʽ
    CLK_SysTickDelay(_10ms);
    LCD_COMMAND_WRITE(0xAF);                        //����ʾ
    CLK_SysTickDelay(_10ms);	
}

void disp_line()
{
	uint jj;	
	WriteCommand(0xb3);	//select page
	WriteCommand(0x10);		//set MSB
	WriteCommand(0x01);		//set LSB
	for(jj=0;jj<126;jj++)
	{
		WriteData(0x80);
	}
  
}

//-------------------------------------------------------------------------------
//�ӳ�������:void lcdpos(void).
//����:���������(XPOS,YPOS)λ�ö�Ӧ���ڲ�RAM��ַ.
//-------------------------------------------------------------------------------
void lcdpos(void)                       //���������(XPOS,YPOS)�ڲ�RAM��ַ���ӳ���
{  unsigned char Column;
   Column=XPOS+1;
   WriteCommand(0xB0|((YPOS/8)&0x7));          //ҳ��ַ����
   WriteCommand(0x10|(Column>>4));             //�еĸ���λ����
   WriteCommand(Column&0x0F);                  //�еĵ���λ����
}

//-------------------------------------------------------------------------------
//�ӳ�������:void lcdfill(unsigned char d).
//����:������ʾd��ʾ���ֽ�����.
//-------------------------------------------------------------------------------
void lcdfill(unsigned char d)           //������ʾd������ֽ������ӳ���
{   unsigned char j;
    for(YPOS=0;YPOS<64;YPOS+=8)         //8ҳ
    {   
		LCD_DISP_PAGE(YPOS/8);
		LCD_DISP_FIRST_COL(0);
        for(j=0;j<128;j++)              //128��
            LCD_DISP_DATA_WRITE(d);                   //��ͼ������
    }
}

//-------------------------------------------------------------------------------
//�ӳ�������:void setlcdvoltage(unsigned char vol)
//����:����LCD��ѹ����������ʾ�ĶԱȶ�
//-------------------------------------------------------------------------------
void setlcdvoltage(unsigned char vol)   //LCD��ѹ����
{   WriteCommand(0x81);
    WriteCommand(vol&0x3F);                    //��ΧΪ0-63,�ϵ�Ĭ��ֵΪ32
}


void disp_2(uchar st)
{
	uint ii;
	uint jj;	
	for(ii=0;ii<32;ii += 8)
	{
		LCD_DISP_PAGE(ii/8);
		LCD_DISP_FIRST_ROW(0);
		LCD_DISP_FIRST_COL(0);
		if(st<64)
		{
			if((ii+8)%16==8)
			{
				for(jj=st;jj>0;jj--)
				{
					LCD_DISP_DATA_WRITE(GB_16[3-(jj-1)/16].Msk[15-(jj-1)%16]);
				}
			}
			if((ii+8)%16==0)
			{
				for(jj=st;jj>0;jj--)
				{
					LCD_DISP_DATA_WRITE(GB_16[3-(jj-1)/16].Msk[31-(jj-1)%16]);
				}
//				CLK_SysTickDelay(50000);
			}
		}
		else if(st==64)
		{
			if((ii+8)%16==8)
			for(jj=0;jj<st;jj++)
			{
				LCD_DISP_DATA_WRITE(GB_16[jj/16].Msk[jj%16]);
			}
			if((ii+8)%16==0)
			for(jj=0;jj<st;jj++)
			{
				LCD_DISP_DATA_WRITE(GB_16[jj/16].Msk[jj%16+16]);
			}
		}
		else if(st>64)
		{
			if((ii+8)%16==8)
			{
				for(jj=0;jj<st-64;jj++)LCD_DISP_DATA_WRITE(0);
				LCD_DISP_FIRST_COL(st-64);
				for(jj=0;jj<64;jj++)LCD_DISP_DATA_WRITE(GB_16[jj/16].Msk[jj%16]);
			}
			if((ii+8)%16==0)
			{
				for(jj=0;jj<st-64;jj++)LCD_DISP_DATA_WRITE(0);
				LCD_DISP_FIRST_COL(st-64);
				for(jj=0;jj<64;jj++)LCD_DISP_DATA_WRITE(GB_16[jj/16].Msk[jj%16+16]);
			}
		}
	}
  
}
//-----------------------------------------------------------------------------
void disp_21(uchar st)
{
	uint ii;
	uint jj;	
	for(ii=0;ii<64;ii += 8)
	{
		LCD_DISP_PAGE(ii/8);
		LCD_DISP_FIRST_ROW(0);
		LCD_DISP_FIRST_COL(st);
		if((ii+8)%16==8)
			for(jj=0;jj<128-st;jj++)
			{
				LCD_DISP_DATA_WRITE(GB_16[jj/16].Msk[jj%16]);
			}
		if((ii+8)%16==0)
			for(jj=0;jj<128-st;jj++)
			{
				LCD_DISP_DATA_WRITE(GB_16[jj/16].Msk[jj%16+16]);
			}
		
//		WriteCommand(0xb0+ii);	//select page
//		WriteCommand(0x10);		//set MSB
//		WriteCommand(0x00);		//set LSB
//		if(ii==0)
//		for(jj=0;jj<128;jj++)
////			WriteData(0x31);
//			if(jj<16)WriteData(GB_16->Msk[jj]);
//			else if(jj<32)WriteData(GB_16->Msk[jj+18]);
//			else if(jj<128)WriteData(0);
//		for(jj=0;jj<128;jj++)
//			if(jj<16)WriteData(GB_16->Msk[jj+16]);
//			else if(jj<32)WriteData(GB_16->Msk[jj+34]);
//			else if(jj<128)WriteData(0);
	}
  
}
 
//-----------------------------------------------------------------------------
void disp_3(void)
{
	uint ii;
	uint jj;	
	for(ii=0;ii<8;ii++)
	{
		LCD_DISP_PAGE(ii);
		LCD_DISP_FIRST_COL(0);
		for(jj=0;jj<128;jj++)
		{
			LCD_DISP_DATA_WRITE(0xcc);
			LCD_DISP_DATA_WRITE(0x00);
		}	
//		WriteCommand(0xb0+ii);	//select page
//		WriteCommand(0x10);		//set MSB
//		WriteCommand(0x00);		//set LSB
//		for(jj=0;jj<128;jj++)
//			WriteData(0);
	}
}


void disp_window(void)
{
	uint jj;	
//	WriteCommand(0xb0);	//select page
//	WriteCommand(0x10);		//set MSB
//	WriteCommand(0x01);		//set LSB
//	for(jj=0;jj<126;jj++)
//	{
//		WriteData(0x01);
//	}

//	WriteCommand(0xb3);	//select page
//	WriteCommand(0x10);		//set MSB
//	WriteCommand(0x01);		//set LSB
//	for(jj=0;jj<126;jj++)
//	{
//		WriteData(0x80);
//	}

	for(jj=0;jj<4;jj++)
	{
		WriteCommand(0xb0+jj);	//select page
		WriteCommand(0x10);		//set MSB
		WriteCommand(0x00);		//set LSB

		WriteData(0xff);
	}
  
//	for(jj=0;jj<4;jj++)
//	{
//		WriteCommand(0xb0+jj);	//select page
//		WriteCommand(0x17);		//set MSB
//		WriteCommand(0x0f);		//set LSB

//		WriteData(0xff);
//	}

}


// ���ֿ�: ����16.dot ����ȡģ�¸�λ,��������:�����Ҵ��ϵ���  init //
void LCD_INIT(void)
{
	LCD_RSTB = 0;
	CLK_SysTickDelay(_10ms);
	LCD_RSTB = 1;
	CLK_SysTickDelay(_10ms);
	LCD_DISP_SWITCH(1);		//0/1
	CLK_SysTickDelay(_10ms);
	LCD_DISP_FIRST_ROW(0);	//0-63
	CLK_SysTickDelay(_10ms);
	LCD_DISP_FIRST_COL(0);	//0-127
	CLK_SysTickDelay(_10ms);
	LCD_ADC_SELECT(0);		//0/1
	CLK_SysTickDelay(_10ms);
	LCD_VOLTAGE_SET(0);		//0/1	col
	CLK_SysTickDelay(_10ms);
//	LCD_DISP_ALL(1);		//0/1
//	CLK_SysTickDelay(_10ms);
	LCD_BIAS_SET(0);		//0/1
	CLK_SysTickDelay(_10ms);
	LCD_COM_OUTPUT(8);		//0/8	row
	CLK_SysTickDelay(_10ms);
	LCD_POWER_SET(7);		//0-7
	CLK_SysTickDelay(_10ms);
	LCD_VR_SET(4);			//0-7
	CLK_SysTickDelay(_10ms);
	LCD_VOLTAGE_ADJUST(1);	//0-63
	CLK_SysTickDelay(_10ms);
	LCD_LIGHT(0);			//0-3
	CLK_SysTickDelay(_10ms);
}
void LCD_DISP_SWITCH(uchar sw)
{
	LCD_COMMAND_WRITE(0xae | sw);	
}
void LCD_DISP_FIRST_ROW(uchar row)	//line (0-63)
{
	if(row<64)
	{
		LCD_COMMAND_WRITE( row | 0x40 );
	}
}
void LCD_DISP_PAGE(uchar page)	//page (0-7)
{
	if(page<8)
	{
		LCD_COMMAND_WRITE(0xb0 | page);
	}
}
void LCD_DISP_FIRST_COL(uchar col)	//col (0-127)
{
	LCD_COMMAND_WRITE(( col >>4 ) | 0x10);
	LCD_COMMAND_WRITE( col & 0x0f );
}
void LCD_DISP_STATE(void)
{
//	uchar d;
	LCD_A0 = 0;
	LCD_CSB = 0;
	LCD_CSB = 1;
//	d = recieve();
	LCD_CSB = 1;
}
void LCD_DISP_DATA_WRITE(uchar d)
{
	LCD_A0 = 1;
	LCD_CSB = 1;
	LCD_CSB = 0;
	transbyte(d);
	LCD_CSB = 1;
}
void LCD_COMMAND_WRITE(uchar d)
{
	LCD_A0 = 0;
	LCD_CSB = 1;
	LCD_CSB = 0;
	transbyte(d);
	LCD_CSB = 1;	
}
uchar LCD_DISP_DATA_READ(void)
{
	uchar d;
	LCD_A0 = 1;
	LCD_CSB = 0;
	LCD_CSB = 1;
//	d = recieve();
	return d;
}
void LCD_ADC_SELECT(uchar direction)
{
	LCD_COMMAND_WRITE(direction | 0xa0);
}
void LCD_VOLTAGE_SET(uchar v)
{
	LCD_COMMAND_WRITE(0xa6 | v);
}
void LCD_DISP_ALL(uchar all)
{
	LCD_COMMAND_WRITE(0xa4 | all);
}
void LCD_BIAS_SET(uchar bias)
{
	LCD_COMMAND_WRITE(0xa2 | bias);
}
void LCD_RW_MODIFY(uchar mode)
{
	LCD_COMMAND_WRITE(0xee & mode);
}
void LCD_RESET(void)
{
	LCD_COMMAND_WRITE(0xe2);
}
void LCD_COM_OUTPUT(uchar f)
{
	LCD_COMMAND_WRITE(0xc0 | f);
}
void LCD_POWER_SET(uchar d)
{
	LCD_COMMAND_WRITE(0x28 | d);
}
void LCD_VR_SET(uchar d)
{
	LCD_COMMAND_WRITE(0x20 | d);
}
void LCD_VOLTAGE_ADJUST(uchar d)
{
	LCD_COMMAND_WRITE(0x81);
	LCD_COMMAND_WRITE(d);
}
void LCD_LIGHT(uchar d)
{
	LCD_COMMAND_WRITE(0x81);
	LCD_COMMAND_WRITE(d);
}
void LCD_STEPUP_SET(uchar d)
{
	LCD_COMMAND_WRITE(0xf0);
	LCD_COMMAND_WRITE(d);
}
