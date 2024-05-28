#include "./krnl.h"

#define BUGPRINT(x) k_wait(mutexSem, 0), Serial.println(x), k_signal(mutexSem)
#define  STK 150
#define NRELM 10 
unsigned char taskStak_1[STK], taskStak_2[STK]; 
 
struct k_t *pTask1, *pTask2, *mutexSem; 

struct k_msg_t *msgQ1;  

int q1[NRELM]; 




void producer(){  
  int i = 0; 

 while(true){  
    i++;
    k_send(msgQ1,&i); 
    k_eat_msec(20);
  }
}

void consumer(){   
  int ii; 
  int lostMsgSinceLastCall; 
  int errCode;
 while(true){
    errCode = k_receive(msgQ1,&ii,0, &lostMsgSinceLastCall); 

    k_wait(mutexSem, 0); { 
      Serial.println(ii);
    }
    k_signal(mutexSem);
  }
  

}


void setup() {
  // put your setup code here, to run once: 
  Serial.begin(115200); 
  k_init(2, 1, 1);  
  mutexSem = k_crt_sem(1, 10); 
  msgQ1 = k_crt_send_Q(NRELM, sizeof(int), q1); 
  pTask1 =  k_crt_task(producer, 15, taskStak_1, STK);
  pTask2 =  k_crt_task(consumer, 15, taskStak_2, STK); 
  k_start();

}

void loop() {
  // put your main code here, to run repeatedly:

}
