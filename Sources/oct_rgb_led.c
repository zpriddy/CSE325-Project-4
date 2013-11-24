//*******************************************************************************************************
// oct_rgb_led.c
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


int toggle = 0;



int BLUE_RGB_R   = 1;
int BLUE_RGB_G   = 1;
int BLUE_RGB_B   = 100;
int GREEN_RGB_R  = 1;
int GREEN_RGB_G  = 69;
int GREEN_RGB_B  = 1;
int INDIGO_RGB_R = 29;
int INDIGO_RGB_G = 0;
int INDIGO_RGB_B = 51;
int RED_RGB_R    = 100;
int RED_RGB_G    = 1;
int RED_RGB_B    = 1;
int ORANGE_RGB_R = 54;
int ORANGE_RGB_G = 20;
int ORANGE_RGB_B = 0;
int VIOLET_RGB_R = 93;
int VIOLET_RGB_G = 51;
int VIOLET_RGB_B = 93;
int WHITE_RGB_R  = 90;
int WHITE_RGB_G  = 100;
int WHITE_RGB_B  = 100;
int YELLOW_RGB_R = 100;
int YELLOW_RGB_G = 100;
int YELLOW_RGB_B = 0;




void oct_rgb_led_init()
{
	gpio_port_init(rgb_comm_port, rgb_led_1_comm, gpio_funct_gpio, gpio_data_dir_out, gpio_pin_state_low);
	gpio_port_init(rgb_comm_port, rgb_led_2_comm, gpio_funct_gpio, gpio_data_dir_out, gpio_pin_state_low);
	gpio_port_init(rgb_comm_port, rgb_led_3_comm, gpio_funct_gpio, gpio_data_dir_out, gpio_pin_state_low);
	
}

void oct_rgb_led_all_off()
{
	gpio_port_set_pin_state(rgb_comm_port, rgb_led_1_comm, gpio_pin_state_low);
	gpio_port_set_pin_state(rgb_comm_port, rgb_led_2_comm, gpio_pin_state_low);
	gpio_port_set_pin_state(rgb_comm_port, rgb_led_3_comm, gpio_pin_state_low);
}

void oct_rgb_led_all_on()
{
	gpio_port_set_pin_state(rgb_comm_port, rgb_led_1_comm, gpio_pin_state_high);
	gpio_port_set_pin_state(rgb_comm_port, rgb_led_2_comm, gpio_pin_state_high);
	gpio_port_set_pin_state(rgb_comm_port, rgb_led_3_comm, gpio_pin_state_high);
}

void oct_rgb_led_on(gpio_pin_t p_pin)
{
	gpio_port_set_pin_state(rgb_comm_port, p_pin, gpio_pin_state_high);
}

void oct_rgb_led_off(gpio_pin_t p_pin)
{
	gpio_port_set_pin_state(rgb_comm_port, p_pin, gpio_pin_state_low);
}

void oct_rgb_led_toggle(gpio_pin_t p_pin)
{
	if(toggle == 0)
	{
		oct_rgb_led_on(p_pin);
		toggle = 1;
	}
	else
	{
		oct_rgb_led_off(p_pin);
		toggle = 0;
	}
	
}

void oct_rgb_set_color(int p_color)
{

	
	switch(p_color)
	{
		case C_BLUE:
			pwm_channel_set_duty(4, BLUE_RGB_R);
			pwm_channel_set_duty(5, BLUE_RGB_G);
			pwm_channel_set_duty(6, BLUE_RGB_B);
			break;
		case C_RED:
			pwm_channel_set_duty(4, RED_RGB_R);
			pwm_channel_set_duty(5, RED_RGB_G);
			pwm_channel_set_duty(6, RED_RGB_B);
			break;
		case C_GREEN:
			pwm_channel_set_duty(4, GREEN_RGB_R);
			pwm_channel_set_duty(5, GREEN_RGB_G);
			pwm_channel_set_duty(6, GREEN_RGB_B);
			break;
		case C_ORANGE:
			pwm_channel_set_duty(4, ORANGE_RGB_R);
			pwm_channel_set_duty(5, ORANGE_RGB_G);
			pwm_channel_set_duty(6, ORANGE_RGB_B);
			break;
		case C_INDIGO:
			pwm_channel_set_duty(4, INDIGO_RGB_R);
			pwm_channel_set_duty(5, INDIGO_RGB_G);
			pwm_channel_set_duty(6, INDIGO_RGB_B);
			break;
		case C_WHITE:
			pwm_channel_set_duty(4, WHITE_RGB_R);
			pwm_channel_set_duty(5, WHITE_RGB_G);
			pwm_channel_set_duty(6, WHITE_RGB_B);
			break;
		case C_YELLOW:
			pwm_channel_set_duty(4, YELLOW_RGB_R);
			pwm_channel_set_duty(5, YELLOW_RGB_G);
			pwm_channel_set_duty(6, YELLOW_RGB_B);
			break;
		case C_VIOLET:
			pwm_channel_set_duty(4, VIOLET_RGB_R);
			pwm_channel_set_duty(5, VIOLET_RGB_G);
			pwm_channel_set_duty(6, VIOLET_RGB_B);
			break;
			
	}

	//The colors are set in oct_rgb_led.h and you just pass the array to the function

	
}