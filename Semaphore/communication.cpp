/*
 * communication.cpp
 *
 *  Created on: May 23, 2020
 *      Author: cssouza
 */


#include <Arduino.h>
#include "communication.h"


static void Communication::open(int baudRate){
	Serial.begin(baudRate);
}

static void Communication::send(const char *buffer, int size)
{
	Serial.write(buffer, size);
}

static void Communication::recv(char *buffer, int size)
{
	Serial.readBytes(buffer, size);
}

static void Communication::close()
{
	Serial.end();
}

