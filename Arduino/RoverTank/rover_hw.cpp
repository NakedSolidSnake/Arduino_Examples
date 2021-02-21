/*
 * rover_hw.cpp
 *
 *  Created on: 30 de out de 2019
 *      Author: solid
 */

#include "Arduino.h"
#include "include/rover_hw.h"

#define M1_F 9
#define M1_R 12
#define M2_F 11
#define M2_R 10

#define LED_VD 7
#define LED_AM 6
#define LED_VM 5
#define BT     4



typedef void(*RoverDir_cb)(void);

static void Rover_leftDir();
static void Rover_stopDir();
static void Rover_rightDir();
static void Rover_fwdDir();
static void Rover_rearDir();


static RoverDir_cb cb[] =
{
		Rover_stopDir,
		Rover_fwdDir,
		Rover_leftDir,
		Rover_rightDir,
		Rover_rearDir
};

void ROVER_hw_init(void)
{
	int i;

	for(i = M1_F; i <= M1_R; i++){
		pinMode(i , OUTPUT);
	}

	for( i = LED_VM; i <= LED_VD; i++){
		pinMode(i , OUTPUT);
	}

	pinMode(BT , INPUT);

	Serial.begin(9600);
}

void ROVER_direction(RoverTankDirections_t direction)
{
	cb[direction]();
	delay(1);
}

void ROVER_setMode(RoverTankMode_t rover_mode)
{

}

static void Rover_leftDir()
{
	digitalWrite(M2_F, HIGH);
}

static void Rover_stopDir()
{
	digitalWrite(M1_F, LOW);
	digitalWrite(M2_F, LOW);
}

static void Rover_rightDir()
{
	digitalWrite(M1_F, HIGH);
}

static void Rover_fwdDir()
{
	digitalWrite(M1_F, HIGH);
	digitalWrite(M2_F, HIGH);
}

static void Rover_rearDir()
{
	digitalWrite(M1_R, HIGH);
	digitalWrite(M2_R, HIGH);
}

