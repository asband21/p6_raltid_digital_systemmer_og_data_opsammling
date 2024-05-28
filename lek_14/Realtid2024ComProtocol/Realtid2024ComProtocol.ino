int ledPin = 50;
bool silentMode = false; //Used to prevent a unit from sending packets

char incomingByte = 0; //holds each char
char command[4]; //holds each message
int commandRegister = 0; //holds the string command as an int


void readSerial() {
  // Check if data is available to read from Serial1
  if (Serial1.available() > 0) {
    // Read the incoming byte
    incomingByte = Serial1.read();
    if (incomingByte == 'W'){ // We use W as a startChar
        command[0] = 'W';
        for(int i = 1; i < 4; i++){
            incomingByte = Serial1.read();
            command[i] = incomingByte; 
            Serial.flush();
        }
      }
    }
    
    // Print the received byte to the Serial Monitor
  
    Serial.print("Received: ");
    for(int i = 0; i < 4; i++){
        Serial.print(command[i]);
 
          }
    Serial.println();
  
 }


void writeSerial(int messageID) {

  //W is start bit
  char package0[] = "W50L"; //set led50 LOW
  char package1[] = "W50H"; //set led50 HIGH
  char package2[] = "WioL"; //stop sending io
  char package3[] = "WioH"; //start sending io

  // Send each byte of the package
  if (messageID == 0) {
  for (int i = 0; i < 4; i++) {
    Serial1.write(package0[i]);
    delay(10);  // Small delay to ensure the receiver gets each byte properly
  }
  }
   if (messageID == 1) {
  for (int i = 0; i < 4; i++) {
    Serial1.write(package1[i]);
    delay(10);  // Small delay to ensure the receiver gets each byte properly
  }
  }
   if (messageID == 2) {
  for (int i = 0; i < 4; i++) {
    Serial1.write(package2[i]);
    delay(10);  // Small delay to ensure the receiver gets each byte properly
  }
  }
   if (messageID == 3) {
  for (int i = 0; i < 4; i++) {
    Serial1.write(package3[i]);
    delay(10);  // Small delay to ensure the receiver gets each byte properly
  }
  }
}


int commandExecute() {
  //This section is a bit lazy, sorry if you hate "if" statements :)
  char char0 = command[0];
  char char1 = command[1];
  char char2 = command[2];
  char char3 = command[3];

  if (char0 == 'W') {
    if (char1 == '5'){
      if (char3 == 'L'){
        // LED LOW
        digitalWrite(ledPin, LOW);
      }
      if (char3 == 'H'){
        // LED HIGH
        digitalWrite(ledPin, HIGH);
      }
    }
    if (char1 == 'i'){
      if (char3 == 'L'){
        // IO LOW
        silentMode = true;
      }
      if (char3 == 'H'){
        // IO HIGH
        silentMode = false;
      }
    }
      
  }

}


void setup() {
Serial.begin(115200);
Serial1.begin(115200);
}

void loop() {
    //Slave action
    readSerial();
    commandExecute();

    //Master action
    if (!silentMode){
       writeSerial(1); //ID for LED HIGH
       writeSerial(2); //ID for IO silent
       delay(2000);
       writeSerial(0); //ID for LED LOW
       writeSerial(3); //ID for IO speak

       
    }
}
