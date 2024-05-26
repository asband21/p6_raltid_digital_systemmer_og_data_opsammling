#include <math.h>

// Define the pins for thermistor and known resistor
const int thermistorPin = A0;   // Analog pin for thermistor 
const int  buttionPin = 12; 
const float knownResistance = 10000.0;  // Resistance of the known resistor in ohms
const float resistanceAt25C = 10.0;  // Resistance of the thermistor at 25°C in ohms

// Define variables for storing temperature and resistance values
float temperature[] = {25.0, 50.0, 100.0}; // Example temperatures in Celsius
float resistance[3]; // Array to store resistance values for each temperature
int  i = 0; 

void setup() {
  Serial.begin(9600);  // Initialize serial communication 
  pinMode(buttionPin,INPUT);
}

void loop() {
  // Read the analog input from the thermistor pin
  int rawValue = analogRead(thermistorPin);
  
  // Convert raw value to voltage
  float voltage = rawValue * (5.0 / 1023.0); // Assuming 5V reference
  
  // Calculate resistance of the thermistor using voltage divider formula
  float thermistorResistance = (knownResistance * voltage) / (5.0 - voltage);

  // Print the voltage and resistance values
  Serial.print("Voltage (V): ");
  Serial.print(voltage);
  Serial.print("\t Resistance (ohms): ");
  Serial.println(thermistorResistance);

  // Store the resistance value for each temperature
  
  if (digitalRead(buttionPin) == true) { // Check if temperature is approximately 25 degrees Celsius
    resistance[i] = thermistorResistance; 
    i++; 
  }


  // Check if all resistance values are collected
  if (resistance[0] != 0 && resistance[1] != 0 && resistance[2] != 0) {
    // Perform linear regression to calculate Steinhart-Hart parameters
    float sum_T = 0.0;
    float sum_ln_R = 0.0;
    float sum_ln_R_pow_3 = 0.0;
    float sum_T_times_ln_R = 0.0;
    float sum_ln_R_times_ln_R_pow_3 = 0.0;

    for (int i = 0; i < 3; i++) {
      float ln_R = log(resistance[i] / resistanceAt25C); // Normalize resistance to 25°C
      float ln_R_pow_3 = pow(ln_R, 3);
      sum_T += temperature[i];
      sum_ln_R += ln_R;
      sum_ln_R_pow_3 += ln_R_pow_3;
      sum_T_times_ln_R += temperature[i] * ln_R;
      sum_ln_R_times_ln_R_pow_3 += ln_R * ln_R_pow_3;
    }

    float N = 3.0; // Number of data points
    float sum_ln_R_squared = sum_ln_R * sum_ln_R;
    float sum_T_times_sum_ln_R = sum_T * sum_ln_R;
    
    // Calculate the parameters
    float C = (N * sum_T_times_ln_R - sum_T * sum_ln_R) / (N * sum_ln_R_pow_3 - sum_ln_R_squared);
    float B = (sum_T - C * sum_ln_R_pow_3) / sum_ln_R;
    float A = (sum_T - B * sum_ln_R - C * sum_ln_R_pow_3) / N;

    // Print the parameters
    Serial.print("Steinhart-Hart Parameters: A = ");
    Serial.print(A);
    Serial.print(", B = ");
    Serial.print(B);
    Serial.print(", C = ");
    Serial.println(C);

    // Stop further measurements
    while (true) {
      delay(1000);
    }
  }

  // Delay for a moment before taking the next measurement
  delay(1000);
}