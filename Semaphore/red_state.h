/*
 * red_state.h
 *
 *  Created on: May 23, 2020
 *      Author: cssouza
 */

#ifndef RED_STATE_H_
#define RED_STATE_H_

#include "state.h"
#include "traffic.h"

class RedState : public State
{
private:
    RedState();
public:
    void doAction(Traffic *context)override;
    static RedState *getInstance();

};



#endif /* RED_STATE_H_ */
