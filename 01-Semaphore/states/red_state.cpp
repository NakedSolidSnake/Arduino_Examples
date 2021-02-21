#include "red_state.h"
#include <unistd.h>
#include <iostream>

RedState::RedState() : State(){
    m_greenState = new GreenState();
}

RedState::~RedState(){
    delete m_greenState;
}

void RedState::doAction(Context *context)
{    
    std::cout << this->to_string() << std::endl;
    sleep(3);
    context->setState(m_greenState);
}

std::string RedState::to_string(){
    return "Red State";
}