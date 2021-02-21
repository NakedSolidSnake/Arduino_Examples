#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#define RED			5
#define YELLOW		6
#define BLUE		7

int redLEDProfiler = 0;
int yellowLEDProfiler = 0;
int blueLEDProfiler = 0;

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
	while(1){
		redLEDProfiler++;
		Serial.print("redLEDProfiler: ");
		Serial.println(redLEDProfiler);
	}
}

static void yellowBlinkLed(void *params)
{
	while(1){
		yellowLEDProfiler++;
		Serial.print("yellowLEDProfiler: ");
		Serial.println(yellowLEDProfiler);
	}
}

static void blueBlinkLed(void *params)
{
	while(1){
		blueLEDProfiler++;
		Serial.print("blueLEDProfiler: ");
		Serial.println(blueLEDProfiler);
	}
}
