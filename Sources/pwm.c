//*******************************************************************************************************
// pwm.c
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

void pwm_channel_disable(int p_channel) {
	MCF_PWM_PWME &= ~(0x1 << p_channel);
}

void pwm_channel_enable(int p_channel) {
	MCF_PWM_PWME |= 0x1 << p_channel;
}

void pwm_channel_disable_all() {
	MCF_PWM_PWME &= 0;
}

void pwm_channel_init(int p_channel) {
	MCF_PWM_PWME &= ~(0x1 << p_channel); 		// 1. Clear PWME[PWMEn] to disable channel n during configuration.
	MCF_PWM_PWMPOL |= (0x1 << p_channel); 		// 2. Set PWMPOL[PPOLn] to select high polarity.
	MCF_PWM_PWMCLK &= ~(0x1 << p_channel); 		//3. Clear or set PWMCLK[PCKA] to select clock A or clock SA for the channel 0 counter.
	MCF_PWM_PWMPRCLK &= ~(0b01110111); 			//4. Write the selected clock A prescaler value to PWMPRCLK[PCKA].
	MCF_PWM_PWMPRCLK |= 0b00010001;
	//MCF_PWM_PWMPRCLK |= 0b10011001;
	MCF_PWM_PWMCAE &= ~(0x1 << p_channel); 		// 5. Clear PWMCAE[CAEn] to select left-alignment.
	MCF_PWM_PWMSCLA = 0x99; 					//6. If clock SA is being used write the selected scale value to PWMSCLA[SCALEA].
	MCF_PWM_PWMSCLB = 0x99;
	MCF_PWM_PWMCNT(p_channel) &= ~(0x3 << p_channel * 2); //7. Write 0x00 to PWMCNTn to reset the counter to 0.
	MCF_PWM_PWMPER(p_channel) = 0x63; 			//8. Write the desired period to PWMPERn, see Eqn. 31-7.
	MCF_PWM_PWMDTY(p_channel) = 0x31; 			//9. Write the desired duty to PWMDTYn, see Eqn. 31-8.

	// Enable ports for PWM output
	switch (p_channel) {
	case 4:
		gpio_port_init(gpio_port_tc, gpio_pin_2, gpio_funct_tertiary,
				gpio_data_dir_x, gpio_pin_state_x);
		break;
	case 5:
		gpio_port_init(gpio_port_ta, gpio_pin_2, gpio_funct_tertiary,
				gpio_data_dir_x, gpio_pin_state_x);
		break;
	case 6:
		gpio_port_init(gpio_port_tc, gpio_pin_3, gpio_funct_tertiary,
				gpio_data_dir_x, gpio_pin_state_x);
		break;

	}
	pwm_channel_enable(p_channel);

	MCF_PWM_PWME |= 0x1 << p_channel; // 10. Set PWM[PWMEn] to enable channel n and output the signal

}

void pwm_channel_set_duty(int p_channel, int p_duty) {
	p_duty = 100 - p_duty;
	MCF_PWM_PWMDTY(p_channel) = (uint8) p_duty;

}

void pwm_channel_set_frequency() {	
	
}

void pwm_channel_start_output(int p_channel) {
	MCF_PWM_PWME |= 0x1 << p_channel;
}
