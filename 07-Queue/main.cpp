#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>

#define YELLOW		5
#define RED			6
#define BLUE		7


QueueHandle_t xQueue;

static void vSenderTask(void *params);
static void vReceiveTask(void *params);

static void activeLed(int32_t led);

TaskHandle_t  red_handle, yellow_handle;

void setup() {
	Serial.begin(115200);

	for(int i = YELLOW; i <= BLUE; i++){
		pinMode(i, OUTPUT);
	}

	xTaskCreate(vSenderTask, "Send Task", 128, NULL, 1, NULL);
	xTaskCreate(vReceiveTask, "Receive Task", 128, NULL, 2, NULL);

	xQueue = xQueueCreate(5, sizeof(int32_t));

}

void loop() {

}

static void vSenderTask(void *params)
{
	(void)params;
	const TickType_t delay1s = pdMS_TO_TICKS(50000);
	int32_t sendValue = 0;
	BaseType_t queueRet = 0;

	while(1)
	{
		sendValue = (rand() % 3) + 5;
		queueRet = xQueueSend(xQueue, &sendValue, 0);
		if(queueRet != pdTRUE){

		}
		vTaskDelay(delay1s);
	}
}

static void vReceiveTask(void *params)
{
	(void)params;
	BaseType_t queueRet = 0;
	int32_t recvValue;

	while(1)
	{
		queueRet = xQueueReceive(xQueue, &recvValue, portMAX_DELAY);
		if(queueRet == pdTRUE){
			activeLed(recvValue);
			Serial.print("Value Received: ");
			Serial.println(recvValue);
		}
	}
}

static void activeLed(int32_t led)
{
	switch(led){

	case YELLOW:
		digitalWrite(YELLOW, digitalRead(YELLOW) ^ 1);
		break;

	case RED:
		digitalWrite(RED, digitalRead(RED) ^ 1);
		break;

	case BLUE:
		digitalWrite(BLUE, digitalRead(BLUE) ^ 1);
		break;
	default:
		return ;

	}
}
