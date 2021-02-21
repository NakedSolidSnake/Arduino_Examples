#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#define RED			6
#define YELLOW		5
#define BLUE		7

void vHW_init(void);
static void interruptInit(void);

static void redBlinkLed(void *params);
TaskHandle_t xLedRedHandle;

void setup() {
	vHW_init();
	xTaskCreate(redBlinkLed, "RED Task", 128, NULL, 1, &xLedRedHandle);

	interruptInit();
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
	static uint32_t thread_notification;
	while(1)
	{

		thread_notification = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		if(thread_notification)
			digitalWrite(RED, digitalRead(RED) ^ 1);
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
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	uint32_t receivedNumber;
	TCNT1 = timer1_counter;
	vTaskNotifyGiveFromISR(xLedRedHandle, &xHigherPriorityTaskWoken);

}
