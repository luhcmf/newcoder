#include "timers.h"

unsigned long oldtime;
unsigned long oldtime3;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  timer1.init(1000000);
  timer3.init(1000000);  

  timer1.startTimer(test);
  timer3.startTimer(test3);
  
  oldtime = millis();
  oldtime3 = millis();
}

void test(){
  unsigned long period = millis() - oldtime;
  Serial.print(period);
  Serial.print('\t');
  oldtime = millis();
}

void test3(){
  unsigned long period = millis() - oldtime3;
  Serial.println(period);
//  Serial.print('\t');
  oldtime3 = millis();
}



void loop() {
  // put your main code here, to run repeatedly:
}
