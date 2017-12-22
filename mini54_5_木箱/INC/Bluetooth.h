#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include <stdio.h>
#include "Mini51Series.h"
#include "task.h"
#include "KEY_Scan.h"

#ifdef Bluetooth_GLOBALS
	#define Bluetooth_EXT 
#else
	#define Bluetooth_EXT extern
#endif


//#define EP_DET  			P52
Bluetooth_EXT	unsigned char AUDIO_flag;	
Bluetooth_EXT	unsigned char BT_connect;
Bluetooth_EXT	void Bluetooth_Test_Task(void);
Bluetooth_EXT	void BT_patch(void);
Bluetooth_EXT	void BT_Play_Pause(void);	
void BT_REV_TASK(void);	
void BT_FWD_TASK(void);	
	

#endif
