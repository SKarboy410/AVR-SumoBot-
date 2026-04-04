#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "util.h"

void ultrasonic_init(void);
void ultrasonic_trigger(void);
uint8_t ultrasonic_ready(void);

uint16_t ultrasonic_get_dist(void);

#endif