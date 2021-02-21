/*
 * traffic.cpp
 *
 *  Created on: May 23, 2020
 *      Author: cssouza
 */

#include "traffic.h"


Traffic::Traffic(State *state){
	m_state = state;
}

void Traffic::setState(State *state)
{
	this->m_state = state;
}

State *Traffic::getState() const{
	return m_state;
}

void Traffic::exec(void){
	m_state->doAction(this);
}
