/*
 * rover_hw.h
 *
 *  Created on: 30 de out de 2019
 *      Author: solid
 */

#ifndef INCLUDE_ROVER_HW_H_
#define INCLUDE_ROVER_HW_H_

#include "rover_tank_types.h"

void ROVER_hw_init(void);

void ROVER_direction(RoverTankDirections_t direction);

void ROVER_setMode(RoverTankMode_t rover_mode);


#endif /* INCLUDE_ROVER_HW_H_ */
