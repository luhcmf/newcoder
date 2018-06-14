#include "TimerOne.h"

#define go_up 0x01
#define go_down 0x02

bool motor1,motor2,m1_break,m2_break;
const int offset, motor1_amp = 0, motor2_amp = 1;
static int m1_count, m2_count;
byte m1_state, m2_state;

/*motor 1 output*/
const int 
 

void setup() {
  // put your setup code here, to run once:
  Timer1.initialize(50000);
  Timer1.attachInterrupt(auto_loop);
  m1_state = go_up;
  m2_state = go_up;
}

double get_current(int motor){
  int reading = analogRead(motor);
  reading += offset;
  double I = (reading*5000/1024-2500)/66;
  return I;
}
void auto_loop(){
  if(motor1 == true){
    if(get_current(motor1_amp) > 10){
      //motor1 stop
      m1_break = true;
    }
    if(m1_break){
      m1_count++;
      if(m1_count >= 100){
        m1_break = false;
        if(m1_state == go_up)
          m1_state = go_down;
        else if(m1_state == go_down)
          m1_state = go_up;          
      }
    }
    if(!m1_break && (m1_state==go_up)){
      //motor1 go up
    }
    if(!m1_break && (m1_state==go_down)){
      //motor1 go down
    }
  }
  if(motor2 == true){
    if(get_current(motor2_amp) > 10){
      //motor2 stop
      m2_break = true;
    }
    if(m2_break){
      m2_count++;
      if(m2_count >= 100){
        m2_break = false;
        if(m2_state == go_up)
          m2_state = go_down;
        else if(m2_state == go_down)
          m2_state = go_up;          
      }
    }
    if(!m2_break && (m2_state==go_up)){
      //motor2 go up
    }
    if(!m2_break && (m2_state==go_down)){
      //motor2 go down
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
