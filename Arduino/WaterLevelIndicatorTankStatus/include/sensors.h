/*
 * hardware.h
 *
 *  Created on: 11 de set de 2019
 *      Author: solid
 */

#ifndef INCLUDE_SENSORS_H_
#define INCLUDE_SENSORS_H_

/* Sensor Pins */
#define SENSOR_EMPTY	3
#define SENSOR_LEVEL1	4
#define SENSOR_LEVEL2	5
#define SENSOR_LEVEL3	6
#define SENSOR_FULL		7

/* Sensor state */
#define ERROR_SENSOR        	  -1
#define MASK_EMPTY				0x01
#define MASK_EMPTY_L1			0x03
#define MASK_EMPTY_L1L2			0x07
#define MASK_EMPTY_L1L2L3		0x0F
#define MASK_ALL_SENSORS		0x1F

int Sensor_init(void);
int Sensor_getState(void);

#endif /* INCLUDE_SENSORS_H_ */
