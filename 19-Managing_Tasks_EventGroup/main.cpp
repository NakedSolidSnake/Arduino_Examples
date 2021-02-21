#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <event_groups.h>

#define YELLOW	5
#define RED		6
#define BLUE	7

#define TASK1_BIT (1UL << 0UL)
#define TASK2_BIT (1UL << 1UL)
#define TASK3_BIT (1UL << 2UL)

EventGroupHandle_t xEventGroup;



static void InputTask1(void *pvParams);
static void InputTask2(void *pvParams);
static void InputTask3(void *pvParams);
static void OutputTask(void *pvParams);


void setup(){
	Serial.begin(115200);
	for(int i = YELLOW; i <= BLUE; i++){
		pinMode(i, OUTPUT);
	}

	xEventGroup = xEventGroupCreate();

	xTaskCreate(InputTask1, "Input Task 1", 100, NULL, 1, NULL);
	xTaskCreate(InputTask2, "Input Task 2", 100, NULL, 1, NULL);
	xTaskCreate(InputTask3, "Input Task 3", 100, NULL, 1, NULL);
	xTaskCreate(OutputTask, "Output Task", 100, NULL, 1, NULL);

}

void loop(){

}

static void InputTask1(void *pvParams)
{
	const TickType_t xDelay500ms = pdMS_TO_TICKS(500);

	while(1)
	{
		xEventGroupSetBits(xEventGroup, TASK1_BIT);
		vTaskDelay(xDelay500ms);
	}
}

static void InputTask2(void *pvParams)
{
	const TickType_t xDelay500ms = pdMS_TO_TICKS(500);

	while(1)
	{
		xEventGroupSetBits(xEventGroup, TASK2_BIT);
		vTaskDelay(xDelay500ms);
	}
}

static void InputTask3(void *pvParams)
{
	const TickType_t xDelay500ms = pdMS_TO_TICKS(500);

	while(1)
	{
		xEventGroupSetBits(xEventGroup, TASK3_BIT);
		vTaskDelay(xDelay500ms);
	}
}


static void OutputTask(void *pvParams)
{
	const EventBits_t xBitsWaitFor = (TASK1_BIT | TASK2_BIT | TASK3_BIT);
	EventBits_t xEventGroupValue;

	while(1)
	{
		xEventGroupValue = xEventGroupWaitBits(xEventGroup,
											   xBitsWaitFor,
											   pdTRUE,
											   pdTRUE,
											   portMAX_DELAY);

		if(xEventGroupValue & TASK1_BIT){
			digitalWrite(RED, digitalRead(RED) ^1);
		}

		if(xEventGroupValue & TASK2_BIT){
			digitalWrite(YELLOW, digitalRead(YELLOW) ^1);
		}

		if(xEventGroupValue & TASK3_BIT){
			digitalWrite(BLUE, digitalRead(BLUE) ^1);
		}


	}
}

