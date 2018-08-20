/*
 * interrupt.c
 *
 *  Created on: Oct 20, 2017
 *      Author: lemmo
 */

#include "msp.h"
#include "interrupt.h"
#include "vars.h"
#include "scooter.h"

volatile uint32_t beam_break;
extern uint32_t accel_Y;
extern uint8_t timer_flag;
extern SCOOT * scoot_struct;

void CS_IRQHandler(void)
{
	CS->KEY = 0x695A; // Unlock CS module for register access
	CS->CLRIFG = 0x0343;	//Clear CSIFG
	CS->KEY = 0;	// lock CS module for register access
}

void PORT1_IRQHandler(void)
{
	if(P1IFG & 0x20){	//statement for P1.5
			P1IFG &= ~0x20;
			scoot_struct->cur_dist += SPOKE_ARC;
			return;
	}
	if(P1IFG & 0x02){	//statement for P1.1
			P1IFG &= ~0x02;
			scoot_struct->cur_dist = 0; //resetting distance
			return;
	}
	if(P1IFG & 0x10){	//statement for P1.4
			P1IFG &= ~0x10;
			return;
	}
	return;
}

void ADC14_IRQHandler(void)
{

    if(ADC14->IFGR0 & ADC14_IFGR0_IFG0)
    { // If our accelerometer is done converting our Y force, paste our value into accel_Y
        accel_Y = ADC14->MEM[0];
    }
}

void TA0_0_IRQHandler(void)
{
	TIMER_A0->CCTL[0] &= ~0x01;     // Clear the interrupt flag
	timer_flag = 1; //set flag for while loop in main
}
