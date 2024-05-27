// Define the motor control pins
const int pwmPin = 10;  // PWM control pin
const int dirPin = 12;  // Direction control pin
const int encoderPinA = 2;  // Encoder pin A
const int encoderPinB = 9;  // Encoder pin B

// Variables for encoder
volatile long encoderCount = 0;

// Number of pulses per revolution (depends on the encoder specifications)
const int pulsesPerRevolution = 500;  // Example value, replace with your encoder's actual value

void setup() {
  // Initialize motor control pins
  pinMode(pwmPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  
  // Initialize encoder pins
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  
  // Attach interrupts for the encoder
  attachInterrupt(digitalPinToInterrupt(encoderPinA), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), encoderISR, CHANGE);
  
  // Start serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Example to rotate motor for testing
  rotateMotor(30, true);  // Rotate 30 revolutions CW
  delay(3000);            // Wait for 3 seconds
  rotateMotor(30, false); // Rotate 30 revolutions CCW
  delay(3000);            // Wait for 3 seconds
  
  // Print the encoder count
  Serial.print("Encoder Count: ");
  Serial.println(encoderCount);
  delay(1000);  // Wait for 1 second
}

void setMotorSpeed(int speed) {
  analogWrite(pwmPin, speed);
}

void setMotorDirection(bool direction) {
  digitalWrite(dirPin, direction);
}

void rotateMotor(int revolutions, bool direction) {
  // Calculate the target count based on the number of pulses per revolution
  long targetCount = revolutions * pulsesPerRevolution;
  
  // Set motor direction
  setMotorDirection(direction);
  
  // Reset encoder count
  encoderCount = 0;
  
  // Run the motor until the target count is reached
  while (abs(encoderCount) < targetCount) {
    setMotorSpeed(255);  // Full speed
  }
  
  // Stop the motor
  setMotorSpeed(0);
}

// Interrupt Service Routine (ISR) for the encoder
void encoderISR() {
  // Read the encoder pins
  int a = digitalRead(encoderPinA);
  int b = digitalRead(encoderPinB); 

  
  // Determine the direction of rotation and update the count
  if (a == b) {
    encoderCount++;
  } else {
    encoderCount--;
  }
}
