#ifndef TIMER
#define TIMER

#include <avr/wdt.h>
#include "util.h"
#include <avr/interrupt.h>

#define clockCyclesPerMicrosecond() (F_CPU/1000000UL)
#define clockCylesToMicrosecond(a) ((a)/clockCyclesPerMicrosecond())
#define microsecondsToClockCycles(a) ((a)*clockCyclesPerMicrosecond())


//timer 0
void timer0_init(void);
void delay_ms(uint64_t delay);
uint64_t millis(void);
#endif