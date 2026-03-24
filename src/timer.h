#ifndef TIMER_H
#define TIMER_H

#include "util.h"
#include <avr/interrupt.h>

#define clockCyclesPerMicrosecond() (F_CPU/1000000UL)
#define clockCyclesToMicrosecond(a) ((a)/clockCyclesPerMicrosecond())
#define microsecondsToClockCycles(a) ((a)*clockCyclesPerMicrosecond())


//timer 0
void timer0_init(void);
bool delay_ms(uint64_t delay);
uint64_t millis(void);
// void delay_blocking_ms(uint64_t delay);

#endif