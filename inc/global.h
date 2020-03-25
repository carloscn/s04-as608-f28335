/*
 * global.h
 *
 *  Created on: 2018Äê4ÔÂ16ÈÕ
 *      Author: weihaochen
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_



#include "DSP2833x_Device.h"     // DSP281x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP281x Examples Include File
#include "type.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "sci.h"
#include "as608.h"


#define DELAY_MS(A)  DSP28x_usDelay(((((long double) A * 1000000.0L) / (long double)CPU_RATE) - 9.0L) / 5.0L)
#endif /* INC_GLOBAL_H_ */
