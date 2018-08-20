/*
 * Accelerometer.c
 *
 *  Created on: Nov 5, 2017
 *     
 */

#include "msp.h"
#include "uart.h"
#include "scooter.h"

// Include our global variables //
extern uint32_t accel_Y;
extern SCOOT * scoot_struct;

void configure_ADC_accel(void)
{
    // Configure the Reference Module
    while(REF_A->CTL0 & REF_A_CTL0_GENBUSY); // Wait if reference generator is busy
    REF_A->CTL0 |= REF_A_CTL0_VSEL_0 | REF_A_CTL0_ON;   // Set up a 1.2 V reference voltage
    ADC14->CTL0 &= ~(ADC14_CTL0_ENC);   // Turn off our ADC so that we can edit its values

    // Configure port P4.0 to ADC accelerometer inputs
    // Set P4.0 and P4.2 to ADC tertiary mode, Accelerometer Y and Z directions
    P4->SEL0 |= BIT2;
    P4->SEL1 |= BIT2;

    // Configure our ADC
    // Joystick Sensor Sample time > 30us, ADC ON!, Select SMCLK as our input clock, and single-channel single-conversion //
    ADC14->CTL0 |= ADC14_CTL0_SHT0_5 | ADC14_CTL0_SHP | ADC14_CTL0_ON | ADC14_CTL0_SSEL_4 | ADC14_CTL0_CONSEQ_0;
    ADC14->CTL1 |= ADC14_CTL1_RES__14BIT;     // 14 bit resolution
    ADC14->MCTL[0] |= ADC14_MCTLN_INCH_11;    // Map Accelerometer Y to Memory 1, 3.3 VREF
    ADC14->IER0 |= ADC14_IER0_IE0;            // Enable MCTL0 interrupts!

    while(REF_A->CTL0 & REF_A_CTL0_GENRDY); // Wait for reference generator to settle
    ADC14->CTL0 |= ADC14_CTL0_ENC;          // ADC14 enable conversion
    NVIC_EnableIRQ(ADC14_IRQn);             // enable ADC14 interrupts

}

void convert_Accelerometer(void)
{
// Check our y-direction forces to see which way we are moving //
        if(accel_Y > 9700 && (scoot_struct->velocity == 0))
            scoot_struct->reverse = 0;//UART_send_n(" Backing Up ", 13);
        else if((accel_Y < 9600) && (scoot_struct->velocity == 0))
            scoot_struct->reverse = 1; //UART_send_n(" Moving Forward ", 17);
}

