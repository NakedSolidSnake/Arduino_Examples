/*
 * green_state.cpp
 *
 *  Created on: May 23, 2020
 *      Author: cssouza
 */
#include "green_state.h"
#include "yellow_state.h"
#include "traffic_light.h"
#include <Arduino.h>
#include "communication.h"
#include <string.h>


GreenState::GreenState(){

}

void GreenState::doAction(Traffic *context){
	Communication::send("Green", strlen("Green"));
	TrafficLight::getInstance()->setTrafficLight(TrafficLight::GREEN_LIGHT, 3000);
	context->setState(YellowState::getInstance());
}

static GreenState *GreenState::getInstance(){
	static GreenState *state = nullptr;
	if(state == nullptr){
		state = new GreenState();
	}

	return state;
}
