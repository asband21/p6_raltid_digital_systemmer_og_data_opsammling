#include "./krnl.h"

#define STK 150

const byte ledPin = LED_BUILTIN;

struct k_t *s1;


struct k_t *pTask;
unsigned char taskStak[STK];

struct k_t *pTask_2;
unsigned char taskStak_2[STK];

volatile long v = 0;
void t1()
{
  k_set_sem_timer(s1, 100);
	while(1)
	{
    k_wait(s1, 0);
		Serial.println(v);
	}
}

void t2()
{
  while(1)
  { // your tas
    k_sleep(2000);
    v++;
  }
}

void setup()
{
	int res;
	Serial.begin(115200);
	while (!Serial);
	pinMode (ledPin, OUTPUT);
	k_init (2, 1, 0);
	pTask = k_crt_task(t1, 2, taskStak, STK);
  pTask_2 = k_crt_task(t2, 10, taskStak_2, STK);

  s1 = k_crt_sem(0, 10);
  
  res = k_start();
  
	Serial.print("ups an error occured:"); 
	Serial.println(res);
	while(1);
}
