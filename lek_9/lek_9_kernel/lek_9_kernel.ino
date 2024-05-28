#include "./krnl.h"


#define STK 150
unsigned char taskStak_1[STK], taskStak_2[STK]; 
struct k_t *pTask_1, *pTask_2; // pointer to task descriptor

//int l = 0;
void Task_1(){ 
 while(true){ 
    //l++;
    Serial.println("Task_1");
    //Serial.println(l);
    k_sleep(10); 
    //l--; 
  }
}

void Task_2(){ 
 while(true){
    Serial.println("Task____2");
    k_sleep(50); 
  }
  

}
void(* resetFunc) (void) = 0;


void setup() { 
  int res;
  Serial.begin(9600);  
  k_init(2, 0, 0);  
  pTask_1 = k_crt_task(Task_1, 1, taskStak_1, STK); 
  pTask_2 = k_crt_task(Task_2, 2, taskStak_2, STK);

  res = k_start(); // 1 milli sec tick

 // (*resetFunc)();
 // while (1) ;

}

void loop() {
  // put your main code here, to run repeatedly:

}
