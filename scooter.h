/*
 * scooter.h
 *
 *  Created on: Oct 31, 2017
 *    
 */

#ifndef SCOOTER_H_
#define SCOOTER_H_
#include "msp.h"

typedef struct SCOOT_t{
	volatile float cur_dist;
	volatile float prev_dist;
	volatile float velocity;
	volatile uint8_t reverse;
} SCOOT;

/*******************************************
 *
 *          scoot_initialize()
 *
 * A function that initializes a scooter
 * structure that stores our variables
 ******************************************/
SCOOT * scoot_initialize(void);
void delete_scoot(SCOOT* scooter);

#endif /* SCOOTER_H_ */
