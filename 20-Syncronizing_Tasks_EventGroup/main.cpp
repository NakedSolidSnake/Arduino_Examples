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
const EventBits_t xBitsWaitFor = (TASK1_BIT | TASK2_BIT | TASK3_BIT);


static void InputTask1(void *pvParams);
static void InputTask2(void *pvParams);
static void InputTask3(void *pvParams);


void setup(){
	Serial.begin(115200);
	for(int i = YELLOW; i <= BLUE; i++){
		pinMode(i, OUTPUT);
	}

	xEventGroup = xEventGroupCreate();

	xTaskCreate(InputTask1, "Input Task 1", 100, NULL, 1, NULL);
	xTaskCreate(InputTask2, "Input Task 2", 100, NULL, 1, NULL);
	xTaskCreate(InputTask3, "Input Task 3", 100, NULL, 1, NULL);

}

void loop(){

}

static void InputTask1(void *pvParams)
{
	const TickType_t xDelay500ms = pdMS_TO_TICKS(500);
	EventBits_t uxReturn;

	while(1)
	{
		uxReturn = xEventGroupSync(xEventGroup,
						TASK1_BIT,
						xBitsWaitFor,
						portMAX_DELAY);

		if((uxReturn & xBitsWaitFor) == xBitsWaitFor){
			digitalWrite(YELLOW, digitalRead(YELLOW) ^1);
			vTaskDelay(xDelay500ms);
		}
	}
}

static void InputTask2(void *pvParams)
{
	const TickType_t xDelay500ms = pdMS_TO_TICKS(500);
	EventBits_t uxReturn;
	while(1)
	{
		uxReturn = xEventGroupSync(xEventGroup,
				TASK2_BIT,
				xBitsWaitFor,
				portMAX_DELAY);

		if((uxReturn & xBitsWaitFor) == xBitsWaitFor){
			digitalWrite(RED, digitalRead(RED) ^1);
			vTaskDelay(xDelay500ms);
		}
	}
}

static void InputTask3(void *pvParams)
{
	const TickType_t xDelay500ms = pdMS_TO_TICKS(500);

	EventBits_t uxReturn;
		while(1)
		{
			uxReturn = xEventGroupSync(xEventGroup,
					TASK3_BIT,
					xBitsWaitFor,
					portMAX_DELAY);

			if((uxReturn & xBitsWaitFor) == xBitsWaitFor){
				digitalWrite(BLUE, digitalRead(BLUE) ^1);
				vTaskDelay(xDelay500ms);
			}
		}
}
