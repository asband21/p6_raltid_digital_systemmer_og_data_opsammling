// Defining pins

int inputSin = A0;
int storedSin = 0; 

unsigned char m_1; 
unsigned char m_2; 

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(A0, INPUT);  
pinMode((4,5,6,7,8,9,10,11), OUTPUT);

}

void loop() {
  storedSin = analogRead(inputSin) / 4;
  m_1 = PORTD & B00001111;  
  m_1 = m_1 | (storedSin<<4);
  PORTD = m_1;

  m_2= PORTB & B11110000; 
  m_2 = m_2 | (storedSin>>4);
  PORTB = m_2; 

delay(1);
}
