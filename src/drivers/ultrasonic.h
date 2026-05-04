#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "util.h"

// for ultrasonic sensors 2 and 3
typedef struct{
    uint32_t start;
    uint32_t width;
    uint8_t state;
    uint8_t ready;
} ultrasonic_sensor;

extern volatile ultrasonic_sensor ultrasonic_side[2];

void ultrasonic_init(void);
void ultrasonic_update(void);


void ultrasonic_main_trigger(void);
uint8_t ultrasonic_main_ready(void);

uint16_t ultrasonic_main_get_dist(void);
uint16_t ultrasonic_side_get_dist(uint8_t i);

void ultrasonic2_trigger(void);


#endif