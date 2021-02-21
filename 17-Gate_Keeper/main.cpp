#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>


static const char *pcStringToPrint[] =
{
		"Task 1 ################################################## Task 1\r\n",
		"Task 2 -------------------------------------------------- Task 2\r\n",
		"Tick Hook %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% TICK Hook\r\n"
};


static void vOutputTask(void *pvParams);
static void GateKeeperTask(void *pvParams);

QueueHandle_t xPrintQueue;

void setup(){

	Serial.begin(115200);

	xPrintQueue = xQueueCreate(5, sizeof(char *));
	xTaskCreate(vOutputTask, "Printer 1", 100, (void *)0, 1, NULL);
	xTaskCreate(vOutputTask, "Printer 2", 100, (void *)0, 1, NULL);

	xTaskCreate(GateKeeperTask, "GateKeeper", 100, NULL, 0, NULL);
}

void loop(){

}

static void vOutputTask(void *pvParams)
{
	int idx = (int)pvParams;

	while(1)
	{
		xQueueSend(xPrintQueue, &pcStringToPrint[idx], 0);
	}
}

static void GateKeeperTask(void *pvParams)
{
	char *pcMessageToPrint;
	while(1)
	{
		xQueueReceive(xPrintQueue, pcMessageToPrint, portMAX_DELAY);
		Serial.println(pcMessageToPrint);
	}
}

void vApplicationTickHook(void){

}
