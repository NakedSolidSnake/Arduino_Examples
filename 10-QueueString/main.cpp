#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <string.h>
#include <stdio.h>

#define BUFF_MAX 30

#define YELLOW		5
#define RED			6
#define BLUE		7


QueueHandle_t xQueue;

static void vSenderTask(void *params);
static void vReceiveTask(void *params);

static void activeLed(const char * led);
static void executeCommand(const char *command);

static const char *commands[] = {
		"YELLOW ON",
		"YELLOW OFF",
		"RED ON",
		"RED OFF",
		"BLUE ON",
		"BLUE OFF",
};

TaskHandle_t  red_handle, yellow_handle;

void setup() {
	Serial.begin(115200);

	for(int i = YELLOW; i <= BLUE; i++){
		pinMode(i, OUTPUT);
	}

	xTaskCreate(vSenderTask, "Send Task", 240, NULL, 1, NULL);
	xTaskCreate(vReceiveTask, "Receive Task", 240, NULL, 2, NULL);

	xQueue = xQueueCreate(1, BUFF_MAX);

}

void loop() {

}

static void vSenderTask(void *params)
{
	(void)params;
	const TickType_t delay1s = pdMS_TO_TICKS(100000);
	int32_t sendValue = 0;
	BaseType_t queueRet = 0;

	while(1)
	{
		sendValue = (rand() % 6);
		Serial.print("Sender: ");
		Serial.println(commands[sendValue]);
		queueRet = xQueueSend(xQueue, commands[sendValue], 100);
		if(queueRet != pdTRUE){

		}
	}
}

static void vReceiveTask(void *params)
{
	(void)params;
	BaseType_t queueRet = 0;
	char recvValue[BUFF_MAX] = {0};

	while(1)
	{
		queueRet = xQueueReceive(xQueue, &recvValue, portMAX_DELAY);
		if(queueRet == pdTRUE){
			activeLed(recvValue);
		}
	}
}

static void activeLed(const char * led)
{
	for(int i = 0; i < (sizeof(commands) / sizeof(commands[0])); i++){
		if(strcmp(commands[i], led) == 0){
			executeCommand(commands[i]);
		}
	}
}

static void executeCommand(const char *command)
{
	char *str = command;
	char delim[] = " ";
	int pin;
	int state = LOW;
	Serial.print("Command: ");
	Serial.println(command);

	char *ptr = strtok(str, delim);
	Serial.print("LED :");

	while(ptr != NULL){
		Serial.print(ptr);
		Serial.print(" ");
		if((strcmp(ptr, "YELLOW")) == 0){
			pin = YELLOW;
		} else if((strcmp(ptr, "RED")) == 0){
			pin = RED;
		} else if((strcmp(ptr, "BLUE")) == 0){
			pin = BLUE;
		}else if((strcmp(ptr, "ON")) == 0){
			state = HIGH;
		} else if((strcmp(ptr, "OFF")) == 0){
			state = LOW;
		}
		ptr = strtok(NULL, delim);
	}
	Serial.println(" ");

	digitalWrite(pin, state);

}
