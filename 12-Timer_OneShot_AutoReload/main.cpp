#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <timers.h>


#define YELLOW		5
#define RED			6
#define BLUE		7

#define ONE_SHOT_TIMER_PERIOD		(pdMS_TO_TICKS(500))
#define AUTO_RELOAD_TIMER_PERIOD	(pdMS_TO_TICKS(300))


TimerHandle_t xTimer1, xTimer2;
BaseType_t xTimer1Started, xTimer2Started;

static void prvOneShotTimerCallback(TimerHandle_t xTimer);
static void prvAutoReloadTimerCallback(TimerHandle_t xTimer);


void setup() {
	Serial.begin(115200);

	for(int i = YELLOW; i <= BLUE; i++){
		pinMode(i, OUTPUT);
	}

	xTimer1 = xTimerCreate("One Shot",
							ONE_SHOT_TIMER_PERIOD,
							pdFALSE,
							0,
							prvOneShotTimerCallback);

	xTimer2 = xTimerCreate("Reload",
								AUTO_RELOAD_TIMER_PERIOD,
								pdTRUE,
								0,
								prvAutoReloadTimerCallback);

	if(xTimer1 != NULL && xTimer2 != NULL){
		xTimer1Started = xTimerStart(xTimer1, 0);
		xTimer2Started = xTimerStart(xTimer2, 0);
	}

	while((xTimer1Started != pdPASS && xTimer2Started != pdPASS))
	{
	}
}

void loop() {

}

static void prvOneShotTimerCallback(TimerHandle_t xTimer)
{
	static TickType_t xTimerNow;
	xTimerNow = xTaskGetTickCount();
	Serial.print(" One-shot timer callback execution : ");
	Serial.println(xTimerNow);
}

static void prvAutoReloadTimerCallback(TimerHandle_t xTimer)
{
	static TickType_t xTimerNow;
	xTimerNow = xTaskGetTickCount();
	Serial.print(" Auto-Reload timer callback execution : ");
	Serial.println(xTimerNow);
}
