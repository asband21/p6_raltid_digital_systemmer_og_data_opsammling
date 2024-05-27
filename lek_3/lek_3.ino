
int analogPin = 12;   // potentiometer connected to analog pin 3value
void setup()
{
   pinMode(analogPin, OUTPUT);  // sets the pin as output
}

void loop()
{
  analogWrite(analogPin, (int)((0.02)*255)); // analogWrite values from 0 to 255
} 
