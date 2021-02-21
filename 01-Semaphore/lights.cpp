#include "lights.h"
#include <iostream>
// #include <Arduino.h>

Lights::Lights(){
	initLight();
}

void Lights::initLight(void)
{
	for(int i = LIGHT_RED; i <= LIGHT_GREEN; i++)
	{
		// pinMode(i, OUTPUT);
        std::cout << "Configura: " << i << std::endl;
	}
}

void Lights::setLightHigh(lights light)
{
	// digitalWrite(light, HIGH);
    std::cout << "Liga: " << light << std::endl;
}

void Lights::setLightLow(lights light)
{
	// digitalWrite(light, LOW);
    std::cout << "Desliga: " << light << std::endl;
}
