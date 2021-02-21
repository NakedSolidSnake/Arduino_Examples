#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <event_groups.h>

#define YELLOW	5
#define RED		6
#define BLUE	7

#define TASK1_BIT (1UL << 0UL)
#define TASK2_BIT (1UL << 1UL)

EventGroupHandle_t xEventGroup;



static void EventBitSettingTask(void *pvParams);
static void EventBitReadingTask(void *pvParams);


void setup(){
	Serial.begin(115200);
	for(int i = YELLOW; i <= BLUE; i++){
		pinMode(i, OUTPUT);
	}

	xEventGroup = xEventGroupCreate();

	xTaskCreate(EventBitSettingTask, "Bit Setter", 100, NULL, 1, NULL);
	xTaskCreate(EventBitReadingTask, "Bit Setter", 100, NULL, 1, NULL);

}

void loop(){

}

static void EventBitSettingTask(void *pvParams)
{
	const TickType_t xDelay500ms = pdMS_TO_TICKS(500);

	while(1)
	{
		xEventGroupSetBits(xEventGroup, TASK1_BIT);
		vTaskDelay(xDelay500ms);
		xEventGroupSetBits(xEventGroup, TASK2_BIT);
		vTaskDelay(xDelay500ms);

	}
}

static void EventBitReadingTask(void *pvParams)
{
	const EventBits_t xBitsWaitFor = (TASK1_BIT | TASK2_BIT);
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


	}
}
