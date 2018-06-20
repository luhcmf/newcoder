#include "timers.h"

timerOne timer1;
timerThree timer3;
timerFour timer4;
timerFive timer5;

void (*timerOne::funcCallback)() = NULL;
void (*timerThree::funcCallback)() = NULL;
void (*timerFour::funcCallback)() = NULL;
void (*timerFive::funcCallback)() = NULL;

#if defined(__AVR__)
ISR(TIMER1_COMPA_vect)
{
  timer1.funcCallback();
}
ISR(TIMER3_COMPA_vect){
	timer3.funcCallback();
}
ISR(TIMER4_COMPA_vect){
	timer4.funcCallback();
}
ISR(TIMER5_COMPA_vect){
	timer5.funcCallback();
}
/*
#elif defined(__arm__) && defined(CORE_TEENSY)
void ftm1_isr(void)
{
  uint32_t sc = FTM1_SC;
  #ifdef KINETISL
  if (sc & 0x80) FTM1_SC = sc;
  #else
  if (sc & 0x80) FTM1_SC = sc & 0x7F;
  #endif
  timer1.funcCallback();
}*/
#endif

