/*
 * scooter.c
 *
 *  Created on: Oct 31, 2017
 *      Author: lemmo
 */
#include "scooter.h"

SCOOT * scoot_initialize(){
    SCOOT * scooter = (SCOOT*)malloc(sizeof(SCOOT));
    scooter->cur_dist = 0;
    scooter->prev_dist = 0;
    scooter->reverse = 0; //(default direction is forward)
    scooter->velocity = 0;
    return scooter;
}

void delete_scoot(SCOOT* scooter){
    free(scooter);
}

