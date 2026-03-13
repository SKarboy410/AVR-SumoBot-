#ifndef GPIO
#define GPIO

#include "util.h"
#include "pin_defines.h"

void gpio_init(void);
void gpio_set(uint8_t pin, uint8_t dir);
void gpio_read(uint8_t pin);
void gpio_write(uint8_t pin,uint8_t val);
void gpio_toggle(uint8_t pin);




#endif