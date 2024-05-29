#include <Arduino_FreeRTOS.h>
int data[20];
void analog(void *pvParameters)
{
	TickType_t xLastWakeTime = xTaskGetTickCount();
	for (int i = 0;; i = ++i % 20)
	{
		data[i] = analogRead(1);
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(10));
	}
}

void print(void *pvParameters)
{

	TickType_t xLastWakeTime = xTaskGetTickCount();
	for (;;)
	{
		for(int i = 0; i < 20; i++)
			Serial.println(data[i]);
		Serial.println("----------------------------------------");
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000)); 
	}
}

void setup() {
	Serial.begin(115200);
	xTaskCreate(analog, "analog" , 1000, NULL, 1, NULL); 
	xTaskCreate(print, "print" , 1000, NULL, 2, NULL); 
	vTaskStartScheduler();
}
void loop() {
	// Nothing to do here since tasks handle everything
}
