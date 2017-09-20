
#include "FM12832R.h"






unsigned char XPOS;                     //列方向LCD点阵位置指针
unsigned char YPOS;                     //行方向LCD点阵位置指针

//sbit A0PIN  =P3^2;
//sbit RESPIN =P3^1;
//sbit SCLPIN =P3^3;
//sbit SIPIN  =P3^4;
//sbit CSPIN  =P3^0;
//sbit key    =P2^0;


//typedef	struct typFNT_GB16 GB;
/////////////////////////////////////////////////////////////////////////
// 汉字字模表                                                          //
// 汉字库: 宋体16.dot 纵向取模下高位,数据排列:从左到右从上到下         //
/////////////////////////////////////////////////////////////////////////
GB GB_16[] =          // 数据表
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

// 汉字表：
// 通道

void Backlight(unsigned char ms)
{
	LCD_BL = 0;
	CLK_SysTickDelay(ms);
	LCD_BL = 1;
	CLK_SysTickDelay(200-ms);
}

//-------------------------------------------------------------------------------
//子程序名称:void transbyte(unsigned char d).
//功能:送1字节数据到液晶显示控制器.
//-------------------------------------------------------------------------------
void transbyte(unsigned char d)         //送1字节数据到液晶显示控制器子程序
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
        d<<=1;                          //从高到低位送字节位数据到液晶显示控制器
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
//子程序名称:lcdwc(unsigned char c).
//功能:向液晶显示控制器送指令.
//-------------------------------------------------------------------------------
void WriteCommand(unsigned char c)
{
	LCD_A0 = 0;
	LCD_CSB = 1;
	LCD_CSB = 0;
	transbyte(c);
	LCD_CSB = 1;	
}

void lcdreset(void)                     //液晶显示控制器初始化子程序
{   
	LCD_RSTB = 0;
	CLK_SysTickDelay(_10ms);
	LCD_RSTB = 1;
	CLK_SysTickDelay(_10ms);
    LCD_COMMAND_WRITE(0xA2);                        //设置LCD bias 对比度
    CLK_SysTickDelay(_10ms);
    LCD_COMMAND_WRITE(0xA0);                        //设置ADC select
    CLK_SysTickDelay(_10ms);
    LCD_COMMAND_WRITE(0xC8);                        //设置COM反向
    CLK_SysTickDelay(_10ms);
	LCD_COMMAND_WRITE(0x24);							//电压内部电阻比率
    CLK_SysTickDelay(_10ms);
	LCD_COMMAND_WRITE(0x81);							//电压调节 进入设置
    CLK_SysTickDelay(_10ms);
	LCD_COMMAND_WRITE(0x03);							//
    CLK_SysTickDelay(_10ms);
	LCD_COMMAND_WRITE(0x29);
    CLK_SysTickDelay(_10ms);
	LCD_COMMAND_WRITE(0x2B);
    CLK_SysTickDelay(_10ms);
//    WriteCommand(0x60);                        //设置显示初始行
//    CLK_SysTickDelay(_10ms);
    LCD_COMMAND_WRITE(0x2F);                        //设置电源控制模式
    CLK_SysTickDelay(_10ms);
    LCD_COMMAND_WRITE(0xAF);                        //开显示
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
//子程序名称:void lcdpos(void).
//功能:设置坐标点(XPOS,YPOS)位置对应的内部RAM地址.
//-------------------------------------------------------------------------------
void lcdpos(void)                       //设置坐标点(XPOS,YPOS)内部RAM地址的子程序
{  unsigned char Column;
   Column=XPOS+1;
   WriteCommand(0xB0|((YPOS/8)&0x7));          //页地址设置
   WriteCommand(0x10|(Column>>4));             //列的高四位设置
   WriteCommand(Column&0x0F);                  //列的低四位设置
}

//-------------------------------------------------------------------------------
//子程序名称:void lcdfill(unsigned char d).
//功能:整屏显示d表示的字节数据.
//-------------------------------------------------------------------------------
void lcdfill(unsigned char d)           //整屏显示d代表的字节数据子程序
{   unsigned char j;
    for(YPOS=0;YPOS<64;YPOS+=8)         //8页
    {   
		LCD_DISP_PAGE(YPOS/8);
		LCD_DISP_FIRST_COL(0);
        for(j=0;j<128;j++)              //128列
            LCD_DISP_DATA_WRITE(d);                   //送图形数据
    }
}

//-------------------------------------------------------------------------------
//子程序名称:void setlcdvoltage(unsigned char vol)
//功能:设置LCD电压用来调节显示的对比度
//-------------------------------------------------------------------------------
void setlcdvoltage(unsigned char vol)   //LCD电压设置
{   WriteCommand(0x81);
    WriteCommand(vol&0x3F);                    //范围为0-63,上电默认值为32
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


// 汉字库: 宋体16.dot 纵向取模下高位,数据排列:从左到右从上到下  init //
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
