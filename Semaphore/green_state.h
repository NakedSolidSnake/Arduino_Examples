/*
 * green_state.h
 *
 *  Created on: May 23, 2020
 *      Author: cssouza
 */

#ifndef GREEN_STATE_H_
#define GREEN_STATE_H_

#include "state.h"
#include "traffic.h"

class GreenState : public State
{
private:
    GreenState();
public:
    void doAction(Traffic *context)override;
    static GreenState *getInstance();
};



#endif /* GREEN_STATE_H_ */
