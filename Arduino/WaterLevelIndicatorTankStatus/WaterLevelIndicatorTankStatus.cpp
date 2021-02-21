#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "include/sensors.h"
#include "include/LCD.h"
#include "include/messages.h"
#include "include/water_pump.h"

/**
 * 	The TaskSensor must notify TaskLCD using TaskNotify this will prevent
 * 	waste processor time updating LCD with the same information
 *
 */

static void hw_init(void);

static void vTaskSensor(void *pvParams);
static void vTaskLCD(void *pvParams);
static void vTaskWaterPump(void *pvParams);

static TaskHandle_t xLCDHandle;
static TaskHandle_t xWaterPumpHandle;
static int sensorOldState = 0;
static int sensorCurrentState = 0;
static int waterPumpControl = PUMP_OFF;

void setup() {
	hw_init();

	/* Init Tasks */
	BaseType_t xTaskResult;

	xTaskResult = xTaskCreate(vTaskSensor, "Task Sensor", 128, NULL, 1, NULL);
	if(xTaskResult != pdTRUE){
		while(1){
			Serial.println("Error Task Sensor");
			delay(1);
		}
	}

#if DEBUG
	Serial.println("Task Sensor Created");
#endif

	xTaskResult = xTaskCreate(vTaskLCD, "Task LCD", 128, NULL, 1, &xLCDHandle);
	if(xTaskResult != pdTRUE){
		while(1){
			Serial.println("Error Task LCD");
			delay(1);
		}
	}

#if DEBUG
	Serial.println("Task LCD Created");
#endif

	xTaskResult = xTaskCreate(vTaskWaterPump, "Task Water Pump", 128, NULL, 1, &xWaterPumpHandle);
		if(xTaskResult != pdTRUE){
			while(1){
				Serial.println("Error Task Water Pump");
				delay(1);
			}
		}

	#if DEBUG
		Serial.println("Task Water Pump Created");
	#endif


}

void loop() {

}

static void hw_init(void)
{
	Sensor_init();
	LCD_init();
	WATERPUMP_init();
	Serial.begin(115200);
}

static void vTaskSensor(void *pvParams)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

#if DEBUG
	Serial.println("Task Sensor Running...");
#endif

	while(1)
	{
		sensorCurrentState = Sensor_getState();
		if(sensorCurrentState != sensorOldState){
			sensorOldState = sensorCurrentState;
			//Notify LCD Task to update data
			xTaskNotifyGive(xLCDHandle);
		}

#if DEBUG
		Serial.print("Sensor Current: ");
		Serial.println(sensorCurrentState);
#endif

	}
}

static void vTaskLCD(void *pvParams)
{
	int xTaskNotification;
	int error = 0;

	LCD_printCenter(splash, LCD_LINE_1);
	char *msgPtr = NULL;

#if DEBUG
	Serial.println("Task LCD Running...");
#endif

	while(1)
	{
		xTaskNotification = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		if(xTaskNotification){
			//update LCD
			switch(sensorCurrentState){
			case MASK_EMPTY:
				msgPtr = tankEmpty;
				waterPumpControl = PUMP_ON;
				break;
			case MASK_EMPTY_L1:
				msgPtr = tankLevel1;
				break;
			case MASK_EMPTY_L1L2:
				msgPtr = tankLevel2;
				break;
			case MASK_EMPTY_L1L2L3:
				msgPtr = tankLevel3;
				break;
			case MASK_ALL_SENSORS:
				msgPtr = tankFull;
				waterPumpControl = PUMP_OFF;
				break;
			default:
				msgPtr = tankError;
				waterPumpControl = PUMP_OFF;
				error = 1;
			}

			LCD_printCenter(msgPtr, LCD_LINE_2);
			xTaskNotifyGive(xWaterPumpHandle);

			vTaskDelay(100);
			if(error){
				while(1){
					delay(1000);
					Serial.print("Verify which sensor has problem: ");
					for(int i = 0; i < 5; i++){
						Serial.print((sensorCurrentState >> i) & 0x01);
					}
					Serial.println();
					Serial.println("After fixed, reset the system.");
				}
			}
		}
	}
}

static void vTaskWaterPump(void *pvParams)
{
	int xTaskNotification;
	while(1)
	{
		xTaskNotification = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		if(xTaskNotification){
			WATERPUMP_set(waterPumpControl);
		}
	}
}
