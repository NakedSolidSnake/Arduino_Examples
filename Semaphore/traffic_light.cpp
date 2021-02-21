/*
 * traffic_light.cpp
 *
 *  Created on: May 25, 2020
 *      Author: cssouza
 */

#include <Arduino.h>
#include "traffic_light.h"

static TrafficLight *TrafficLight::getInstance()
{
	static TrafficLight *trafficLight = nullptr;
	if(trafficLight == nullptr)
		trafficLight = new TrafficLight();

	return trafficLight;
}

void TrafficLight::setTrafficLight(light l, int duration)
{
	for(int i = RED_LIGHT; i <= GREEN_LIGHT; i++){
		setLightOff((light)i);
	}

	switch (l) {
	case RED_LIGHT:
		setLightOn(l);
		break;
	case YELLOW_LIGHT:
		setLightOn(l);
		break;
	case GREEN_LIGHT:
		setLightOn(l);
		break;
	default:
		return;
	}

	delay(duration);
}


TrafficLight::TrafficLight()
{
	initLights();
}

void TrafficLight::initLights()
{
	for(int i = RED_LIGHT; i <= GREEN_LIGHT; i++){
		pinMode(i, OUTPUT);
	}
}

void TrafficLight::setLightOn(light l)
{
	digitalWrite(l, HIGH);
}

void TrafficLight::setLightOff(light l)
{
	digitalWrite(l, LOW);
}

class Lights{

};

