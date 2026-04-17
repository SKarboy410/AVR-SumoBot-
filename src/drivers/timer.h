#ifndef TIMER_H
#define TIMER_H

#include "util.h"

#define clockCyclesPerMicrosecond() (F_CPU/1000000UL)
#define clockCyclesToMicrosecond(a) ((a)/clockCyclesPerMicrosecond())
#define microsecondsToClockCycles(a) ((a)*clockCyclesPerMicrosecond())


//timer 0
void timer0_init(void);
bool delay_ms(uint64_t delay);
uint64_t millis(void);
uint64_t micros(void);
// void delay_blocking_ms(uint64_t delay);

#endif