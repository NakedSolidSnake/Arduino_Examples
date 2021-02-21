/*
 * traffic_light.h
 *
 *  Created on: May 25, 2020
 *      Author: cssouza
 */

#ifndef TRAFFIC_LIGHT_H_
#define TRAFFIC_LIGHT_H_



class TrafficLight{
public:
	enum light{
		RED_LIGHT = 3,
		YELLOW_LIGHT = 4,
		GREEN_LIGHT = 5
	};

	static TrafficLight *getInstance();
	void setTrafficLight(light l, int duration);

private:
	TrafficLight();
	void initLights();
	void setLightOn(light l);
	void setLightOff(light l);
	class Lights;
};

#endif /* TRAFFIC_LIGHT_H_ */
