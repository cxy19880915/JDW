#define TASK_GLOBALS
#include "task.h"

/************************************************************
 *@init file
 ************************************************************/
/**
 *Init GPIO mode 
 */
void GPIO_Init( void )
{
	/* Init P2.2 P2.3 P2.4 and P3.6 to be output mode */
	
	GPIO_SetMode(P3, BIT5, GPIO_PMD_OUTPUT);//LCD_CSB
	GPIO_SetMode(P3, BIT4, GPIO_PMD_OUTPUT);//LCD_RSTB
	GPIO_SetMode(P3, BIT2, GPIO_PMD_OUTPUT);//LCD_A0
	GPIO_SetMode(P3, BIT1, GPIO_PMD_OUTPUT);//LCD_SCL
	GPIO_SetMode(P5, BIT4, GPIO_PMD_OUTPUT);//LCD_SDA
	GPIO_SetMode(P3, BIT0, GPIO_PMD_OUTPUT);//LCD_BL
	
	/*****init gpio output******/

}


