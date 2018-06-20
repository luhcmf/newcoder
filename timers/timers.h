#ifndef	timers_h_
#define	timers_h_

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif
#include <avr/interrupt.h>

#define	resolution	65536

class timerOne
{	
	unsigned long comvalue;
	
	public:
		timerOne(){
		}
		static void (*funcCallback)();
		setTimer(unsigned long microseconds){			
			TCNT1 = 0;
			comvalue = microseconds*16;
			if(comvalue < resolution){
				comvalue = comvalue - 1;
				TCCR1B |= _BV(CS10) | _BV(WGM12);
			}
			else if(comvalue < resolution*8){
				comvalue = comvalue/8 - 1;
				TCCR1B |= _BV(CS11) | _BV(WGM12);
			}
			else if(comvalue < resolution*64){
				comvalue = comvalue/64 - 1;
				TCCR1B |= _BV(CS10) | _BV(CS11) | _BV(WGM12);
			}
			else if(comvalue < resolution*256){
				comvalue = comvalue/256 - 1;
				TCCR1B |= _BV(CS12) | _BV(WGM12);
			}
			else if(comvalue < resolution*1024){
				comvalue = comvalue/1024 -1;
				TCCR1B |= _BV(CS10) | _BV(CS12) | _BV(WGM12);
			}
			else{
				comvalue = resolution - 1;
				TCCR1B |= _BV(CS10) | _BV(CS12) | _BV(WGM12);
			}
			OCR1A = comvalue;	
		}
		init(unsigned long microseconds){
			noInterrupts();
			TCCR1A = 0;
			TCCR1B = 0;
			TCCR1B |=  _BV(WGM12);
			setTimer(microseconds);
			interrupts();
		}
		startTimer(void (*func)()){
			funcCallback = func;
			TIMSK1 |= _BV(OCIE1A);
		}
		startTimer(void (*func)(),unsigned long microseconds){			
			TCCR1B = 0;
			setTimer(microseconds);
			startTimer(func);
		}
		stopTimer(){
			TIMSK1 = 0;
		}		
};
extern timerOne timer1;

class timerThree
{	
	unsigned long comvalue;
	
	public:
		timerThree(){
		}
		static void (*funcCallback)();
		setTimer(unsigned long microseconds){			
			TCNT3 = 0;
			comvalue = microseconds*16;
			if(comvalue < resolution){
				comvalue = comvalue - 1;
				TCCR3B |= _BV(CS30) | _BV(WGM32);
			}
			else if(comvalue < resolution*8){
				comvalue = comvalue/8 - 1;
				TCCR3B |= _BV(CS31) | _BV(WGM32);
			}
			else if(comvalue < resolution*64){
				comvalue = comvalue/64 - 1;
				TCCR3B |= _BV(CS30) | _BV(CS31) | _BV(WGM32);
			}
			else if(comvalue < resolution*256){
				comvalue = comvalue/256 - 1;
				TCCR3B |= _BV(CS32) | _BV(WGM32);
			}
			else if(comvalue < resolution*1024){
				comvalue = comvalue/1024 -1;
				TCCR3B |= _BV(CS30) | _BV(CS32) | _BV(WGM32);
			}
			else{
				comvalue = resolution - 1;
				TCCR3B |= _BV(CS30) | _BV(CS32) | _BV(WGM32);
			}
			OCR3A = comvalue;		
		}
		init(unsigned long microseconds){
			noInterrupts();
			TCCR3A = 0;
			TCCR3B = 0;
			TCCR3B |=  _BV(WGM32);
			setTimer(microseconds);
			interrupts();
		}
		startTimer(void (*func)()){
			funcCallback = func;
			TIMSK3 |= _BV(OCIE3A);
		}
		startTimer(void (*func)(),unsigned long microseconds){			
			TCCR3B = 0;
			setTimer(microseconds);
			startTimer(func);
		}
		stopTimer(){
			TIMSK3 = 0;
		}		
};
extern timerThree timer3;

class timerFour
{	
	unsigned long comvalue;
	
	public:
		timerFour(){
		}
		static void (*funcCallback)();
		setTimer(unsigned long microseconds){			
			TCNT4 = 0;
			comvalue = microseconds*16;
			if(comvalue < resolution){
				comvalue = comvalue - 1;
				TCCR4B |= _BV(CS40) | _BV(WGM42);
			}
			else if(comvalue < resolution*8){
				comvalue = comvalue/8 - 1;
				TCCR4B |= _BV(CS41) | _BV(WGM42);
			}
			else if(comvalue < resolution*64){
				comvalue = comvalue/64 - 1;
				TCCR4B |= _BV(CS40) | _BV(CS41) | _BV(WGM42);
			}
			else if(comvalue < resolution*256){
				comvalue = comvalue/256 - 1;
				TCCR4B |= _BV(CS42) | _BV(WGM42);
			}
			else if(comvalue < resolution*1024){
				comvalue = comvalue/1024 -1;
				TCCR4B |= _BV(CS40) | _BV(CS42) | _BV(WGM42);
			}
			else{
				comvalue = resolution - 1;
				TCCR4B |= _BV(CS40) | _BV(CS42) | _BV(WGM42);
			}
			OCR4A = comvalue;			
		}
		init(unsigned long microseconds){
			noInterrupts();
			TCCR4A = 0;
			TCCR4B = 0;
			TCCR4B |=  _BV(WGM42);
			setTimer(microseconds);
			interrupts();
		}
		startTimer(void (*func)()){
			funcCallback = func;
			TIMSK4 |= _BV(OCIE4A);
		}
		startTimer(void (*func)(),unsigned long microseconds){			
			TCCR4B = 0;
			setTimer(microseconds);
			startTimer(func);
		}
		stopTimer(){
			TIMSK4 = 0;
		}		
};
extern timerFour timer4;

class timerFive
{	
	unsigned long comvalue;
	
	public:
		timerFive(){
		}
		static void (*funcCallback)();
		setTimer(unsigned long microseconds){			
			TCNT5 = 0;
			comvalue = microseconds*16;
			if(comvalue < resolution){
				comvalue = comvalue - 1;
				TCCR5B |= _BV(CS50) | _BV(WGM52);
			}
			else if(comvalue < resolution*8){
				comvalue = comvalue/8 - 1;
				TCCR5B |= _BV(CS51) | _BV(WGM52);
			}
			else if(comvalue < resolution*64){
				comvalue = comvalue/64 - 1;
				TCCR5B |= _BV(CS50) | _BV(CS51) | _BV(WGM52);
			}
			else if(comvalue < resolution*256){
				comvalue = comvalue/256 - 1;
				TCCR5B |= _BV(CS52) | _BV(WGM52);
			}
			else if(comvalue < resolution*1024){
				comvalue = comvalue/1024 -1;
				TCCR5B |= _BV(CS50) | _BV(CS52) | _BV(WGM52);
			}
			else{
				comvalue = resolution - 1;
				TCCR5B |= _BV(CS50) | _BV(CS52) | _BV(WGM52);
			}
			OCR5A = comvalue;		
		}
		init(unsigned long microseconds){
			noInterrupts();
			TCCR5A = 0;
			TCCR5B = 0;
			TCCR5B |=  _BV(WGM52);
			setTimer(microseconds);
			interrupts();
		}
		startTimer(void (*func)()){
			funcCallback = func;
			TIMSK5 |= _BV(OCIE5A);
		}
		startTimer(void (*func)(),unsigned long microseconds){			
			TCCR5B = 0;
			setTimer(microseconds);
			startTimer(func);
		}
		stopTimer(){
			TIMSK5 = 0;
		}		
};
extern timerFive timer5;
#endif
