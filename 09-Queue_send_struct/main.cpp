#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>

#define YELLOW		5
#define RED			6
#define BLUE		7

typedef enum
{
	eSender1,
	eSender2
}DataSource_t;

typedef struct
{
	char ucValue[10];
	DataSource_t eDataSource;
}Data_t;

static const Data_t xStructToSend[2] = {
		{"Sender 1", eSender1},
		{"Sender 2", eSender2},
};

QueueHandle_t xQueue;

static void vSenderTask(void *pvParams);
static void vReceiverTask(void *pvParams);

void setup()
{
	Serial.begin(9600);
	xQueue = xQueueCreate(3, sizeof(Data_t));

	xTaskCreate(vSenderTask, "Sender Task 1", 240, (void *)&xStructToSend[0], 2, NULL);
	xTaskCreate(vSenderTask, "Sender Task 2", 240, (void *)&xStructToSend[1], 2, NULL);
	xTaskCreate(vReceiverTask, "Sender Task 2", 240, NULL, 1, NULL);
}

void loop(){

}

static void vSenderTask(void *pvParams)
{
	BaseType_t xStatus;
	const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

	while(1)
	{
		xStatus = xQueueSend(xQueue, pvParams, xTicksToWait);
		if(xStatus != pdPASS){
			Serial.println("Could not send to the queue");
		}
	}

}

static void vReceiverTask(void *pvParams)
{
	BaseType_t qStatus;
	Data_t valueReceived;
	uint8_t data;

	while(1)
	{
		qStatus = xQueueReceive(xQueue, &valueReceived, 0);
		if(qStatus == pdPASS){
			Serial.print("Data received successfully: ");
			if(valueReceived.eDataSource == eSender1){


			}else if(valueReceived.eDataSource == eSender2){

			}
			Serial.print("Data: ");
			Serial.println(valueReceived.ucValue);
		}
		else{
			Serial.println("Could not receive from queue");
		}
	}
}
