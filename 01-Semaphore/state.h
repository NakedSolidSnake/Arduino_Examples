#ifndef __STATE_H
#define __STATE_H

#include "context.h"
#include <iostream>

class Context;

class State{
    public:
        virtual void doAction(Context *context) = 0;
        virtual std::string to_string() = 0;
};

#endif