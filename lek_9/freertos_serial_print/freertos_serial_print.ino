#include <Arduino_FreeRTOS.h>

SemaphoreHandle_t encoderSemaphore;

void aaa(void *pvParameters)
{

	TickType_t xLastWakeTime = xTaskGetTickCount();
	for (;;) {
		if (xSemaphoreTake(encoderSemaphore, portMAX_DELAY) == pdTRUE)
		{
			Serial.println("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
			xSemaphoreGive(encoderSemaphore);
		}
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(50)); 
	}
}

void bbb(void *pvParameters)
{

	TickType_t xLastWakeTime = xTaskGetTickCount();
	for (;;) {
		if (xSemaphoreTake(encoderSemaphore, portMAX_DELAY) == pdTRUE)
		{
			Serial.println("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
			xSemaphoreGive(encoderSemaphore);
		}
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(50)); 
	}
}

void setup() {
	Serial.begin(115200);
	encoderSemaphore = xSemaphoreCreateMutex();
	xTaskCreate(aaa, "aaa" , 1000, NULL, 1, NULL); 
	xTaskCreate(aaa, "bbb" , 1000, NULL, 1, NULL); 
	vTaskStartScheduler();
}

void loop() {
	// Nothing to do here since tasks handle everything
}
