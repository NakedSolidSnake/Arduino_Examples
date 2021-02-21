#ifndef __GREEN_STATE_H
#define __GREEN_STATE_H

#include "../state.h"
#include "yellow_state.h"
#include <string>

class YellowState;

class GreenState : public State
{
public: 
    GreenState();
    ~GreenState();
    void doAction(Context *context)override;
    std::string to_string();
private:
    YellowState *m_yellowState;
};

#endif