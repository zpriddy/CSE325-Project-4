//*******************************************************************************************************
// common.h
//
// DESCRIPTION: A common header file for all header files.
//
// AUTHORS:
// 	Abdulla Al Braiki (ayalbrai@asu.edu)
//	Zachary Priddy (zpriddy@asu.edu)
//
// Computer Science & Engineering
// Arizona State University
// Tempe, AZ 85287-8809
// 
//********************************************************************************************************
#ifndef COMMON_H_
#define COMMON_H_

/*Header Files*/
#include "dtim.h"
#include "gpio.h"
#include "uc_dipsw.h"
#include "uc_led.h"
#include "support_common.h"
#include "uc_pushb.h"
#include "gpt.h"
#include "int.h"
#include "gpio.h"
#include "pwm.h"
#include "oct_rgb_led.h"
#include "pit.h"





#define DELAY_TIME		(250)



#define LED_ON 			(1)
#define LED_OFF 			(0)

#define ON 				(1)
#define OFF				(0)

extern volatile int LED_DIR;

#define C_BLUE    (0)
#define C_GREEN   (1)
#define C_INDIGO  (2)
#define C_ORANGE  (3)
#define C_RED     (4)
#define C_VIOLET  (5)
#define C_WHITE   (6)
#define C_YELLOW  (7)









#endif /* COMMON_H_ */
