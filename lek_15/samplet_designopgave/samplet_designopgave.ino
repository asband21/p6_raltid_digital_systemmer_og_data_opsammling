#include <Arduino_FreeRTOS.h>
#include <Arduino.h>
#include <PID_v1.h>
#include <semphr.h>  

// Define pin numbers
#define PWM_PIN 10
#define DIR_PIN 12
#define ENCODER_A_PIN 2
#define ENCODER_B_PIN 9
#define POTENTIOMETER_PIN A0

// Define variables
volatile long encoderCountOlde = 0 ;
volatile long encoderCount = 0;
double motorSpeed = 0;
double motorSetpoint = 0;
double motorOutput = 0;

// PID parameters
double Kp = 6.0;
double Ki = 4.0;
double Kd = 3.0;
PID motorPID(&motorSpeed, &motorOutput, &motorSetpoint, Kp, Ki, Kd, DIRECT);

// Semaphore
SemaphoreHandle_t encoderSemaphore;

// Previous state of encoder pins
int lastEncoderAState = LOW;
int lastEncoderBState = LOW;

// Function to read encoder
//måske interropt?
void readEncoder() {
	int encoderAState = digitalRead(ENCODER_A_PIN);
	int encoderBState = digitalRead(ENCODER_B_PIN);

	// Checking if encoder is standing still
	if (encoderAState != lastEncoderAState) {
		if (encoderBState == HIGH) {
			encoderCount++;
		} else {
			encoderCount--;
		}
		lastEncoderAState = encoderAState;
	}
	vTaskDelayUntil(pdMS_TO_TICKS(5)); // Delay to reduce CPU load
}

// Task to read speed reference from potentiometer
void readPotentiometer(void *pvParameters) {
	for (;;) {
		int potValue = analogRead(POTENTIOMETER_PIN);
		motorSetpoint =  map(potValue, 0, 1023, 0, 255); // Map potentiometer value to target speed
		vTaskDelayUntil(pdMS_TO_TICKS(100)); // Delay to reduce CPU load 
	}
}

// Task to read controller parameters from serial input
void readSerialParams(void *pvParameters) {
	for (;;) {
		if (Serial.available() > 0) {
			String input = Serial.readStringUntil('\n');
			// Parse input and update PID parameters
			if (input.length() > 0) {
				// Expected input format: "Kp,Ki,Kd"
				double newKp, newKi, newKd;
				int commaIndex1 = input.indexOf(',');
				int commaIndex2 = input.indexOf(',', commaIndex1 + 1);
				if (commaIndex1 != -1 && commaIndex2 != -1) {
					newKp = input.substring(0, commaIndex1).toDouble();
					newKi = input.substring(commaIndex1 + 1, commaIndex2).toDouble();
					newKd = input.substring(commaIndex2 + 1).toDouble();
					if (xSemaphoreTake(encoderSemaphore, portMAX_DELAY) == pdTRUE) {
						// Update PID parameters
						motorPID.SetTunings(newKp, newKi, newKd);
						xSemaphoreGive(encoderSemaphore);
					}
				}
			}
		}
		vTaskDelay(pdMS_TO_TICKS(100)); // Delay to reduce CPU load
		//vTaskDelayUntil() og er 100 ikke er meget? 
	}
}

// Task to control motor speed using PID
void controlMotorSpeed(void *pvParameters) {
	for (;;) {
		if (xSemaphoreTake(encoderSemaphore, portMAX_DELAY) == pdTRUE) {
	 		//readEncoder();
			motorSpeed = (encoderCount - encoderCountOlde) * (10.0 / 500.0); // Calculate motor speed based on encoder counts in rpm
			encoderCountOlde = encoderCount;
			xSemaphoreGive(encoderSemaphore);
		}
		motorPID.Compute(); // Compute PID output
		analogWrite(PWM_PIN, abs(motorOutput)); // Write PWM signal to motor 
							// Motor needs DIR_PIN to slow down
		digitalWrite(DIR_PIN, (motorOutput >= 0) ? HIGH : LOW); // Determine direction based on PID output
		vTaskDelayUntil(pdMS_TO_TICKS(100)); // Delay to reduce CPU load
	}
}

void setup() {
	// Initialize serial communication
	Serial.begin(115200);

	// Configure pin modes
	pinMode(PWM_PIN, OUTPUT);
	pinMode(DIR_PIN, OUTPUT);
	pinMode(ENCODER_A_PIN, INPUT_PULLUP);
	pinMode(ENCODER_B_PIN, INPUT_PULLUP);

	// Create semaphore
	encoderSemaphore = xSemaphoreCreateMutex();

	// Initialize PID controller
	motorPID.SetMode(AUTOMATIC);
	motorPID.SetSampleTime(100);

	// Create tasks
	xTaskCreate(readEncoder, "encoder" , 1000, NULL, 1, NULL);   //1, NULL);
	xTaskCreate(controlMotorSpeed, "MotorControlTask" , 1000, NULL, 2, NULL);   //1, NULL);
	xTaskCreate(readPotentiometer, "PotentiometerTask", 1000, NULL, 3, NULL);  //1, NULL);
	xTaskCreate(readSerialParams,  "SerialParamsTask" , 1000, NULL, 4, NULL);    //2, NULL);

	// Start the scheduler
	vTaskStartScheduler();
}

void loop() {
	// Nothing to do here since tasks handle everything
}
