#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>

#define YELLOW		5
#define RED			6
#define BLUE		7


typedef int TaskProfiler;

TaskProfiler sendTaskProfiler;
TaskProfiler receiveTaskProfiler;

QueueHandle_t yearQueue;

static void vSenderTask(void *pvParams);
static void vReceiverTask(void *pvParams);

void setup()
{
	Serial.begin(9600);
	yearQueue = xQueueCreate(5, sizeof(int32_t));

	static int year1 = 1999;
	static int year2 = 2019;

	pinMode(RED, OUTPUT);

	xTaskCreate(vSenderTask, "Sender Task 1", 100, (void *)&year1, 1, NULL);
	xTaskCreate(vSenderTask, "Sender Task 2", 100, (void *)&year2, 1, NULL);
	xTaskCreate(vReceiverTask, "Sender Task 2", 100, NULL, 2, NULL);
}

void loop(){

}

static void vSenderTask(void *pvParams)
{
	BaseType_t qStatus;
	int32_t valueToSend = *(int32_t *)pvParams;

	while(1)
	{
		qStatus = xQueueSend(yearQueue, &valueToSend, 0);
		if(qStatus != pdPASS){
			Serial.println("Could not send to the queue");
		}
		digitalWrite(RED, HIGH);
	}

}

static void vReceiverTask(void *pvParams)
{
	BaseType_t qStatus;
	int32_t valueReceived;
	const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

	while(1)
	{
		qStatus = xQueueReceive(yearQueue, &valueReceived, xTicksToWait);
		if(qStatus == pdPASS){
			Serial.print("Data received successfully: ");
			Serial.println(valueReceived);
		}
		else{
			Serial.println("Could not receive from queue");
		}

		digitalWrite(RED, LOW);
	}

}
