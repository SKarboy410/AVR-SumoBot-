#include "pwm.h"
#include <avr/io.h>

void pwm_init(){
    gpio_set(MOTOR1_EN,OUTPUT); //left motor
    gpio_set(MOTOR2_EN, OUTPUT); //right motor

    TCCR2A = 0;
    TCCR2B = 0;

    TCCR2A |= (1<<WGM21) | (1<<WGM20); // fast PWM mode
    TCCR2A |= (1<<COM2A1) | (1<<COM2B1); // non-inverting mode

    TCCR2B |= (1<<CS21);

    OCR2A = 0;
    OCR2B = 0;

}
void pwm_set(gpio_pin_t pwm, uint8_t value){
    if(pwm == MOTOR1_EN)
        OCR2A = value;
    else if(pwm == MOTOR2_EN)
        OCR2B = value;
}

void pwm_set_duty_cycle(gpio_pin_t pwm,uint8_t percent){
    if(percent > 100)
        percent = 100;


    uint8_t value = (percent * 255) / 100;    
    pwm_set(pwm,value);

}
