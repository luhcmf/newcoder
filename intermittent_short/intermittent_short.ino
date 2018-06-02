#include "TimerOne.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#define phase1    0x01
#define phase2    0x02
#define phase3    0x03
#define pwr_off   0x04
#define stop_run  0x05
#define test_cycle  60
//the folowing time unit is in second
#define phase1_cnt  15   //connect to power, do nothing
#define phase2_cnt  300   //short the circuit
#define phase3_cnt  165   //open the circuit, wait to switch off the power
#define pwr_off_cnt 10   //a break

int state, wait_count,time_counting, cycles;
bool timer_state = false,timer_isr = false;
const int short_pin = 3,Vbat = 4, GND = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  lcd.begin(16,2);
  Timer1.initialize(1000);
  pinMode(short_pin,OUTPUT);
  pinMode(Vbat,OUTPUT);
  pinMode(GND,OUTPUT);
  state = phase1;  
  lcd.setCursor(0,0);
  lcd.print("Ready");
  lcd.setCursor(0,1);
  lcd.print("starting");
  delay(5000);
  lcd.clear();
  lcd.print("cycles:");
  lcd.setCursor(8,0);
  lcd.print(1);
}

void time_waiting(int count){
  timer_state = true;
  wait_count = count;
  Timer1.attachInterrupt(counting,1000000);
  timer_isr = true;
}

void counting(){
  time_counting++;
  if(time_counting >= wait_count){
    Timer1.detachInterrupt();
    timer_state = false;
    time_counting = 0;
//    Serial.println("timer end");
//    Serial.println(time_counting);
  }
}
void loop() {
  lcd.setCursor(12,0);
  lcd.print((wait_count-time_counting));
    if(wait_count-time_counting < 10){
    lcd.setCursor(13,0);
    lcd.print("  ");
  }
  else if(wait_count-time_counting < 100){
    lcd.setCursor(14,0);
    lcd.print(" ");
  }
    if(state == phase1){
      // nothing for 15s
      if(!timer_state && !timer_isr){
        time_waiting(phase1_cnt);
        //connect to power
        digitalWrite(Vbat,HIGH);
//        Serial.println("connect to power");
        lcd.setCursor(0,1);
        lcd.print("power on     ");        
      }
      else if(!timer_state && timer_isr){
        state = phase2;
        timer_isr = false;
//        Serial.println("phase1 end");      
      }
    }
    else if(state == phase2){
      // short circuit
      if(!timer_state && !timer_isr){
        time_waiting(phase2_cnt);
        //short the circuit
        digitalWrite(short_pin,HIGH);
//        Serial.println("short the circuit");
        lcd.setCursor(0,1);
        lcd.print("short circuit");
      }
      else if(!timer_state && timer_isr){
        state = phase3;
        timer_isr = false;
//        Serial.println("phase2 end");
        digitalWrite(short_pin,LOW);
//        Serial.println("open the circuit");
      }
    }
    else if(state == phase3){
      //nothing for 2m45s
      if(!timer_state && !timer_isr){
        time_waiting(phase3_cnt);
//        Serial.println("waiting to cut power");
        lcd.setCursor(0,1);
        lcd.print("open circuit "); 
      }
      else if(!timer_state && timer_isr){
        state = pwr_off;
        timer_isr = false;
//        Serial.println("phase3 end");
      }
    }
    else if(state == pwr_off){      
      //swutch off the power supply
      if(!timer_state && !timer_isr){
        time_waiting(pwr_off_cnt);
        //switch off the power
        digitalWrite(Vbat,LOW);
//        Serial.println("switch off the power");
        lcd.setCursor(0,1);
        lcd.print("power off    ");
      }
      else if(!timer_state && timer_isr){
        if(cycles == test_cycle)
          state = stop_run;
        else{
          cycles++;
          state = phase1;
          timer_isr = false;
//        Serial.print("cycle number:  ");
//        Serial.println(cycles);
//        lcd.clear();
          lcd.setCursor(8,0);
          lcd.print((cycles+1));
//        Serial.println("power 0ff end");
        }        
      }
    }
    else if(state == stop_run){
      //open all relay
//      Serial.println("stop running test");
      lcd.setCursor(0,1);
      lcd.print("test finished");
    }
}
