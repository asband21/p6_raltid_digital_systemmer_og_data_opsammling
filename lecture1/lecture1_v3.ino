// Defining pins
int inputSin = A0;
int storedSin = 0;
int a = 1;
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
	delay(1);
}
