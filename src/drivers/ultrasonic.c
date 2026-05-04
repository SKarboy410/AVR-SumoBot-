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

volatile ultrasonic_sensor ultrasonic_side[2]; // for side sensors

void ultrasonic_main_init(void){
    gpio_set(US1_TRIG,OUTPUT);
    gpio_write(US1_TRIG,LOW);
    gpio_set(US1_ECHO,INPUT);

    TCCR1A = 0;
    TCCR1B = (1<<CS11); //set prescaler to 8
    TCCR1B |= (1<<ICNC1) | (1<<ICES1);
    //ICNC - Noise Filter, ICES - Input capture edge select for echo pulses, set to rising edge here

    TIMSK1 |= (1<<ICIE1); //input capture interrupt enable

}

void ultrasonic_main_trigger(void){
    gpio_write(US1_TRIG,HIGH); //write 1 to trig pin
    _delay_us(10); //trig pin needs to enabled for 10 microseconds for it send a pulse
    gpio_write(US1_TRIG,LOW); //set it back to low

    awaiting_for_echo = 1; //wait
}

ISR(TIMER1_CAPT_vect){ //if input capture pin detects rising/falling edge
    if(!awaiting_for_echo)
        return;
    
    if(TCCR1B & (1<<ICES1)){ //detect rising edge
        echo_start_time = ICR1; //capture time of rising edge
        TCCR1B &= ~(1<<ICES1); //set to detect falling edge
    }
    else{
        echo_end_time = ICR1; //capture time of falling edge

        TCCR1B |= (1<<ICES1); //set back to rising edge for next pulse

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
        pulse_duration = (0xFFFF - start_time) + end_time + 1; //avoid negative values

    return (uint16_t)(pulse_duration/116); //116 because time scale is different
}

//Ultrasonic 2 and 3
//For the side sensors, a pin change interrupt is used, which detects any change in the pin of the port

//Pin Change Interrupt Request
ISR(PCINT2_vect) {
    uint32_t now = micros();

    if (ultrasonic_side[0].state == 0 && gpio_read(US2_ECHO)) { //read start time
        ultrasonic_side[0].start = now;
        ultrasonic_side[0].state = 1;
    } 
    else if (ultrasonic_side[0].state == 1 && !gpio_read(US2_ECHO)) { //get pulse duration
        ultrasonic_side[0].width = now - ultrasonic_side[0].start;
        ultrasonic_side[0].state = 0;
        ultrasonic_side[0].ready = 1;
    }
}

ISR(PCINT1_vect) { 
    uint32_t now = micros();

    if (ultrasonic_side[1].state == 0 && gpio_read(US3_ECHO)) { //read start time
        ultrasonic_side[1].start = now;
        ultrasonic_side[1].state = 1;
    } 
    else if (ultrasonic_side[1].state == 1 && !gpio_read(US3_ECHO)) { //get pulse duration
        ultrasonic_side[1].width = now - ultrasonic_side[1].start;
        ultrasonic_side[1].state = 0;
        ultrasonic_side[1].ready = 1;
    }
}

void ultrasonic_side_init(){
    gpio_set(US2_TRIG,OUTPUT);
    gpio_set(US3_TRIG,OUTPUT);

    gpio_set(US2_ECHO,INPUT);
    gpio_set(US3_ECHO,INPUT);

    PCICR |= (1 << PCIE1); //pin change for PORTC
    PCICR |= (1 << PCIE2); //pin change for PORTD

    PCMSK1 |= (1 << PCINT8); //for PC0(A0)
    PCMSK2 |= (1 << PCINT23); //for PD7(D7)

}

void ultrasonic2_trigger(){
    gpio_write(US2_TRIG,HIGH); //write 1 to trig pin
    _delay_us(10); //trig pin needs to enabled for 10 microseconds for it send a pulse
    gpio_write(US2_TRIG,LOW); //set it back to low

    ultrasonic_side[0].state = 0;
    ultrasonic_side[0].ready = 0;
}

void ultrasonic3_trigger(){
    gpio_write(US3_TRIG,HIGH); //write 1 to trig pin
    _delay_us(10); //trig pin needs to enabled for 10 microseconds for it send a pulse
    gpio_write(US3_TRIG,LOW); //set it back to low

    ultrasonic_side[1].state = 0;
    ultrasonic_side[1].ready = 0;
}

uint16_t ultrasonic_side_get_dist(uint8_t i){
    uint32_t pulse_duration;

    cli();
    pulse_duration = ultrasonic_side[i].width;
    ultrasonic_side[i].ready = 0;
    sei();

    return pulse_duration/58; //actual distance formula
}

// Scheduler
uint8_t current = 0;
uint32_t last_trig = 0;

//basically fire each trigger sequentially
void ultrasonic_update(){

    
    for (uint8_t i = 0; i < 2; i++) {
        if (ultrasonic_side[i].state == 1 && (micros() - ultrasonic_side[i].start > 30000)) {
            ultrasonic_side[i].state = 0;
            ultrasonic_side[i].width = 0;
            ultrasonic_side[i].ready = 1;
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

//Main Init
void ultrasonic_init(){
    ultrasonic_main_init();
    ultrasonic_side_init();

    sei();
}

