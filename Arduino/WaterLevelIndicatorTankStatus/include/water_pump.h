/*
 * water_pump.h
 *
 *  Created on: Sep 13, 2019
 *      Author: cssouza
 */

#ifndef INCLUDE_WATER_PUMP_H_
#define INCLUDE_WATER_PUMP_H_


#define WATER_PUMP 	2

#define PUMP_ON		1
#define PUMP_OFF	0

int WATERPUMP_init(void);
int WATERPUMP_set(int onOff);


#endif /* INCLUDE_WATER_PUMP_H_ */

