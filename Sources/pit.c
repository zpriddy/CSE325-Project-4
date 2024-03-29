//*****************************************************************************
// pit.c
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
//*****************************************************************************

#include "common.h"


static int_isr g_timer0_callback = 0;
static int_isr g_timer1_callback = 0;

void pit0_init(int_isr p_callback, int p_scaler)
{
	g_timer0_callback = p_callback;
	
	int_config(55, 2, 7, pit_0_handler);

	// Disable the timer
	MCF_PIT0_PCSR &=  ~(MCF_PIT_PCSR_EN);

	// Enable the debug mode
	MCF_PIT0_PCSR |= MCF_PIT_PCSR_DBG;

	// Enable overwrite
	MCF_PIT0_PCSR |= MCF_PIT_PCSR_OVW;

	// Enable the interups
	MCF_PIT0_PCSR |= MCF_PIT_PCSR_PIE;

	// Clear the interupt flag
	MCF_PIT0_PCSR |= MCF_PIT_PCSR_PIF;

	// Set and forget mode (reload)
	MCF_PIT0_PCSR |= MCF_PIT_PCSR_RLD;

	// Write the prescaler
	MCF_PIT0_PCSR |= MCF_PIT_PCSR_PRE(p_scaler);

	// Write PMR0
	MCF_PIT0_PMR |= MCF_PIT_PMR_PM(49999);
}

void pit1_init(int_isr p_callback, int p_scaler)
{
	g_timer1_callback = p_callback;

	// Disable the timer
	MCF_PIT1_PCSR &=  ~(MCF_PIT_PCSR_EN);

	// Enable the debug mode
	MCF_PIT1_PCSR |= MCF_PIT_PCSR_DBG;

	// Enable overwrite
	MCF_PIT1_PCSR |= MCF_PIT_PCSR_OVW;

	// Enable the interups
	MCF_PIT1_PCSR |= MCF_PIT_PCSR_PIE;

	// Clear the interupt flag
	MCF_PIT1_PCSR |= MCF_PIT_PCSR_PIF;

	// Set and forget mode (reload)
	MCF_PIT1_PCSR |= MCF_PIT_PCSR_RLD;

	// Write the prescaler
	MCF_PIT1_PCSR |= MCF_PIT_PCSR_PRE(p_scaler);

	// Write PMR0
	MCF_PIT1_PMR = (uint16)0x3D08;
	
	int_config(56, 2, 7, pit_1_handler);

}

void pit0_enable()
{
	// Enable the timer
	MCF_PIT0_PCSR |=  (MCF_PIT_PCSR_EN);
}

void pit0_disable()
{
	// Enable the timer
	MCF_PIT0_PCSR &=  ~(MCF_PIT_PCSR_EN);
}

void pit0_clr_flg()
{
	// Clear the interupt flag
	MCF_PIT0_PCSR |= MCF_PIT_PCSR_PIF;
}

void pit1_enable()
{
	// Enable the timer
	MCF_PIT1_PCSR |=  (MCF_PIT_PCSR_EN);
}

void pit1_disable()
{
	// Enable the timer
	MCF_PIT1_PCSR &=  ~(MCF_PIT_PCSR_EN);
}

void pit1_clr_flg()
{
	// Clear the interupt flag
	MCF_PIT1_PCSR |= MCF_PIT_PCSR_PIF;
}




/*-----------------------------------------------------------------------------
 * FUNCTION: pit0_handler
 *
 * DESCRIPTION
 * ISR for pit0 handler.
 *-----------------------------------------------------------------------------*/
__declspec(interrupt) void pit_0_handler(void)
{

		//Clear Flag 
		MCF_PIT0_PCSR |= MCF_PIT_PCSR_PIF;
		//Disable
	 	MCF_PIT0_PCSR &= ~(MCF_PIT_PCSR_PIE);
	 	
        if (g_timer0_callback)
                g_timer0_callback();
        //Enable
        MCF_PIT0_PCSR |= MCF_PIT_PCSR_PIE;

}

/*-----------------------------------------------------------------------------
 * FUNCTION: pit1_handler 
 *
 * DESCRIPTION
 * ISR for pit1 handler.
 *---------------------------------------------------------------------------*/

__declspec(interrupt) void pit_1_handler(void)
{
        //Clear Flag
		MCF_PIT1_PCSR |= MCF_PIT_PCSR_PIF;
		//Disable
	 	MCF_PIT1_PCSR &= ~(MCF_PIT_PCSR_PIE);

        if (g_timer1_callback)
                g_timer1_callback();
        
        //Enable
        MCF_PIT1_PCSR |= MCF_PIT_PCSR_PIE;
}