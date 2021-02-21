#include <Arduino.h>

class Traffic;
class YellowState;
class RedState;
class GreenState;
class State;



class Traffic {
private:
    State *m_state;

public:
    Traffic(State *state){
    	m_state = state;
    }

    void setState(State *state)
    {
    	this->m_state = state;
    }

    State *getState() const{
    	return m_state;
    }

    void exec(void){
    	m_state->doAction(this);
    }
};

class RedState : public State
{
public:
	RedState(){

    }

    void doAction(Traffic *context)override{
    	context->setState(new GreenState());
    }
};

class YellowState : public State
{
public:
    YellowState(){

    }
    void doAction(Traffic *context)override{
    	context->setState(new RedState());
    }
};

class GreenState : public State
{
public:
    GreenState(){

    }

    void doAction(Traffic *context)override{
    	context->setState(new YellowState());
    }
};

static Traffic *context;
void setup() {
	context = new Traffic(new RedState());
}

void loop() {
	context->exec();
}
