/*
 * traffic.h
 *
 *  Created on: May 23, 2020
 *      Author: cssouza
 */

#ifndef TRAFFIC_H_
#define TRAFFIC_H_

#include "state.h"

class Traffic {
private:
    State *m_state;

public:
    Traffic(State *state);
    void setState(State *state);
    State *getState() const;
    void exec(void);
};


#endif /* TRAFFIC_H_ */
