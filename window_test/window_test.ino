#include "TimerOne.h"
#include "Filter.h"

#define go_up 0x01
#define go_down 0x02

bool motor1,motor2,m1_break,m2_break;
const int offset, motor1_amp = 0, motor2_amp = 1;
static int m1_count, m2_count;
byte m1_state, m2_state;
/*motor control pin*/
const int m1_p = 2, m1_n = 3, m2_p = 4, m2_n = 5;
/*switch*/
const int s1=22, s2=24, s3=26, s4=28,
          s5=30, s6=32, s7=34, s8=36;
static bool sw1_auto, sw2_auto;

ExponentialFilter <double> filter1(50,0);
ExponentialFilter <double> filter2(50,0);
ExponentialFilter <double> filter3(50,0);
ExponentialFilter <double> filter4(50,0);

void setup() {
  // put your setup code here, to run once:
  pinMode(m1_p,OUTPUT);
  pinMode(m1_n,OUTPUT);
  pinMode(m2_p,OUTPUT);
  pinMode(m2_n,OUTPUT);
  pinMode(s1,INPUT);
  pinMode(s2,INPUT);
  pinMode(s3,INPUT);
  pinMode(s4,INPUT);
  pinMode(s5,INPUT);
  pinMode(s6,INPUT);
  pinMode(s7,INPUT);
  pinMode(s8,INPUT);
  Timer1.initialize(50000);
  Timer1.attachInterrupt(auto_loop);
  m1_state = go_up;
  m2_state = go_up;
}
double get_current(int motor){
  int reading = analogRead(motor);
  reading += offset;
  double I = (reading*5000/1024-2500)/66;
  if(motor == motor1_amp){
    filter1.Filter(I);
    return filter1.Current();
  }
  else if(motor == motor2_amp){
    filter2.Filter(I);
    return filter2.Current();
  }
}
void m1_stop(){
  digitalWrite(m1_p,LOW);
  digitalWrite(m1_n,LOW);
}
void m2_stop(){
  digitalWrite(m2_p,LOW);
  digitalWrite(m2_n,LOW);
}
void m1_run(){
  if(m1_state==go_up){
    digitalWrite(m1_p,HIGH);
    digitalWrite(m1_n,LOW);       
  }
  else if(m1_state==go_down){
    digitalWrite(m1_p,LOW);
    digitalWrite(m1_n,HIGH);
  }
}
void m2_run(){
  if(m2_state==go_up){
    digitalWrite(m2_p,HIGH);
    digitalWrite(m2_n,LOW);       
  }
  else if(m2_state==go_down){
    digitalWrite(m2_p,LOW);
    digitalWrite(m2_n,HIGH);
  }
}
void auto_loop(){
  if(motor1 == true){
    if(get_current(motor1_amp) > 10){
      //motor1 stop
      m1_stop();
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
    else if(!m1_break){
      m1_run();
    }
  }
  if(motor2 == true){
    if(get_current(motor2_amp) > 10){
      //motor2 stop
      m2_stop();
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
    else if(!m2_break){
      m2_run();
    }
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(s1) == HIGH){
    motor1 = true;
    sw1_auto = true;
  }
  if(digitalRead(s5) == HIGH){
    motor2 = true;
    sw1_auto = true;
  }
  if(digitalRead(s4) == HIGH){
    m1_stop();
    sw1_auto = false;
  }
  if(digitalRead(s8) == HIGH){
    m2_stop();
    sw2_auto = false;
  }
  if(!sw1_auto){
    if(digitalRead(s2) == HIGH){
      m1_state = go_up;
      m1_run();
    }
    else if(digitalRead(s3) == HIGH){
      m1_state = go_down;
      m1_run();
    }
    else
      m1_stop();
  }
  if(!sw2_auto){
    if(digitalRead(s6) == HIGH){
      m2_state = go_up;
      m2_run();
    }
    else if(digitalRead(s7) == HIGH){
      m2_state = go_down;
      m2_run();
    }
    else
      m2_stop();
  }
}
