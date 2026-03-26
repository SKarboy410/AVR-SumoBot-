#include "pwm.h"
#include <avr/io.h>

void pwm_init(){
    gpio_set(MOTOR1_EN,OUTPUT);
    gpio_set(MOTOR2_EN, OUTPUT);

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

void pwm_set_duty_cycle(gpio_pin_t pwm,float duty_cycle_percent){
    if(duty_cycle_percent < 0)
        duty_cycle_percent = 0;
    if(duty_cycle_percent > 100)
        duty_cycle_percent = 100;

    uint8_t value = (uint8_t)((duty_cycle_percent/100)*255);
    pwm_set(pwm,value);

}
