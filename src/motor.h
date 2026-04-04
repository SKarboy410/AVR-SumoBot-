#ifndef MOTOR_H
#define MOTOR_H

#include "util.h"

typedef enum{
    FORWARD,
    REVERSE,
    STOP
}motor_dir;

void motor_init(); //initiatialize motor driver
void motor_left(motor_dir dir, uint8_t speed);
void motor_right(motor_dir dir, uint8_t speed);
#endif