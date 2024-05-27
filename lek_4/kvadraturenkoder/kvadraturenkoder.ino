int p1 = 9;
int p2 = 2;

//int re_pos = 10000;
int re_pos = 12;

//char index = 0;
byte index = 0;
int posison = 0;
int record[16] = {0, 1, -1 ,re_pos, -1, 0, re_pos, 1, 1, re_pos, 0, -1, re_pos, +1, -1, 0};

void setup()
{
	Serial.begin(115200);
	pinMode(p1, INPUT);
	pinMode(p2, INPUT);
	Serial.println("hej");
}

void loop()
{
	index = index << 1;
	index += digitalRead(p1);  
	index = index << 1;
	index += digitalRead(p2);
	index = index & B00001111; 
	posison += record[index];
  /*if(index != 0)
    Serial.println(index);
	*/
	if(record[index]*record[index])
		Serial.println(posison);
}
