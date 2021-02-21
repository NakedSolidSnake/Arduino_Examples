#include <Arduino.h>

String message;

void setup() {
	Serial.begin(9600);
	Serial.setTimeout(100);

}

void loop() {
	Serial.println("Waiting for receiving a answer");
	message = Serial.readString();

	Serial.println(message);
}
