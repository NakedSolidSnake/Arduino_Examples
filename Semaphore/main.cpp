#include <Arduino.h>
#include "traffic.h"
#include "red_state.h"
#include "traffic_light.h"
#include "communication.h"

static Traffic *context;
void setup() {
	Communication::open(9600);
	//Chama construtor para inicializar os pinos do semaforo
	TrafficLight::getInstance();
	context = new Traffic(RedState::getInstance());
}

void loop() {
	context->exec();
}


