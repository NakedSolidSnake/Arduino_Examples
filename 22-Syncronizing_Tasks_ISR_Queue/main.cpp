#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>


#define YELLOW		5
#define RED			6
#define BLUE		7

static void vIntegerGenerator(void *params);
static void vStringPrinter(void *params);

static void interruptInit(void);

QueueHandle_t xInterQueue, xStringQueue;

static const char *pcStrings[] =
{
		"Hello\r\n",
		"I\r\n",
		"am\r\n",
		"here\r\n"
};


void setup() {

	BaseType_t xTimerBlueStarted, xTimerRedStarted;

	Serial.begin(115200);

	for(int i = YELLOW; i <= BLUE; i++){
		pinMode(i, OUTPUT);
	}

	xInterQueue = xQueueCreate(10, sizeof(uint32_t));
	xStringQueue = xQueueCreate(10, sizeof(char *));

	xTaskCreate(vIntegerGenerator, "Integer Generator", 128, NULL, 1, NULL);
	xTaskCreate(vStringPrinter, "String Printer", 128, NULL, 1, NULL);

	interruptInit();
}

void loop() {

}

static void vIntegerGenerator(void *params)
{
	TickType_t xLastExecutionTime;
	const TickType_t xDelay200ms = pdMS_TO_TICKS(200);
	uint32_t valueToSend = 0;

	xLastExecutionTime = xTaskGetTickCount();
	while(1)
	{
		vTaskDelayUntil(&xLastExecutionTime, xDelay200ms);
		for(int i = 0; i < 5; i++){
			xQueueSendToBack(xInterQueue, &valueToSend, 0);
			valueToSend++;
		}
	}
}

static void vStringPrinter(void *params)
{
	char *pcString;
	while(1)
	{
		xQueueReceive(xStringQueue, &pcString, portMAX_DELAY);
		Serial.println(pcString);
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
	uint32_t receivedNumber;
	TCNT1 = timer1_counter;
	xQueueReceiveFromISR(xInterQueue, &receivedNumber, pdFALSE);
	receivedNumber &= 0x03;
	xQueueSendToBackFromISR(xStringQueue, &pcStrings[receivedNumber], 0);
}
