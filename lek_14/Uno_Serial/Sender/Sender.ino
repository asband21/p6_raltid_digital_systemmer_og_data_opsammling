#include <Arduino.h>

const int receiverID = 2;
const int senderID = 1;
bool ledState = false; // Variable to keep track of the LED state
char ResponseByte;
void setup() {
  Serial.begin(115200);
}

void loop() {
  if (ledState) {
    sendCommand("W131"); // Turn on LED on pin 13
  } else {
    sendCommand("W132"); // Turn off LED on pin 13
  }
  
  ledState = !ledState; // Toggle LED state
  delay(600); // Wait for 1 second before sending the next command
  while (Serial.available()>0){
    ResponseByte = Serial.read();
    Serial.print(ResponseByte);
  }

  Serial.flush();
}

void sendCommand(const char* command) {
  //Serial.print('<'); // SOT
  //Serial.print(receiverID, HEX);
  //Serial.print(senderID, HEX);
  Serial.print(command);
  //Serial.print('>'); // EOT
  Serial.println();
}