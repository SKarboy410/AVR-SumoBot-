#ifndef GPIO_H
#define GPIO_H

#include "util.h"
#include "pin_defines.h"

void gpio_set(uint8_t pin, uint8_t dir);
void gpio_toggle(uint8_t pin);
void gpio_write(uint8_t pin,uint8_t val);
uint8_t gpio_read(uint8_t pin);


#endif