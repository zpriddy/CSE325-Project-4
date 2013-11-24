//*******************************************************************************************************
// oct_rgb_led.h
//
// DESCRIPTION:
//
// AUTHORS:
//  Abdulla Al Braiki (ayalbrai@asu.edu)
//  Zachary Priddy (zpriddy@asu.edu)
//
// Computer Science & Engineering
// Arizona State University
// Tempe, AZ 85287-8809
//
// Date: Oct 24, 2013
// 
//********************************************************************************************************

#include "common.h"

#ifndef OCT_RGB_LED_H_
#define OCT_RGB_LED_H_



void oct_rgb_led_init();
void oct_rgb_led_all_off();
void oct_rgb_led_all_on();
void oct_rgb_led_on(gpio_pin_t );
void oct_rgb_led_off(gpio_pin_t );
void oct_rgb_led_toggle(gpio_pin_t p_pin);
void oct_rgb_set_color(int p_color);


#endif /* OCT_RGB_LED_H_ */
