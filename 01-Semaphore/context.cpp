#include "context.h"

Context::Context(State *state)
{
    m_state = state;
}

void Context::setState(State *state)
{
    this->m_state = state;
}

State *Context::getState() const
{
    return m_state;
}

void Context::exec(void){
    m_state->doAction(this);
}