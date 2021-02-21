#ifndef __CONTEXT_H
#define __CONTEXT_H

#include "state.h"

class State;

class Context {
private:
    State *m_state;

public:
    Context(State *state);
    void setState(State *state);
    State *getState() const;
    void exec(void);    
};

#endif