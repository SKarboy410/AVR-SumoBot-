#include "motor.h"
#include "gpio.h"
#include "pwm.h"
#include "pin_defines.h"

void motor_init(){
    pwm_init();
    //left motor
    gpio_set(MOTOR1_DIR1,OUTPUT);
    gpio_set(MOTOR1_DIR2,OUTPUT);
    //right motor
    gpio_set(MOTOR2_DIR1,OUTPUT);
    gpio_set(MOTOR2_DIR2,OUTPUT);
}

void motor_left(motor_dir dir, uint8_t speed){ // speed should be between 80 and 100
    if(dir == FORWARD){
        gpio_write(MOTOR1_DIR1,HIGH);
        gpio_write(MOTOR1_DIR2,LOW);
    }
    else if(dir == REVERSE){
        gpio_write(MOTOR1_DIR1,LOW);
        gpio_write(MOTOR1_DIR2,HIGH);
    }
    else if(dir == STOP){
        gpio_write(MOTOR1_DIR1,HIGH);
        gpio_write(MOTOR1_DIR2,HIGH);
    }

    pwm_set_duty_cycle(MOTOR1_EN,speed);

}

void motor_right(motor_dir dir, uint8_t speed){ // speed should be between 80 and 100
    if(dir == FORWARD){
        gpio_write(MOTOR2_DIR1,HIGH);
        gpio_write(MOTOR2_DIR2,LOW);
    }
    else if(dir == REVERSE){
        gpio_write(MOTOR2_DIR1,LOW);
        gpio_write(MOTOR2_DIR2,HIGH);
    }
    else if(dir == STOP){
        gpio_write(MOTOR2_DIR1,HIGH);
        gpio_write(MOTOR2_DIR2,HIGH);
    }

    pwm_set_duty_cycle(MOTOR2_EN, speed);
}