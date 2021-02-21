/*
 * yellow_state.cpp
 *
 *  Created on: May 23, 2020
 *      Author: cssouza
 */

#include "yellow_state.h"
#include "red_state.h"
#include "traffic_light.h"
#include <Arduino.h>
#include "communication.h"
#include <string.h>

YellowState::YellowState(){

}
void YellowState::doAction(Traffic *context){
	Communication::send("Yellow", strlen("Yellow"));
	TrafficLight::getInstance()->setTrafficLight(TrafficLight::YELLOW_LIGHT, 3000);
	context->setState(RedState::getInstance());
}

static YellowState *YellowState::getInstance(){
	static YellowState *state = nullptr;
	if(state == nullptr){
		state = new YellowState();
	}

	return state;
}

