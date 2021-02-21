#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>


#define YELLOW		5
#define RED			6
#define BLUE		7

static void redBlinkLed(void *params);
static void yellowBlinkLed(void *params);
static void blueBlinkLed(void *params);

static void print(const char *msg);


SemaphoreHandle_t xMutex;

void setup() {


	Serial.begin(115200);

	for(int i = YELLOW; i <= BLUE; i++){
		pinMode(i, OUTPUT);
	}

	xMutex = xSemaphoreCreateMutex();

	xTaskCreate(redBlinkLed, "RED Task", 128, NULL, 1, NULL);
	xTaskCreate(yellowBlinkLed, "Yellow Task", 128, NULL, 1, NULL);
	xTaskCreate(blueBlinkLed, "Blue Task", 128, NULL, 1, NULL);
	xSemaphoreGive(xMutex);
}

void loop() {

}

static void redBlinkLed(void *params)
{
	(void)params;
	while(1)
	{
		print("Task LED Red is blinking.");
		digitalWrite(RED, digitalRead(RED) ^ 1);
	}
}

static void yellowBlinkLed(void *params)
{
	(void)params;
	while(1)
	{
		print("Task LED Yellow is blinking.");
		digitalWrite(YELLOW, digitalRead(YELLOW) ^ 1);
	}
}

static void blueBlinkLed(void *params)
{
	(void)params;
	while(1)
	{
		print("Task LED Blue is blinking.");
		digitalWrite(BLUE, digitalRead(BLUE) ^ 1);
	}
}

static void print(const char *msg)
{
	xSemaphoreTake(xMutex, portMAX_DELAY);
	Serial.println(msg);
	xSemaphoreGive(xMutex);
}
