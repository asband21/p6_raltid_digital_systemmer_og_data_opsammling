#include "./krnl.h"

#define STK 150

const byte ledPin = LED_BUILTIN;

struct k_t *pTask;
unsigned char taskStak[STK];

struct k_t *pTask_2;
unsigned char taskStak_2[STK];



void t1()
{
	while(1)
	{ // your tas
		k_sleep (500); 
		digitalWrite (ledPin, HIGH);
		k_sleep (100); 
		digitalWrite (ledPin, LOW);;
	}
}

void t2()
{
  while(1)
  { // your tas
    k_sleep (300); 
    Serial.println("hore unge");
  }
}

void setup()
{
	int res;
	Serial.begin(115200);
	while (!Serial);
	pinMode (ledPin, OUTPUT);
	k_init (2, 0, 0);
	pTask = k_crt_task(t1, 10, taskStak, STK);
  pTask_2 = k_crt_task(t2, 2, taskStak_2, STK);
  
  res = k_start();
  
	Serial.println("kølmyfirsttask");
	Serial.print("ups an error occured:"); 
	Serial.println(res);
	while(1);
}
