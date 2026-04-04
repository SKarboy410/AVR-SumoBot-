#ifndef PWM_H
#define PWM_H

#include "util.h"
#include "gpio.h"

void pwm_init();
void pwm_set_duty_cycle(gpio_pin_t pwm,uint8_t percent);

#endif