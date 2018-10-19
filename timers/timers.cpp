#include "timers.h"

timerOne timer1;
#if defined(__AVR_ATmega2560__)
timerThree timer3;
timerFour timer4;
timerFive timer5;
#endif

void (*timerOne::funcCallback)() = NULL;
#if defined(__AVR_ATmega2560__)
void (*timerThree::funcCallback)() = NULL;
void (*timerFour::funcCallback)() = NULL;
void (*timerFive::funcCallback)() = NULL;
#endif

#if defined(__AVR__)
ISR(TIMER1_COMPA_vect)
{
  timer1.funcCallback();
}
#if defined(__AVR_ATmega2560__)
ISR(TIMER3_COMPA_vect){
	timer3.funcCallback();
}
ISR(TIMER4_COMPA_vect){
	timer4.funcCallback();
}
ISR(TIMER5_COMPA_vect){
	timer5.funcCallback();
}
#endif
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

