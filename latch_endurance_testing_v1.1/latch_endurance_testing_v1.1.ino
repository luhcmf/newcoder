/*  version 1.2 */

#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3,POSITIVE);

//===============setup gpio pin========================//
int relay1 = 7;
int relay2 = 8;
int relay3 = 9;
int SW1 = 6;
int SW2 = 5;
int SW3 = 4;
int SW4 = 3;
int SW5 = 10;

//=====================================================//
int cycle;
int lock_1;
int lock_2;
int lock_3;
int lock_4;
int lock_5;
int state;
int Time;
int real_time;
int system_number;
int Boolean;
int motor_factor;
int motor_time;
int Error;


void setup() {
  Serial.begin(9600);

  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(SW1,INPUT_PULLUP);
  pinMode(SW2,INPUT_PULLUP);
  pinMode(SW3,INPUT_PULLUP);
  pinMode(SW4,INPUT_PULLUP);
  pinMode(SW5,INPUT_PULLUP);

  digitalWrite(relay1,LOW);
  digitalWrite(relay2,LOW);
  digitalWrite(relay3,LOW);

  state = 1;
//===============setup timer1======================//
cli();
 TCCR1A = 0;
 TCCR1B = 0;
 TCNT1 = 0;
 OCR1A = 625;
 TCCR1B |= (1 << WGM12);
 TCCR1B |= (1 << CS12);
 TIMSK1 |= (1 << OCIE1A);
sei();
//==================================================//
  lcd.begin(20,4);   
 
  lcd.setCursor(0,0); 
  lcd.print("Latch testing");
  delay(1000);
  lcd.clear();
//==================================================//
//read EEPROM
int a = EEPROM.read(0);
int b = EEPROM.read(1);

cycle = a*256+b;

//=================================================//
//setup EEPROM
//int a = 0;
//int b = 0;
//EEPROM.write(0,a);
//EEPROM.write(1,b);
//==================================================//
}

ISR(TIMER1_COMPA_vect){
 if (state == 1){                  //stop mode
   digitalWrite(relay1,LOW);
   digitalWrite(relay2,LOW);
   digitalWrite(relay3,LOW);
   system_number = 0;
   Time = 0;
   motor_time = 0;
   if ((lock_1 == 1)&&(lock_2 == 1)){
    Boolean = 4;    //phase
   }else if ((lock_1 == 0)&&(lock_2 == 0)){
    Boolean = 1;
   }else {
    Boolean = 0;
    Error = 1;  //initial lock state error
   }
   
 }

 if (state == 2){                 //Auto mode
  system_number++;
  if (Boolean == 1){              //close
    Time++;
    digitalWrite(relay1,HIGH);
    if (Time >= 100){
      digitalWrite(relay1,LOW);
      Time = 0;
      Boolean = 2;
    }
  }
  if (Boolean == 2){
    Time++;
    if (Time >= 300){
      Time = 0;
      Boolean = 3;
    }
  }
  if (Boolean == 3){
    if ((lock_1 == 1)&&(lock_2 == 1)){
      Boolean = 4;
    }else{
      state = 1;
      Error = 2;    //not locked
    }
  }
  if (Boolean == 4){                 //open
    Time++;
    digitalWrite(relay2,HIGH);
    if (Time >= 50){
      Time = 0;
      digitalWrite(relay2,LOW);
      Boolean = 5;
    }
  }
  if (Boolean == 5){
    Time++;
    if (Time >= 550){
      Time = 0;
      Boolean = 6;
    }
  }
  if (Boolean == 6){
      Boolean = 1;
      system_number = 0;
      cycle++;
      if ((cycle % 20) == 0){
        int a = cycle / 256;
        int b = cycle % 256;
        EEPROM.write(0,a);
        EEPROM.write(1,b);
      }
  }

 if (motor_factor == 0){
  if (lock_3 == 0){
    motor_time++;
    if (motor_time >= 5){
    motor_time = 0;
    motor_factor = 1;
    }
  }
 }
  if (motor_factor == 1){
    motor_time++;
    digitalWrite(relay3,HIGH);
    if ((lock_1 == 0)&&(lock_2 == 0)){
      digitalWrite(relay3,LOW);
      motor_time = 0;
      motor_factor = 0;
    }
    if (motor_time >= 400){
      digitalWrite(relay3,LOW);
      motor_time = 0;
      Error = 3;    //unlock fail
      state = 1;
      motor_factor = 0;
    }
  }
 }
}

void loop() {
  real_time = system_number/100;
  
  lock_1 = digitalRead(SW1);
  lock_2 = digitalRead(SW2);
  lock_3 = digitalRead(SW3);    //unlock switch signal
  lock_4 = digitalRead(SW4);    //button
  lock_5 = digitalRead(SW5);    //button

  if ((lock_4 == 0)&&(lock_5 == 1)){
    state = 1;
  }
  if ((lock_4 == 1)&&(lock_5 == 0)){
    state = 2;
    Error = 0;
  }  

 //===========condition==================//
 if (cycle >= 50000){
  state = 1;
 }
 //============LCD print==================//
  if (Error == 0){
   if (state == 1){
   lcd.clear();
   lcd.setCursor(0,0); 
   lcd.print("cycle:");
   lcd.print(cycle);
   lcd.setCursor(0,1);
   lcd.print("Time:");
   lcd.print(real_time);
   lcd.setCursor(0,2);
   lcd.print("Stop");
   }
   if (state == 2){
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("cycle:");
    lcd.print(cycle);
    lcd.setCursor(0,1);
    lcd.print("Time:");
    lcd.print(real_time);
    lcd.setCursor(0,2);
    lcd.print("Auto");
   }
  }
  if (Error == 1){
   lcd.clear();
   lcd.setCursor(0,0); 
   lcd.print("cycle:");
   lcd.print(cycle);
   lcd.setCursor(0,1);
   lcd.print("Time:");
   lcd.print(real_time);
   lcd.setCursor(0,2);
   lcd.print("ERROR");
   lcd.setCursor(0,3);
   lcd.print("init lock state");
  }
  if (Error == 2){
   lcd.clear();
   lcd.setCursor(0,0); 
   lcd.print("cycle:");
   lcd.print(cycle);
   lcd.setCursor(0,1);
   lcd.print("Time:");
   lcd.print(real_time);
   lcd.setCursor(0,2);
   lcd.print("ERROR");
   lcd.setCursor(0,3);
   lcd.print("lock fail");
  }
  if (Error == 3){
   lcd.clear();
   lcd.setCursor(0,0); 
   lcd.print("cycle:");
   lcd.print(cycle);
   lcd.setCursor(0,1);
   lcd.print("Time:");
   lcd.print(real_time);
   lcd.setCursor(0,2);
   lcd.print("ERROR");
   lcd.setCursor(0,3);
   lcd.print("unlock fail");
  }    
delay(5);

//===========================================//
// Serial.print(lock_1);
// Serial.print("\t");
// Serial.print(lock_2);
// Serial.print("\t");
// Serial.print(lock_3);
// Serial.print("\t");
// Serial.print(lock_4);
// Serial.print("\t");
// Serial.print(lock_5);
// Serial.print("\t");
// Serial.print(state);
// Serial.print("\t");
// Serial.print(Boolean);
// Serial.print("\t");
// Serial.print(Time);
// Serial.print("\t");
// Serial.println(Error);   

}
