#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>

#define YELLOW		5
#define RED			6
#define BLUE		7


QueueHandle_t xQueue1;
QueueHandle_t xQueue2;

QueueSetHandle_t xQueueSet;

static void vSenderTask1(void *params);
static void vSenderTask2(void *params);
static void vReceiveTask(void *params);


void setup() {
	Serial.begin(115200);

	for(int i = YELLOW; i <= BLUE; i++){
		pinMode(i, OUTPUT);
	}

	xQueue1 = xQueueCreate(1, sizeof(char *));
	xQueue2 = xQueueCreate(1, sizeof(char *));

	xQueueSet = xQueueCreateSet(1 * 2);

	xQueueAddToSet(xQueue1, xQueueSet);
	xQueueAddToSet(xQueue2, xQueueSet);

	xTaskCreate(vSenderTask1, "Send Task 1", 240, NULL, 1, NULL);
	xTaskCreate(vSenderTask2, "Send Task 2", 240, NULL, 1, NULL);

	xTaskCreate(vReceiveTask, "Receive Task", 240, NULL, 2, NULL);


}

void loop() {

}

static void vSenderTask1(void *params)
{
	(void)params;
	const TickType_t xBlockTime = pdMS_TO_TICKS(100);
	const char *const messageToSend = " Message from Sender 1";


	while(1)
	{
		vTaskDelay(xBlockTime);
		xQueueSend(xQueue1, &messageToSend, 0);
	}
}

static void vSenderTask2(void *params)
{
	(void)params;
	const TickType_t xBlockTime = pdMS_TO_TICKS(100);
	const char *const messageToSend = " Message from Sender 2";


	while(1)
	{
		vTaskDelay(xBlockTime);
		xQueueSend(xQueue2, &messageToSend, 0);
	}
}



static void vReceiveTask(void *params)
{
	(void)params;

	QueueHandle_t xQueueThatContainsData;
	char *pcReceivedString;


	while(1)
	{
		xQueueThatContainsData = (QueueHandle_t) xQueueSelectFromSet(xQueueSet, portMAX_DELAY);
		xQueueReceive(xQueueThatContainsData, &pcReceivedString, 0);
		Serial.println(pcReceivedString);
	}
}
