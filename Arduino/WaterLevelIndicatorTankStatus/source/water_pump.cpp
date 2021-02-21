/*
 * water_pump.cpp
 *
 *  Created on: Sep 13, 2019
 *      Author: cssouza
 */

#include <Arduino.h>
#include "../include/water_pump.h"

int WATERPUMP_init(void)
{
	pinMode(WATER_PUMP, OUTPUT);
	return 0;
}

int WATERPUMP_set(int onOff)
{
	switch(onOff){
	case PUMP_ON:
		break;
	case PUMP_OFF:
		break;
	default:
		return -1;
	}
	digitalWrite(WATER_PUMP, onOff);
	return 0;
}


