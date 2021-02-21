/*
 * rover_tank.h
 *
 *  Created on: 30 de out de 2019
 *      Author: solid
 */

#ifndef INCLUDE_ROVER_TANK_TYPES_H_
#define INCLUDE_ROVER_TANK_TYPES_H_

#include <stdint.h>

#define MAX_BIND		10

typedef void (*RoverCallback)(void);

typedef enum
{
	ROVER_MODE_REMOTE,
	ROVER_MODE_AUTO
}RoverTankMode_t;

typedef enum
{
	ROVER_DIR_STOP,
	ROVER_DIR_FWD,
	ROVER_DIR_LEFT,
	ROVER_DIR_RIGHT,
	ROVER_DIR_REAR
}RoverTankDirections_t;

/*
 * +----------+----------+----------+----------+----------+----------+
 * |  start   |   mode   | command  | payload  | checksum |   end    |
 * +----------+----------+----------+----------+----------+----------+
 *
 * start    = $
 *
 * mode     = 00 -> ROVER_MODE_REMOTE
 * 			  01 -> ROVER_MODE_AUTO
 *
 * command  = 00 -> CMD_DIR_STOP
 * 			  01 -> CMD_DIR_FWD
 * 			  02 -> CMD_DIR_LEFT
 * 			  03 -> CMD_DIR_RIGHT
 * 			  04 -> CMD_SET_POWER
 *
 * payload  =
 *
 * checksum =
 *
 * end      = &
 */

typedef struct
{
	uint8_t start;
	uint8_t command;
	uint8_t payload[10];
	uint8_t chksum;
	uint8_t end;
}RoverProtocol_t;

typedef struct
{
	RoverTankDirections_t rover_dir;
	RoverCallback rover_cb;
}RoverBind_t;

typedef struct
{
	RoverBind_t binds[MAX_BIND];
	int nbind;
}RoverBindsConnected_t;

#endif /* INCLUDE_ROVER_TANK_TYPES_H_ */
