#include "./krnl.h" 

#define STK 150
unsigned char taskStak_1[STK], taskStak_2[STK], taskStak_1_safe[STK], taskStak_2_safe[STK]; 
struct k_t *pTask_1, *pTask_2, *pTask_1_safe, *pTask_2_safe, *mutSem; // pointer to task descriptor

void Task_1() {  for(;;){Serial.println("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");}}

void Task_2() {  for(;;){Serial.println("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");}}


void Task_1_safe(){  
  for(;;){ 
    k_wait(mutSem, 15); { 
        Serial.println("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"); 
    } k_signal(mutSem);
     
  }
  
}
void Task_2_safe(){  
  for(;;){ 
    k_wait(mutSem, 15); { 
        Serial.println("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"); 
    } k_signal(mutSem);
  
  }
  

}

void setup() {
  // put your setup code here, to run once: 
  Serial.begin(115200);  
   

  // change the if statment:  Ture == w.semaphor, false it is without
  if (false) {  
    k_init(2, 1, 0); 
    pTask_1_safe = k_crt_task(Task_1_safe, 1, taskStak_1_safe, STK); 
    pTask_2_safe = k_crt_task(Task_2_safe, 1, taskStak_2_safe, STK);
  }else{     
    k_init(2, 0, 0); 
    pTask_1 = k_crt_task(Task_1, 1, taskStak_1, STK); 
    pTask_2 = k_crt_task(Task_2, 1, taskStak_2, STK);
  }
  k_start();

}

void loop() {
  // put your main code here, to run repeatedly:
  
}
