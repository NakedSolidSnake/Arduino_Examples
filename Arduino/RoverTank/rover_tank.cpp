/*
 * rover_tank.cpp
 *
 *  Created on: 30 de out de 2019
 *      Author: solid
 */

#include "include/rover_tank_types.h"
#include "include/rover_tank.h"

static RoverBindsConnected_t conn =
		{
				.nbind = 0
		};



void RoverBindCommand(RoverTankDirections_t rover_dir, RoverCallback rover_cb)
{
	if(conn.nbind < MAX_BIND){
		conn.binds[conn.nbind].rover_dir = rover_dir;
		conn.binds[conn.nbind].rover_cb = rover_cb;
		conn.nbind++;
	}else{

	}
}

void RoverCommandExecute(RoverTankDirections_t rover_dir)
{
	for(int i = 0; i < conn.nbind; i++){
		if(conn.binds[i].rover_dir == rover_dir){
			conn.binds[i].rover_cb();
		}
	}
}
