/*
 * RedState.cpp
 *
 *  Created on: May 23, 2020
 *      Author: cssouza
 */

#include <Arduino.h>
#include "red_state.h"
#include "green_state.h"
#include "traffic_light.h"
#include "communication.h"
#include <string.h>

RedState::RedState(){

}

void RedState::doAction(Traffic *context){
	Communication::send("Red", 4);
	TrafficLight::getInstance()->setTrafficLight(TrafficLight::RED_LIGHT, 3000);
	context->setState(GreenState::getInstance());
}

static RedState *RedState::getInstance(){
	static RedState *state = nullptr;
	if(state == nullptr){
		state = new RedState();
	}

	return state;
}

