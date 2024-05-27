const byte ledPin = LED_BUILTIN;
const byte interruptPin = 2;
volatile byte state = LOW;
volatile unsigned long tid = 0;
volatile unsigned long teller = 0;
void setup()
{
	pinMode(ledPin, OUTPUT);
	pinMode(interruptPin, INPUT_PULLUP);
	Serial.begin(115200);
	attachInterrupt(digitalPinToInterrupt(interruptPin), blink, FALLING);
}

void loop()
{
	digitalWrite(ledPin, state);
	Serial.println(teller);
	delay(5);
}

void blink()
{
	unsigned long m_mid = millis();
	if(m_mid - tid > 200)
	{
		state = !state;
		teller++;
		tid = m_mid;
	}

}
