#include <Arduino.h>

#define PIN_2		2
#define PIN_12		12

#define LED_RED		PIN_2
#define BT_SEND		PIN_12

void LED_write(int pin, int state){
	digitalWrite(pin, state);
}

int BT_read(void){
	return digitalRead(BT_SEND);
}

void setup() {
	Serial.begin(9600);
	pinMode(LED_RED, OUTPUT);
	pinMode(BT_SEND, INPUT_PULLUP);
}

void loop() {
	if(Serial.available() > 0){
		char read = Serial.read();
		if(toupper(read) == 'L'){
			LED_write(LED_RED, 1);
		}else if(toupper(read) == 'D'){
			LED_write(LED_RED, 0);
		}
	}

	if(BT_read() == LOW){
		delayMicroseconds(1000);
		while(BT_read() == LOW);
		static int state = 0;
		char letter = 0;
		if(state){
			state = 0;
			letter = 'L';
		}else{
			state = 1;
			letter = 'D';
		}

		Serial.write(letter);
	}
}
