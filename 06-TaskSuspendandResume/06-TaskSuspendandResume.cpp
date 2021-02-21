#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#define YELLOW		5
#define RED			6

typedef int TaskProfiler;

TaskProfiler redLEDProfiler = 0;
TaskProfiler yellowLEDProfiler = 0;

static void redBlinkLed(void *params);
static void yellowBlinkLed(void *params);

TaskHandle_t  red_handle, yellow_handle;

void setup() {
	Serial.begin(115200);
	xTaskCreate(redBlinkLed, "RED Task", 128, NULL, 1, &red_handle);
	xTaskCreate(yellowBlinkLed, "Yellow Task", 128, NULL, 2, &yellow_handle);
}

void loop() {

}

static void redBlinkLed(void *params)
{
	(void)params;
	const TickType_t delay1s = pdMS_TO_TICKS(1000000);
	UBaseType_t red_priority;
	pinMode(RED, OUTPUT);

	while(1)
	{
		if(redLEDProfiler++ > 10){
			redLEDProfiler = 0;
			vTaskResume(yellow_handle);
		}
		digitalWrite(RED, digitalRead(RED) ^ 1);
		delay(500);
	}
}

static void yellowBlinkLed(void *params)
{
	(void)params;
	const TickType_t delay1s = pdMS_TO_TICKS(1000);

	pinMode(YELLOW, OUTPUT);

	while(1)
	{
		if( yellowLEDProfiler++ > 200){
			yellowLEDProfiler = 0;
			vTaskSuspend(NULL);
		}

		digitalWrite(YELLOW, digitalRead(YELLOW) ^ 1);
		delay(50);
	}
}



