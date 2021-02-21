#ifndef __YELLOW_STATE_H
#define __YELLOW_STATE_H

#include "../state.h"
#include "red_state.h"
#include <iostream>

class RedState;

class YellowState : public State
{
public: 
    YellowState();
    ~YellowState();
    void doAction(Context *context)override;
    std::string to_string();
private:
    RedState *m_redState;
};

#endif