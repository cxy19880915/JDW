
#ifndef __IR_H__
#define __IR_H__

#include "task.h"
#include "Encoder.h"
#include "bd3490.h"
#include "tas5754.h"
#include "task.h"
#include "Bluetooth.h"

#ifdef IR_GLOBALS
	#define IR_EXT 
#else
	#define IR_EXT extern
#endif
	

IR_EXT	void IR_init(void);
IR_EXT	void IR_test_task(void);

#endif

