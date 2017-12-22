#ifndef	_I2C_M_H
#define	_I2C_M_H

#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

	void Init_I2C(void);
	UINT8 I2C_Receive(UINT8 u8Address, UINT8* p8Data, UINT32 u32ByteSize);
	void I2C_Write_Command(UINT8 u8Address, UINT8* p8Data, UINT32 u32ByteSize);

#endif
