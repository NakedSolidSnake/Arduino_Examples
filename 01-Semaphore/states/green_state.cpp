#include "green_state.h"

#include <unistd.h>
#include <iostream>

GreenState::GreenState() : State()
{
    m_yellowState = new YellowState();
}

GreenState::~GreenState()
{
    delete m_yellowState;
}

void GreenState::doAction(Context *context)
{
    std::cout << this->to_string() << std::endl;
    sleep(3);
    context->setState(m_yellowState);
}

std::string GreenState::to_string(){
    return "Green State";
}