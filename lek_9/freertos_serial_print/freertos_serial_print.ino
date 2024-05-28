#include <Arduino_FreeRTOS.h>
#include <semphr.h>
SemaphoreHandle_t printSemaphore;

void aaa(void *pvParameters)
{
	TickType_t xLastWakeTime = xTaskGetTickCount();
	for (;;)
	{
		if (xSemaphoreTake( printSemaphore, 0 ) == pdTRUE)
		{
			Serial.println("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
			xSemaphoreGive(printSemaphore);
		}
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(50)); 
	}
}

void bbb(void *pvParameters)
{

	TickType_t xLastWakeTime = xTaskGetTickCount();
	for (;;)
	{
		if (xSemaphoreTake( printSemaphore, 0 ) == pdTRUE)
		{
			Serial.println("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
			xSemaphoreGive(printSemaphore);
		}
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(50)); 
	}
}

void setup()
{
	Serial.begin(115200);
	printSemaphore = xSemaphoreCreateMutex();
	xTaskCreate(aaa, "aaa" , 1000, NULL, 1, NULL); 
	xTaskCreate(bbb, "bbb" , 1000, NULL, 1, NULL); 
	vTaskStartScheduler();
}
void loop()
{
	// Nothing to do here since tasks handle everything
}
