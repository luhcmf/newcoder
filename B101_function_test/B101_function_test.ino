#include "timers.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3,POSITIVE);

const int relayL1 = 51, relayL2 = 50,
relayU1 = 52, relayU2 = 53;

const byte colPins[4] = {39, 41, 43, 45};     //keypad column pins
const byte rowPins[4] = {31, 33, 35, 37};     //keypad row pins
const char keymap[4][4] = {
    {'1','2','3','A'}, 
    {'4','5','6','B'}, 
    {'7','8','9','C'},
    {'*','0','#','D'}
};
char A;
byte i, j;     
byte scanVal;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  lcd.begin(20,4);
  for(int i=50; i<=53;i++){
    pinMode(i,OUTPUT);
  }
  for (i = 0; i <= 3; i++) {
    pinMode(rowPins[i], INPUT);
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
    digitalWrite(rowPins[i], HIGH);
  }
  lcd.setCursor(0,0);
  lcd.print("start test");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  timer1.init(100000);
  timer1.startTimer(sw);
}

void sw(){
  A = NULL;
  for (i = 0; i <= 3; i++) {
    for (j = 0; j <= 3; j++) {
      digitalWrite(colPins[j], LOW);
      scanVal = digitalRead(rowPins[i]);
 
      if (scanVal == LOW) {    
        A = keymap[i][j];
        delay(10);  
        digitalWrite(colPins[j], HIGH);
        break;       
      }
      digitalWrite(colPins[j], HIGH);
    }
  }
//  if(A)
//    Serial.println(A);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(A){
    switch(A){
      case '1':
        digitalWrite(relayL1,HIGH);
        digitalWrite(relayL2,LOW);
        A = NULL;
        lcd.setCursor(0,0);
        lcd.print("1");
        break;
      case '2':
        digitalWrite(relayL1,LOW);
        digitalWrite(relayL2,HIGH);
        A = NULL;
        lcd.setCursor(0,0);
        lcd.print("2");
        break;
      case '3':
        digitalWrite(relayL1,LOW);
        digitalWrite(relayL2,LOW);
        A = NULL;
        lcd.setCursor(0,0);
        lcd.print("3");
        break;
      case '4':
        digitalWrite(relayU1,HIGH);
        digitalWrite(relayU2,LOW);
        A = NULL;
        lcd.setCursor(0,0);
        lcd.print("4");
        break;
      case '5':
        digitalWrite(relayU1,LOW);
        digitalWrite(relayU2,HIGH);
        A = NULL;
        lcd.setCursor(0,0);
        lcd.print("5");
        break;
      case '6':
        digitalWrite(relayU1,LOW);
        digitalWrite(relayU2,LOW);
        A = NULL;
        lcd.setCursor(0,0);
        lcd.print("6");
        break;
      default:
        digitalWrite(relayL1,LOW);
        digitalWrite(relayL2,LOW);
        digitalWrite(relayU1,LOW);
        digitalWrite(relayU2,LOW);
        A = NULL;
        break;
    }
  }

  double I1 = (analogRead(A7)/1024.0*5000-2500)/66;
  lcd.setCursor(0,1);
  lcd.print(abs(I1));
  double I2 = (analogRead(A8)/1024.0*5000-2500)/66;
  lcd.setCursor(0,2);
  lcd.print(abs(I2));

  if(abs(I1) > 10){
    digitalWrite(relayL1,LOW);
    digitalWrite(relayL2,LOW);
  }
  if(abs(I2) > 10){
    digitalWrite(relayU1,LOW);
    digitalWrite(relayU2,LOW);
  }
  delay(20);
}
