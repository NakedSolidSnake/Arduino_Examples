#include "yellow_state.h"
#include <unistd.h>
#include <iostream>

YellowState::YellowState() : State(){
    m_redState = new RedState();
}

YellowState::~YellowState(){
    delete m_redState;
}

void YellowState::doAction(Context *context)
{
    std::cout << this->to_string() << std::endl;
    sleep(2);
    context->setState(m_redState);
}

std::string YellowState::to_string(){
    return "Yellow State";
}