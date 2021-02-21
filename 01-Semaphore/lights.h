/*
 * lights.h
 *
 *  Created on: May 21, 2020
 *      Author: cssouza
 */

#ifndef LIGHTS_H_
#define LIGHTS_H_

class Lights{


public:

	enum lights {
		LIGHT_RED = 2,
		LIGHT_YELLOW,
		LIGHT_GREEN
	};

	Lights();
	void setLightHigh(lights light);
	void setLightLow(lights light);

private:
	void initLight(void);
};






#endif /* LIGHTS_H_ */
