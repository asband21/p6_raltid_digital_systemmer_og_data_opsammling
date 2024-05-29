#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

void task1(void *pvParameters);
void task2(void *pvParameters);


void task1(void *pvParameters) {
    while (1) {
        unsigned long startTime = millis();
        Serial.print("Task 1 Start Time: ");
        Serial.println(startTime);

        // Simulate computation for 20 ms
        delay(20);

        unsigned long endTime = millis();
        Serial.print("Task 1 End Time: ");
        Serial.println(endTime);

        // Time between ready and completion instant
        unsigned long readyTime = endTime - startTime;
        Serial.print("Task 1 Ready to Completion Time: ");
        Serial.println(readyTime);

        // Wait for next period
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}



void task2(void *pvParameters) {
    while (1) {
        unsigned long startTime = millis();
        Serial.print("Task 2 Start Time: ");
        Serial.println(startTime);

        // Simulate computation for 20 ms
        delay(20);

        unsigned long endTime = millis();
        Serial.print("Task 2 End Time: ");
        Serial.println(endTime);

        // Time between ready and completion instant
        unsigned long readyTime = endTime - startTime;
        Serial.print("Task 2 Ready to Completion Time: ");
        Serial.println(readyTime);

        // Wait for next period
        vTaskDelay(80 / portTICK_PERIOD_MS);
    }
}

void setup() {
    Serial.begin(115200);
    xTaskCreate(task1, "Task1", 100, NULL, 1, NULL);
    xTaskCreate(task2, "Task2", 100, NULL, 2, NULL);
    vTaskStartScheduler();
}

void loop() {
    // FreeRTOS handles the tasks, loop can remain empty.

}
