#include "timer.h"

//timer 0

#define MICROSECONDS_PER_TIMER0_OVF (clockCylesToMicrosecond(64*256)) // 1024
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVF/1000) // 1.024
#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVF%1000)>>3) // 24 >> 3 -> 3
#define FRACT_MAX (1000>>3) // 125

volatile uint64_t timer0_overflow_count = 0;
volatile uint64_t timer0_millis = 0;
static uint8_t timer0_fract = 0;

ISR(TIMER0_OVF_vect){

    uint64_t m = timer0_millis;
    uint8_t f = timer0_fract;

    m += MILLIS_INC;
    f += FRACT_INC;
    if(f>=FRACT_MAX){
        f -= FRACT_MAX;
        m +=1;
    }

    timer0_fract = f;
    timer0_millis = m;
    timer0_overflow_count++;

}

void timer0_init(){
    sei();
    TCNT0 = 0;
    //timer 0 already in NORMAL mode
    TCCR0B |= (1<<CS01) | (1<<CS00);
    TIMSK0 |= (1<<TOIE0);

}

uint64_t millis(){
    uint64_t m;
    uint8_t oldSREG = SREG, t;

    cli();
    m = timer0_overflow_count;
    t = TCNT0;

    if((TIFR0 & (1<<TOV0)) && (t< 255))
        m++;
        
    SREG = oldSREG;

    return ((m<<8) + t) * (64/clockCyclesPerMicrosecond());

}




