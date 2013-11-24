//*******************************************************************************************************
// main.c
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
//********************************************************************************************************

#include "common.h"
#include "uc_led.h"

#define forever for(;;)

int i,j,z;



int volatile LED_DIR, LED_ON_COUNT;
int volatile RGB_LED, RGB_LED_CONFIG, CONFIG;
int LED_ON_SET[3];
int dipsw;


gpio_pin_t volatile RGB_LED_PIN[3] = {rgb_led_1_comm, rgb_led_2_comm, rgb_led_3_comm};

//Arrays to store the RGB Info for each rgb led
int volatile LEDS[3];


static void pb1_callback()
{
	//RGB_LED_CONFIG = RGB_LED_CONFIG+1;
	oct_rgb_led_off(RGB_LED_PIN[RGB_LED_CONFIG]);
	RGB_LED_CONFIG++;
	if(RGB_LED_CONFIG > 2)
		RGB_LED_CONFIG=0;
	
	
}
static void pb2_callback()
{
	LED_DIR=0;	
}

static void pit0_callback()
{
	if(CONFIG == 0)
	{
		oct_rgb_led_all_off();

		if(LED_ON_SET[RGB_LED] == 1)
		{
			oct_rgb_set_color(LEDS[RGB_LED]);
			oct_rgb_led_on(RGB_LED_PIN[RGB_LED]);
		}
		RGB_LED++;
				
		if (RGB_LED > 2)
			RGB_LED = 0;
	}
}

static void pit1_callback()
{
	if(CONFIG == 1)
	{
		//dtim0_busy_delay_ms(10);
		oct_rgb_led_toggle(RGB_LED_PIN[RGB_LED_CONFIG]);
	}
	if(CONFIG == 0)
	{
		switch(LED_ON_COUNT)
		{
			case 0: // 0 ms
				LED_ON_SET[0] = 0;
				LED_ON_SET[1] = 0;
				LED_ON_SET[2] = 0;
				LED_ON_COUNT++;
				break;
			case 1: // 200 ms
				LED_ON_SET[0] = 1;
				LED_ON_SET[1] = 0;
				LED_ON_SET[2] = 0;
				LED_ON_COUNT++;
				break;
			case 2: // 400 ms
				LED_ON_SET[0] = 0;
				LED_ON_SET[1] = 0;
				LED_ON_SET[2] = 0;
				LED_ON_COUNT++;
				break;
			case 3: //600 ms
				LED_ON_SET[0] = 1;
				LED_ON_SET[1] = 1;
				LED_ON_SET[2] = 0;
				LED_ON_COUNT++;
				break;
			case 4: // 800 ms
				LED_ON_SET[0] = 0;
				LED_ON_SET[1] = 0;
				LED_ON_SET[2] = 0;
				LED_ON_COUNT++;
				break;
			case 5: // 1000 ms
				LED_ON_SET[0] = 1;
				LED_ON_SET[1] = 0;
				LED_ON_SET[2] = 0;
				LED_ON_COUNT++;
				break;
			case 6: // 1200 ms
				LED_ON_SET[0] = 0;
				LED_ON_SET[1] = 0;
				LED_ON_SET[2] = 0;
				LED_ON_COUNT++;
				break;
			case 7: //1400 ms
				LED_ON_SET[0] = 1;
				LED_ON_SET[1] = 1;
				LED_ON_SET[2] = 1;
				LED_ON_COUNT=0;
				break;
		}
	}
}


//PWM CHECK 
static void pwm_init_check()
{
	pwm_channel_enable(6);
	pwm_channel_enable(5);
	pwm_channel_enable(4);
	
	pwm_channel_set_duty(4, 100);
	pwm_channel_set_duty(5, 1);
	pwm_channel_set_duty(6, 1);
	dtim0_busy_delay_ms(300);
	
	pwm_channel_set_duty(4, 1);
	pwm_channel_set_duty(5, 100);
	pwm_channel_set_duty(6, 1);
	dtim0_busy_delay_ms(300);
	
	pwm_channel_set_duty(4, 1);
	pwm_channel_set_duty(5, 1);
	pwm_channel_set_duty(6, 100);
	dtim0_busy_delay_ms(300);

	pwm_channel_set_duty(4, 1);
	pwm_channel_set_duty(5, 1);
	pwm_channel_set_duty(6, 1);

	
	for(i = 4 ; i < 7 ; i++)
	{
		for(j = 0 ; j < 100 ; j++)
		{
			pwm_channel_set_duty(i, j);
			dtim0_busy_delay_ms(10);
		}
		pwm_channel_set_duty(i, 1);
	}
	
}



//Calls uc_dipsw_init() to initialize the GPIO port to access the DIP switch, uc_led_init() to initialize the port to access
//the LED's, and dtim0_init() to initialize DTIM0.
static void hw_init()
{
	RGB_LED=0;
	LED_ON_COUNT=0;
	LEDS[0] = C_RED;
	LEDS[1] = C_GREEN;
	LEDS[2] = C_BLUE;
	CONFIG = 0;
	
	
	int_inhibit_all();
	pit0_init(pit0_callback, 0x02);
	pit1_init(pit1_callback, 9);
	uc_dipsw_init();
	dtim0_init();
	uc_pushb_init(pb1_callback, pb2_callback);
	oct_rgb_led_init();
	pwm_channel_init(4);
	pwm_channel_init(5);
	pwm_channel_init(6);
	
	int_uninhibit_all();
	
	LED_ON_SET[0] = 0;
	LED_ON_SET[1] = 0;
	LED_ON_SET[2] = 0;
	
	oct_rgb_led_all_off();

	pit0_enable();
	pit1_enable();

}




static void config_mode()
{
	RGB_LED_CONFIG = 0;
	oct_rgb_led_all_off();
	while(uc_dipsw_get_state(uc_dipsw_1) == gpio_pin_state_low)
	{
		dipsw = ( (uc_dipsw_get_state(uc_dipsw_2) ) << 2) | ((uc_dipsw_get_state(uc_dipsw_3) ) << 1) | ((uc_dipsw_get_state(uc_dipsw_4) ));

	    switch(dipsw)
	    {
	    	case 0b111: // 000
	    		oct_rgb_set_color(C_BLUE);		//BLUE
	    		LEDS[RGB_LED_CONFIG] = C_BLUE;
	    		break;
	    	case 0b110: // 001
	    		oct_rgb_set_color(C_GREEN); 	//GREEN
	    		LEDS[RGB_LED_CONFIG] = C_GREEN;
	    		break;
	    	case 0b101: // 010
	    		oct_rgb_set_color(C_INDIGO); 	//INDIGO
	    		LEDS[RGB_LED_CONFIG] = C_INDIGO;
	    	    break;
	    	case 0b100: // 011
	    		oct_rgb_set_color(C_ORANGE); 	//ORANGE
	    		LEDS[RGB_LED_CONFIG] = C_ORANGE;
	    	    break;
	    	case 0b011: // 100
	    		oct_rgb_set_color(C_RED); 		//RED
	    		LEDS[RGB_LED_CONFIG] = C_RED;
	    	    break;
	    	case 0b010: // 101
	    		oct_rgb_set_color(C_VIOLET); 	//VIOLET
	    		LEDS[RGB_LED_CONFIG] = C_VIOLET;
	    	    break;
	    	case 0b001: // 110
	    		oct_rgb_set_color(C_WHITE); 	//WHITE
	    		LEDS[RGB_LED_CONFIG] = C_WHITE;
	    	    break;
	    	case 0b000: // 111
	    		oct_rgb_set_color(C_YELLOW); 	//YELLOW
	    		LEDS[RGB_LED_CONFIG] = C_YELLOW;
	    	    break;
	    }
		
		uc_dipsw_get_state(uc_dipsw_1);

	}
	oct_rgb_led_all_off();
}



static void run()
{
	while(1)
	{
		if(uc_dipsw_get_state(uc_dipsw_1) == gpio_pin_state_low)
		{
			CONFIG = 1;
			config_mode();
		}
		else
		{
			CONFIG = 0;
			dtim0_busy_delay_ms(200);
		}
	}
}


__declspec(noreturn) int main()
{
	hw_init();
	run();
}