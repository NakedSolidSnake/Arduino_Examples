#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#define RED			5
#define YELLOW		6
#define BLUE		7

int redLEDProfiler = 0;
int yellowLEDProfiler = 0;
int blueLEDProfiler = 0;

const uint16_t *blueLed = (uint16_t *)BLUE;
const uint16_t *yellowLed = (uint16_t *)YELLOW;
const uint16_t *redLed = (uint16_t *)RED;

static void vBlinkLed(void *pvParams);

void setup() {
	Serial.begin(115200);

	xTaskCreate(vBlinkLed, "RED Task", 128, (void *)redLed, 1, NULL);
	xTaskCreate(vBlinkLed, "Yellow Task", 128, (void *)yellowLed, 1, NULL);
	xTaskCreate(vBlinkLed, "Blue Task", 128, (void *)blueLed, 2, NULL);
}

void loop() {

}

static void vBlinkLed(void *pvParams)
{
	const int pin = *(int *)pvParams;

	pinMode(pin, OUTPUT);

	while(1){
		redLEDProfiler++;
		Serial.print("redLEDProfiler: ");
		Serial.println(redLEDProfiler);
		digitalWrite(pin, digitalRead(pin) ^1 );
	}
}

