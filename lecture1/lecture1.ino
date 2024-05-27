// Defining pins
int b1 = 4;
int b2 = 5;
int b3 = 6;
int b4 = 7;

int b5 = 8;
int b6 = 9;
int b7 = 10;
int b8 = 11;

int inputSin = A0;

int storedSin = 0;
int a = 1;

void setup() {
	// put your setup code here, to run once:
	Serial.begin(115200);
	pinMode(b0, OUTPUT);
	pinMode(b1, OUTPUT);
	pinMode(b2, OUTPUT);
	pinMode(b3, OUTPUT);
	pinMode(b4, OUTPUT);
	pinMode(b5, OUTPUT);
	pinMode(b6, OUTPUT);
	pinMode(b7, OUTPUT);
	pinMode(b8, OUTPUT);

	pinMode(inputSin, INPUT);
}

void loop() {

	storedSin = analogRead(inputSin) / 4;
	//byte outputValue = map(storedSin, 0, 1023, 0, 255);
	byte outputValue = storedSin;
	a = 1;
	Serial.println(storedSin);

	digitalWrite(b1, a & outputValue );
	a = a * 2;
	digitalWrite(b2, a & outputValue );
	a = a * 2;
	digitalWrite(b3, a & outputValue);
	a = a * 2;
	digitalWrite(b4, a & outputValue);
	a = a * 2;
	digitalWrite(b5, a & outputValue);
	a = a * 2;
	digitalWrite(b6, a & outputValue);
	a = a * 2;
	digitalWrite(b7, a & outputValue);
	a = a * 2;
	digitalWrite(b8, a & outputValue);
	a = a * 2;

	delay(1);
}
