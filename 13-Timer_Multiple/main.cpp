#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <timers.h>


#define YELLOW		5
#define RED			6
#define BLUE		7

#define BLUE_TIMER_PERIOD		(pdMS_TO_TICKS(500))
#define RED_TIMER_PERIOD		(pdMS_TO_TICKS(300))


TimerHandle_t xTimerBlue, xTimerRed;


static void prvAutoReloadTimerCallback(TimerHandle_t xTimer);


void setup() {

	BaseType_t xTimerBlueStarted, xTimerRedStarted;

	Serial.begin(115200);

	for(int i = YELLOW; i <= BLUE; i++){
		pinMode(i, OUTPUT);
	}

	xTimerRed = xTimerCreate("RED TIMER",
							RED_TIMER_PERIOD,
							pdTRUE,
							0,
							prvAutoReloadTimerCallback);

	xTimerBlue = xTimerCreate("BLUE TIMER",
								BLUE_TIMER_PERIOD,
								pdTRUE,
								0,
								prvAutoReloadTimerCallback);

	if(xTimerRed != NULL && xTimerBlue != NULL){
		xTimerRedStarted = xTimerStart(xTimerRed, 0);
		xTimerBlueStarted = xTimerStart(xTimerBlue, 0);
	}

	while((xTimerRedStarted != pdPASS && xTimerBlueStarted != pdPASS))
	{
	}
}

void loop() {

}

static void prvAutoReloadTimerCallback(TimerHandle_t xTimer)
{
	if(xTimer == xTimerRed){
		static int times = 0;
		Serial.println("Red Timer");
		digitalWrite(RED, digitalRead(RED) ^ 1);
		if(times++ == 100){
			xTimerChangePeriod(xTimer, pdMS_TO_TICKS(100), 10);
		}else if (times == 200){
			xTimerChangePeriod(xTimer, RED_TIMER_PERIOD, 10);
			times = 0;
		}

	} else if(xTimer == xTimerBlue){
		Serial.println("Blue Timer");
		digitalWrite(BLUE, digitalRead(BLUE) ^ 1);
	}
}
