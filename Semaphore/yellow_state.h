/*
 * yellow_state.h
 *
 *  Created on: May 23, 2020
 *      Author: cssouza
 */

#ifndef YELLOW_STATE_H_
#define YELLOW_STATE_H_

#include "state.h"

class YellowState : public State
{
private:
    YellowState();
public:
    void doAction(Traffic *context)override;
    static YellowState *getInstance();
};



#endif /* YELLOW_STATE_H_ */
