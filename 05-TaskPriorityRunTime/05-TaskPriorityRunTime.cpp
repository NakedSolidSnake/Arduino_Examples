#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#define YELLOW		5
#define RED			6
#define BLUE		7

typedef int TaskProfiler;

TaskProfiler redLEDProfiler = 0;
TaskProfiler yellowLEDProfiler = 0;
TaskProfiler blueLEDProfiler = 0;

static void redBlinkLed(void *params);
static void yellowBlinkLed(void *params);
static void blueBlinkLed(void *params);

TaskHandle_t blue_handle, red_handle, yellow_handle;

void setup() {
	Serial.begin(115200);
	xTaskCreate(redBlinkLed, "RED Task", 128, NULL, 1, &red_handle);
	xTaskCreate(yellowBlinkLed, "Yellow Task", 128, NULL, 2, &yellow_handle);
//	xTaskCreate(blueBlinkLed, "Blue Task", 128, NULL, 2, &blue_handle);
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
		digitalWrite(RED, digitalRead(RED) ^ 1);
		red_priority = uxTaskPriorityGet(NULL);
		Serial.print("red priority: ");
		Serial.println(red_priority);
		if(red_priority == 3){
			vTaskDelay(100);
			//Sets own task priority
			vTaskPrioritySet(NULL, 1);
		}
		vTaskDelay(delay1s);
	}
}

static void yellowBlinkLed(void *params)
{
	(void)params;
	const TickType_t delay1s = pdMS_TO_TICKS(50);

	pinMode(YELLOW, OUTPUT);

	while(1)
	{
		digitalWrite(YELLOW, digitalRead(YELLOW) ^ 1);
		vTaskPrioritySet(red_handle, 3);
		vTaskDelay(delay1s);
	}
}

static void blueBlinkLed(void *params)
{
	(void)params;
	const TickType_t delay1s = pdMS_TO_TICKS(50);

	pinMode(BLUE, OUTPUT);

	while(1)
	{
		digitalWrite(BLUE, digitalRead(BLUE) ^ 1);
		vTaskDelay(delay1s);
	}
}

