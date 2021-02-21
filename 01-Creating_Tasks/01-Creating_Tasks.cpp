#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#define RED			5
#define YELLOW		6
#define BLUE		7

void vHW_init(void);

static void redBlinkLed(void *params);
static void yellowBlinkLed(void *params);
static void blueBlinkLed(void *params);

void setup() {
	vHW_init();
	xTaskCreate(redBlinkLed, "RED Task", 128, NULL, 1, NULL);
	xTaskCreate(yellowBlinkLed, "Yellow Task", 128, NULL, 1, NULL);
	xTaskCreate(blueBlinkLed, "Blue Task", 128, NULL, 1, NULL);
}

void loop() {

}

void vHW_init(void)
{
	Serial.begin(115200);
	for(int i = RED; i <= BLUE; i++){
		pinMode(i, OUTPUT);
	}
}

static void redBlinkLed(void *params)
{
	(void)params;
	const TickType_t delay1s = pdMS_TO_TICKS(1000000);
	while(1)
	{
		digitalWrite(RED, digitalRead(RED) ^ 1);
		vTaskDelay(delay1s);
	}
}

static void yellowBlinkLed(void *params)
{
	(void)params;
	const TickType_t delay1s = pdMS_TO_TICKS(1000000);
	while(1)
	{
		digitalWrite(YELLOW, digitalRead(YELLOW) ^ 1);
		vTaskDelay(delay1s);
	}
}

static void blueBlinkLed(void *params)
{
	(void)params;
	const TickType_t delay1s = pdMS_TO_TICKS(1000000);
	while(1)
	{
		digitalWrite(BLUE, digitalRead(BLUE) ^ 1);
		vTaskDelay(delay1s);
	}
}
