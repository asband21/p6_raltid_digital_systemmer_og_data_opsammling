// Defining pins
int inputSin = A0;
int storedSin = 0;
int a = 1; 
//unsigned char m_PORTD; 
//unsigned char m_PORTB; 
void setup()
{
	Serial.begin(115200);
	for(int i = 4; i < 12; i++)
		pinMode(i, OUTPUT);
	pinMode(inputSin, INPUT);
}

void loop()
{
	int outputValue = analogRead(inputSin) / 4;
	m_PORTD = PORTD | ((B00001111 & outputValue) << 4 );
	m_PORTB = PORTB | ((B11110000 & outputValue) >> 4 ); 
  //PORTD = m_PORTD;
 // PORTB = m_PORTB;
	delay(1);
}
