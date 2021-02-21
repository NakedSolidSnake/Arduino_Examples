/*
 * state.h
 *
 *  Created on: May 23, 2020
 *      Author: cssouza
 */

#ifndef STATE_H_
#define STATE_H_

class Traffic;

class State{
    public:
        virtual void doAction(Traffic *context) = 0;
};


#endif /* STATE_H_ */
