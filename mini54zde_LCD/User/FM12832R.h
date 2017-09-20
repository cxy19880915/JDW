#ifndef __FM12832R_H__
#define __FM12832R_H__

#include "Mini51Series.h"
#include "task.h"

#define _1us		2
#define _10ms		10000
#define _200ms		200000
#define ON		1
#define OFF		0
#define uchar unsigned char
#define uint unsigned int

#define LCD_CSB				P35
#define LCD_RSTB			P34
#define LCD_A0				P32
#define LCD_SCL				P31
#define LCD_SDA				P54
#define LCD_BL				P30

// ------------------  汉字字模的数据结构定义 ------------------------ //
typedef struct typFNT_GB16                 // 汉字字模数据结构
{
       signed char Index[2];               // 汉字内码索引
       char Msk[32];                       // 点阵码数据
}GB;

void transbyte(unsigned char d);
void WriteData(unsigned char d);
void WriteCommand(unsigned char c);
void lcdpos(void) ;
void lcdfill(unsigned char d);
void setlcdvoltage(unsigned char vol);
void lcdreset(void);
void disp_window(void);
void Disp_text(void);
void disp_2(uchar st);
void disp_3(void);
void Backlight(unsigned char ms);
void setlcdvoltage(unsigned char vol); 

void LCD_INIT(void);
void LCD_DISP_SWITCH(uchar sw);
void LCD_DISP_FIRST_ROW(uchar row);
void LCD_DISP_PAGE(uchar page);
void LCD_DISP_FIRST_COL(uchar col);
void LCD_DISP_DATA_WRITE(uchar d);
void LCD_COMMAND_WRITE(uchar d);
void LCD_ADC_SELECT(uchar direction);
void LCD_VOLTAGE_SET(uchar v);
void LCD_DISP_ALL(uchar all);
void LCD_BIAS_SET(uchar bias);
void LCD_COM_OUTPUT(uchar f);
void LCD_POWER_SET(uchar d);
void LCD_VR_SET(uchar d);
void LCD_VOLTAGE_ADJUST(uchar d);
void LCD_LIGHT(uchar d);
#endif
