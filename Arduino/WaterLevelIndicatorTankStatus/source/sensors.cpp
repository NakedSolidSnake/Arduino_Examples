/*
 * sensors.cpp
 *
 *  Created on: 11 de set de 2019
 *      Author: solid
 */

#include <Arduino.h>
#include "../include/sensors.h"

static int error(int sensorMask);

int Sensor_init(void)
{
	for(int sensor = SENSOR_EMPTY; sensor <= SENSOR_FULL; sensor++)
		pinMode(sensor, INPUT_PULLUP);

	return 0;
}

int Sensor_getState(void)
{
	int sensorMask = 0;
	for(int sensor = SENSOR_EMPTY, shift = 0; sensor <= SENSOR_FULL; sensor++, shift++){
		sensorMask |= (digitalRead(sensor) << shift);
	}

	return error(sensorMask);
}

static int error(int sensorMask)
{

	switch(sensorMask){
	case MASK_EMPTY:
		break;
	case MASK_EMPTY_L1:
		break;
	case MASK_EMPTY_L1L2:
		break;
	case MASK_EMPTY_L1L2L3:
		break;
	case MASK_ALL_SENSORS:
		break;
	default:
		break;
	}
	return sensorMask;
}
