/*
  Sweep

  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Arduino.h>
#include <Servo.h>
#include <stdio.h>

int pos = 0;
Servo servo_9;

void setup()
{
  servo_9.attach(9);
  Serial.begin(9600);

}

void loop()
{
  if(Serial.available() > 0)
  {
   	String s = Serial.readString();


	pos = atoi(s.c_str());
	if(pos > 0 || pos < 181){
		servo_9.write(pos);
		delay(100);
	}
  }
}
