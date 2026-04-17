#include "ultrasonic.h"
#include "gpio.h"
#include "timer.h"

#include <util/delay.h>
#include <avr/interrupt.h>

//code taken from MatGonPer
// Code for all three Ultrasonic sensors
/* Main ultrasonic sensor(Front) - Uses input capture with timer1
   Secondary ultrasonic sensors(Side) - Uses software based capturing
*/

static volatile uint16_t echo_start_time = 0;
static volatile uint16_t echo_end_time = 0;
static volatile uint8_t measurement_ready = 0;
static volatile uint8_t awaiting_for_echo = 0;

volatile ultrasonic_sensor us[2];

void ultrasonic_main_init(void){
    gpio_set(US1_TRIG,OUTPUT);
    gpio_write(US1_TRIG,LOW);
    gpio_set(US1_ECHO,INPUT);

    TCCR1A = 0;
    TCCR1B = (1<<CS11); // set prescaler to 8
    TCCR1B |= (1<<ICNC1) | (1<<ICES1);
    // ICNC - Noise Filter, ICES - INput capture edge select for echo pulses, set to rising edge here

    TIMSK1 |= (1<<ICIE1); // input capture interrupt enable

}

void ultrasonic_main_trigger(void){
    gpio_write(US1_TRIG,HIGH); // write 1 to trig pin
    _delay_us(10); // trig pin needs to enabled for 10 microseconds for it send a pulse
    gpio_write(US1_TRIG,LOW); // set it back to low

    awaiting_for_echo = 1;
}

ISR(TIMER1_CAPT_vect){ // detects edge
    if(!awaiting_for_echo)
        return;
    
    if(TCCR1B & (1<<ICES1)){
        echo_start_time = ICR1; // capture time of rising edge
        TCCR1B &= ~(1<<ICES1); // set to detect falling edge
    }
    else{
        echo_end_time = ICR1; // capture time of falling edge

        TCCR1B |= (1<<ICES1); // set back to rising edge for next pulse

        measurement_ready = 1;
        awaiting_for_echo = 0;
    }
}

uint8_t ultrasonic_main_ready(void){
    return measurement_ready;

}

uint16_t ultrasonic_main_get_dist(void){
    uint16_t start_time, end_time;
    uint32_t pulse_duration;

    cli();
    start_time = echo_start_time;
    end_time = echo_end_time;
    measurement_ready = 0;
    sei();

    if(end_time > start_time)
        pulse_duration = end_time - start_time;
    else
        pulse_duration = (0xFFFF - start_time) + end_time + 1; // avoid negative values

    return (uint16_t)(pulse_duration/116);
}

// Ultrasonic 2 and 3

// Pin Change Interrupt Request
ISR(PCINT2_vect) {
    uint32_t now = micros();

    if (us[0].state == 0 && gpio_read(US2_ECHO)) {
        us[0].start = now;
        us[0].state = 1;
    } 
    else if (us[0].state == 1 && !gpio_read(US2_ECHO)) {
        us[0].width = now - us[0].start;
        us[0].state = 0;
        us[0].ready = 1;
    }
}

ISR(PCINT1_vect) { 
    uint32_t now = micros();

    if (us[1].state == 0 && gpio_read(US3_ECHO)) {
        us[1].start = now;
        us[1].state = 1;
    } 
    else if (us[1].state == 1 && !gpio_read(US3_ECHO)) {
        us[1].width = now - us[1].start;
        us[1].state = 0;
        us[1].ready = 1;
    }
}

void ultrasonic_side_init(){
    gpio_set(US2_TRIG,OUTPUT);
    gpio_set(US3_TRIG,OUTPUT);

    gpio_set(US2_ECHO,INPUT);
    gpio_set(US3_ECHO,INPUT);

    PCICR |= (1 << PCIE1); // PORTC
    PCICR |= (1 << PCIE2); // PORTD

    PCMSK1 |= (1 << PCINT8);   // PC0
    PCMSK2 |= (1 << PCINT23);  // PD7

}

void ultrasonic2_trigger(){
    gpio_write(US2_TRIG,HIGH); // write 1 to trig pin
    _delay_us(10); // trig pin needs to enabled for 10 microseconds for it send a pulse
    gpio_write(US2_TRIG,LOW); // set it back to low

    us[0].state = 0;
    us[0].ready = 0;
}

void ultrasonic3_trigger(){
    gpio_write(US3_TRIG,HIGH); // write 1 to trig pin
    _delay_us(10); // trig pin needs to enabled for 10 microseconds for it send a pulse
    gpio_write(US3_TRIG,LOW); // set it back to low

    us[1].state = 0;
    us[1].ready = 0;
}

uint16_t ultrasonic_side_get_dist(uint8_t i){
    uint32_t w;

    cli();
    w = us[i].width;
    us[i].ready = 0;
    sei();

    return w/58;
}

// Scheduler
uint8_t current = 0;
uint32_t last_trig = 0;

void ultrasonic_update(){

    
    for (uint8_t i = 0; i < 2; i++) {
        if (us[i].state == 1 && (micros() - us[i].start > 30000)) {
            us[i].state = 0;
            us[i].width = 0;
            us[i].ready = 1;
        }
    }

    if(micros() - last_trig >= 40000){

        if(current == 0)
            ultrasonic_main_trigger();
        else if(current == 1)
            ultrasonic2_trigger();
        else
            ultrasonic3_trigger();

        current++;
        if (current == 3) 
            current = 0;

        last_trig = micros();
    }
}

// Main Init

void ultrasonic_init(){
    ultrasonic_main_init();
    ultrasonic_side_init();

    sei();
}



