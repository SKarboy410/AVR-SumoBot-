#include "gpio.h"

#include <avr/io.h>

//pin table
pinmap_t pin_table[15] = {
    [US1_TRIG] = {&DDRD,&PORTD,&PIND,(1<<PD2)},
    [US2_TRIG] = {&DDRD,&PORTD,&PIND,(1<<PD5)},
    [US3_TRIG] = {&DDRD,&PORTD,&PIND,(1<<PD4)},
    [US1_ECHO] = {&DDRB,&PORTB,&PINB,(1<<PB0)},
    [US2_ECHO] = {&DDRD,&PORTD,&PIND,(1<<PD7)},
    [US3_ECHO] = {&DDRC,&PORTC,&PINC,(1<<PC0)},
    [IR1] = {&DDRC,&PORTC,&PINC,(1<<PC1)},
    [IR2] = {&DDRC,&PORTC,&PINC,(1<<PC2)},
    [MOTOR1_DIR1] = {&DDRB,&PORTB,&PINB,(1<<PB1)},
    [MOTOR1_DIR2] = {&DDRB,&PORTB,&PINB,(1<<PB2)},
    [MOTOR1_EN] = {&DDRD,&PORTD,&PIND,(1<<PD3)},
    [MOTOR2_DIR1] = {&DDRD,&PORTD,&PIND,(1<<PD6)},
    [MOTOR2_DIR2] = {&DDRB,&PORTB,&PINB,(1<<PB4)},
    [MOTOR2_EN] = {&DDRB,&PORTB,&PINB,(1<<PB3)},
    [LED_BUILTIN] = {&DDRB,&PORTB,&PINB,(1<<PB5)}

};

void gpio_set(uint8_t pin, uint8_t dir){
    pinmap_t *p = &pin_table[pin];
    if(dir == OUTPUT)
        *p->ddr |= p->bitmask;
    else
        *p->ddr &= ~(p->bitmask);

}

void gpio_write(uint8_t pin,uint8_t val){
    pinmap_t *p = &pin_table[pin];
    if(val==1)
        *p->port |= p->bitmask;
    else
        *p->port &= ~p->bitmask;

}

void gpio_toggle(uint8_t pin){
    pinmap_t *p = &pin_table[pin];
    *p->port ^= p->bitmask;
}

uint8_t gpio_read(uint8_t pin){
    pinmap_t *p = &pin_table[pin];
    return ((*p->pin_reg & p->bitmask)!=0);
}


