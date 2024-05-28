#include <PID_v1.h>

// Define pin numbers
#define PWM_PIN 10
#define DIR_PIN 12
#define ENCODER_A_PIN 2
#define ENCODER_B_PIN 9
#define POTENTIOMETER_PIN A0

// Define variables
volatile long encoderCount = 0;
double motorSpeed = 0;
double motorSetpoint = 0;
double motorOutput = 0;

// PID parameters
double Kp = 1.0;
double Ki = 1.0;
double Kd = 1.0;
PID motorPID(&motorSpeed, &motorOutput, &motorSetpoint, Kp, Ki, Kd, DIRECT);

void readEncoder()
{
}

// Task to read speed reference from potentiometer
void readPotentiometer(void *pvParameters)
{
}

// Task to read controller parameters from serial input
void readSerialParams(void *pvParameters)
{
}

// Task to control motor speed using PID
void controlMotorSpeed(void *pvParameters)
{
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
	// Initialize PID controller
	motorPID.SetMode(AUTOMATIC);
	motorPID.SetSampleTime(100);
}

void loop(){/*Nothing to do here since tasks handle everything*/}
