#include "gpio.h"

#include <avr/io.h>

//pin table
pinmap_t pin_table[15] = {
    [US1_TRIG] = {&DDRD,&PORTD,&PIND,(1<<PD2)}, // D2
    [US2_TRIG] = {&DDRD,&PORTD,&PIND,(1<<PD5)}, // D5
    [US3_TRIG] = {&DDRD,&PORTD,&PIND,(1<<PD4)}, // D4
    [US1_ECHO] = {&DDRB,&PORTB,&PINB,(1<<PB0)}, // D8
    [US2_ECHO] = {&DDRD,&PORTD,&PIND,(1<<PD7)}, // D7
    [US3_ECHO] = {&DDRC,&PORTC,&PINC,(1<<PC0)}, // A0
    [IR1] = {&DDRC,&PORTC,&PINC,(1<<PC1)}, // A1
    [IR2] = {&DDRC,&PORTC,&PINC,(1<<PC2)}, // A2
    [MOTOR1_DIR1] = {&DDRB,&PORTB,&PINB,(1<<PB1)}, // D9
    [MOTOR1_DIR2] = {&DDRB,&PORTB,&PINB,(1<<PB2)}, // D10
    [MOTOR1_EN] = {&DDRB,&PORTB,&PINB,(1<<PB3)}, // D11
    [MOTOR2_DIR1] = {&DDRD,&PORTD,&PIND,(1<<PD6)}, // D6
    [MOTOR2_DIR2] = {&DDRB,&PORTB,&PINB,(1<<PB4)}, // D12
    [MOTOR2_EN] = {&DDRD,&PORTD,&PIND,(1<<PD3)}, // D3
    [LED_BUILTIN] = {&DDRB,&PORTB,&PINB,(1<<PB5)} // D13                                                                                                                                                              

};

void gpio_set(uint8_t pin, uint8_t dir){
    pinmap_t *p = &pin_table[pin];
    if(dir == OUTPUT)
        *p->ddr |= p->bitmask;
    else if(dir == INPUT)
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



