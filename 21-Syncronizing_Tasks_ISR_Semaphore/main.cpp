#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>


#define YELLOW		5
#define RED			6
#define BLUE		7

static void redBlinkLed(void *params);
static void yellowBlinkLed(void *params);
static void blueBlinkLed(void *params);

static void interruptInit(void);


SemaphoreHandle_t xCountingSemaphore;

void setup() {

	BaseType_t xTimerBlueStarted, xTimerRedStarted;

	Serial.begin(115200);

	for(int i = YELLOW; i <= BLUE; i++){
		pinMode(i, OUTPUT);
	}

	xCountingSemaphore = xSemaphoreCreateCounting(1, 0);

	xTaskCreate(redBlinkLed, "RED Task", 128, NULL, 1, NULL);
	xTaskCreate(yellowBlinkLed, "Yellow Task", 128, NULL, 1, NULL);
	xTaskCreate(blueBlinkLed, "Blue Task", 128, NULL, 1, NULL);
	xSemaphoreGive(xCountingSemaphore);

	interruptInit();
}

void loop() {

}

static void redBlinkLed(void *params)
{
	(void)params;
	while(1)
	{
		xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);
		digitalWrite(RED, digitalRead(RED) ^ 1);
	}
}

static void yellowBlinkLed(void *params)
{
	(void)params;
	while(1)
	{
		xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);
		digitalWrite(YELLOW, digitalRead(YELLOW) ^ 1);
	}
}

static void blueBlinkLed(void *params)
{
	(void)params;
	while(1)
	{
		xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);
		digitalWrite(BLUE, digitalRead(BLUE) ^ 1);
	}
}


const static int timer1_counter = 34286;

static void interruptInit(void)
{
	noInterrupts();
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = timer1_counter;
	TCCR1B |= (1 << CS12);
	TIMSK1 |= (1 << TOIE1);

	interrupts();
}

ISR(TIMER1_OVF_vect)
{
	TCNT1 = timer1_counter;
	xSemaphoreGiveFromISR(xCountingSemaphore, pdFALSE);
}
