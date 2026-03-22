#ifndef UART_H
#define UART_H

#include "util.h"
#include <avr/interrupt.h>

#define BAUD 9600

//uart prescaler calculation
#define UBRR_VAL ((F_CPU/(16UL*BAUD))-1UL)
#define UBRRH_VAL (UBRR_VAL >> 8)
#define UBRRL_VAL (UBRR_VAL & 0xff)

//Ring Buffer
struct  ring_buffer
{
    uint8_t *buffer;
    uint8_t size; 
    uint8_t head;
    uint8_t tail;
};

void ring_buffer_put(struct ring_buffer* rb, uint8_t data);
uint8_t ring_buffer_get(struct ring_buffer* rb);
uint8_t ring_buffer_peek(const struct ring_buffer* rb);
bool ring_buffer_full(const struct ring_buffer* rb);
bool ring_buffer_empty(const struct ring_buffer* rb);


//UART
void uart_init(void);
void uart_putchar(char data);
void printStr(const char str[]);
void printByte(uint8_t data);


#endif