#include <Arduino.h>

const int receiverID = 2;
const int senderID = 1;
char incomingByte = 0;
char command[4];

void setup() {
  Serial.begin(750);
  pinMode(13, OUTPUT); // Set pin 13 as output
}

void loop() {
readSerial();
commandExecute();
delay(100);

}


void readSerial() {
  // Check if data is available to read from Serial1
  if (Serial.available() > 0) {
    // Read the incoming byte
    incomingByte = Serial.read();
    if (incomingByte == 'W'){ // We use W as a startChar
        command[0] = 'W';
        for(int i = 1; i < 4; i++){
            incomingByte = Serial.read();
            command[i] = incomingByte; 
            //Serial.flush();
            
        }
      }
    Serial.print("R");
    for(int i = 1; i < 4; i++){
      Serial.print(command[i]);
 
    }
    Serial.println();  
    while (Serial.available() > 0){
      Serial.read();
    } 
   /* Serial.print("R");
    for(int i = 1; i < 4; i++){
      Serial.print(command[i]);
 
    }
    Serial.println();  
    while (Serial.available() > 0){
      Serial.read();*/
  }
  
 }
   
  int commandExecute() {
  //This section is a bit lazy, sorry if you hate "if" statements :)
  char char0 = command[0];
  char char1 = command[1];
  char char2 = command[2];
  char char3 = command[3];

  if (char0 == 'W') {
    if (char1 == '1'){
      if (char3 == '1'){
        // LED LOW
        digitalWrite(13, LOW);
      }
      if (char3 == '2'){
        // LED HIGH
        digitalWrite(13, HIGH);
      }
    }
      
  }

}