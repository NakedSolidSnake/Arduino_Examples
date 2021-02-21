#ifndef __RED_STATE_H
#define __RED_STATE_H

#include "../state.h"
#include "green_state.h"
#include <string>

class GreenState;

class RedState : public State
{
public: 
    RedState();
    ~RedState();
    void doAction(Context *context)override;
    std::string to_string();

private:
    GreenState *m_greenState;
};

#endif