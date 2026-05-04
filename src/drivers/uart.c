#include "uart.h"

#define UART_BUFFER_SIZE (16)
static uint8_t buffer[UART_BUFFER_SIZE];
static struct ring_buffer tx_buffer = {.buffer = buffer, .size = sizeof(buffer)}; //transmission

//start uart transmission
static void uart_tx_start(){
    if(!ring_buffer_empty(&tx_buffer)){
        UDR0 =  ring_buffer_peek(&tx_buffer);
    }
}

// runs everytime UDR register is empty
ISR(USART_UDRE_vect){
    ring_buffer_read(&tx_buffer); //read byte and move tail, byte is sent

    if(!ring_buffer_empty(&tx_buffer))
        uart_tx_start(); //load the rest
    else
        UCSR0B &= ~(1<<UDRIE0); //disable interrupt, stop TX
}

//ring buffer
void ring_buffer_write(struct ring_buffer* rb, uint8_t data){
    rb->buffer[rb->head] = data;
    rb->head++;

    //wrap around
    if(rb->head == rb->size)
        rb->head = 0;
}

uint8_t ring_buffer_read(struct ring_buffer* rb){
    const uint8_t data = rb->buffer[rb->tail];
    rb->tail++;

    //wrap around
    if(rb->tail == rb->size)
        rb->tail = 0;
    
    return data;
}

uint8_t ring_buffer_peek(const struct ring_buffer* rb){
    return rb->buffer[rb->tail];
}

bool ring_buffer_empty(const struct ring_buffer* rb){
    return rb->head==rb->tail;
}

bool ring_buffer_full(const struct ring_buffer* rb){
    uint8_t index_after_head = rb->head+1;
    if(index_after_head == rb->size)
        index_after_head = 0;
    return index_after_head == rb->tail;
}


//UART 
void uart_init(void){

    //set UART prescaler
    UBRR0H = UBRRH_VAL;
    UBRR0L = UBRRL_VAL;

    //uart transfer speed
    #if USE_2X
        UCSR0A |= (1<<U2X0);
    #else
        UCSR0A &= ~(1<<U2X0);
    #endif

    UCSR0B |= (1<<TXEN0) | (1<<RXEN0); // enable uart transmission/reciever
    UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01); // 8 data bits, 1 stop bit

    sei();


}

void uart_putchar(char data){

    uint8_t old = SREG;
    cli();

    const bool tx_ongoing = !ring_buffer_empty(&tx_buffer); // ongoing transmission
    ring_buffer_write(&tx_buffer,data);
    
    if(!tx_ongoing){ // if not tranmission is ongoing
        uart_tx_start();
        UCSR0B |= (1<<UDRIE0); // enable interrupts

    }    
    SREG = old;

    if(data == '\n')
        uart_putchar('\r');

}

void printStr(const char str[]){
    uint8_t i = 0;
    while(str[i]!='\0'){
        uart_putchar(str[i]);
        i++;
    }

}

void printByte(uint8_t data){
  uart_putchar('0' + (data / 100));      
  uart_putchar('0' + ((data / 10) % 10));                      
  uart_putchar('0' + (data % 10));
}

void printNum(uint16_t data){
  uart_putchar((data / 100)+'0');      
  uart_putchar(((data / 10) % 10)+'0');                      
  uart_putchar((data % 10)+'0');
}