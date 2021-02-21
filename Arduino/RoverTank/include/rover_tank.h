/*
 * rover_tank.h
 *
 *  Created on: 30 de out de 2019
 *      Author: solid
 */

#ifndef INCLUDE_ROVER_TANK_H_
#define INCLUDE_ROVER_TANK_H_

#include "rover_tank_types.h"

void RoverBindCommand(RoverTankDirections_t rover_dir, RoverCallback rover_cb);
void RoverCommandExecute(RoverTankDirections_t rover_dir);


#endif /* INCLUDE_ROVER_TANK_H_ */
