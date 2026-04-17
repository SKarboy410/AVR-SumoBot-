#ifndef PIN_DEFINE_H
#define PIN_DEFINE_H

#include "util.h"


typedef enum{
//Ultrason,ic Sensor
US1_TRIG,
US2_TRIG, 
US3_TRIG, 

US1_ECHO, 
US2_ECHO, 
US3_ECHO, 

//IR Sensors
IR1, 
IR2,

//Motor Driver
MOTOR1_DIR1, 
MOTOR1_DIR2, 
MOTOR1_EN, 

MOTOR2_DIR1,
MOTOR2_DIR2, 
MOTOR2_EN,

// LED debug
LED_BUILTIN

}gpio_pin_t;


typedef struct  {
    volatile uint8_t* ddr; 
    volatile uint8_t* port; 
    volatile uint8_t* pin_reg; 
    uint8_t bitmask;
} pinmap_t; 


extern pinmap_t pin_table[15];

#endif